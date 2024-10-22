#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SIZE 1000000  // Taille du tableau
#define TARGET 995256 // Élément à rechercher

// Variable globale pour le fils afin de savoir s'il doit interrompre sa recherche
volatile sig_atomic_t arret_fils = 0;
volatile sig_atomic_t arret_pere = 0;

// Gestionnaire du signal SIGUSR1
void handle_sigusr1(int sig) {
    arret_fils = 1;  // Le signal indique d'arrêter la recherche
}

// Gesttionnaire du signal SIGUSR2
void handle_sigusr2(int sig) {
    arret_pere = 1;  // Le signal indique d'arrêter la recherche
}

// Fonction de recherche utilisée par le fils
bool search_fils(int *arr, int start, int end, const char *who) {
    for (int i = start; i < end; i++) {
        if (arret_fils || arret_pere) {
            // Si le signal a été reçu, le fils arrête la recherche
            printf("%s a été interrompu\n", who);
            return false;
        }

        if (arr[i] == TARGET) {
            printf("%s a trouvé en position : %d\n", who, i);
            return true;
        }
    }
    return false;
}


int main() {
    int *arr = malloc(SIZE * sizeof(int));
    if (arr == NULL) {
        perror("Erreur d'allocation de mémoire");
        exit(EXIT_FAILURE);
    }

    // Initialisation du tableau avec des valeurs quelconques
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i;
    }

    pid_t pid = fork();  // Création d'un processus fils

    if (pid < 0) {
        perror("Erreur lors de la création du processus");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Code du processus fils : il explore la 2ème moitié du tableau
        signal(SIGUSR1, handle_sigusr1);  // Installation du gestionnaire de signal

        bool fils_trouve = search_fils(arr, SIZE / 2, SIZE, "Le fils");

        if (fils_trouve) {
            // Si le fils trouve l'élément, il sort
            exit(EXIT_SUCCESS);
        } else {
            exit(EXIT_FAILURE);
        }
    } else {
        // Code du processus père : il explore la 1ère moitié du tableau
        signal(SIGUSR2, handle_sigusr2);

        bool pere_trouve = search_fils(arr, 0, SIZE / 2, "Le père");

        if (pere_trouve) {
            // Si le père trouve l'élément, il envoie SIGUSR1 au fils
            kill(pid, SIGUSR1);
        }

        // Le père attend que le fils termine
        wait(NULL);

        // Si ni le père ni le fils n'ont trouvé l'élément
        if (!pere_trouve) {
            printf("L'élément n'a pas été trouvé\n");
        }
    }

    free(arr);  // Libération de la mémoire
    return 0;
}
