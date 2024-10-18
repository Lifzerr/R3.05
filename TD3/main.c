#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SIZE 100  // Taille du tableau

void add(int *arr, int start, int end, int* sum) {
    for (int i = start; i < end; i++) {
        *sum += arr[i];
    }
}

int main() {
    // Création du tableau
    int *arr = malloc(SIZE * sizeof(int));

    if (arr == NULL) {
        perror("Erreur d'allocation de mémoire");
        exit(EXIT_FAILURE);
    }

    // Initialisation du tableau avec des valeurs quelconques
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i;
    }

    // Création d'un tube pour communiquer entre les processus
    int tube[2];
    if (pipe(tube) == -1) {
        perror("Erreur lors de la création du tube");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();  // Création d'un processus fils

    if (pid < 0) {
        perror("Erreur lors de la création du processus");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Code du processus fils : il explore la 2ème moitié du tableau
        int sum_fils = 0;
        add(arr, SIZE / 2, SIZE, &sum_fils);
        
        close(tube[0]);  // Fermer le côté lecture
        write(tube[1], &sum_fils, sizeof(int));
        close(tube[1]);  // Fermer le côté écriture après écriture
        exit(EXIT_SUCCESS);  // Le processus fils se termine
    } else {
        // Code du processus père : il explore la 1ère moitié du tableau
        int sum_pere = 0;
        add(arr, 0, SIZE / 2, &sum_pere);

        int sum_fils;
        close(tube[1]);  // Fermer le côté écriture

        // Lecture de la somme calculée par le processus fils
        read(tube[0], &sum_fils, sizeof(int));
        close(tube[0]);  // Fermer le côté lecture après avoir lu

        // Afficher le résultat final
        printf("La somme des deux moitiés du tableau est : %d\n", sum_pere + sum_fils);
        
        // Attendre que le processus fils se termine
        wait(NULL);
    }

    // Libération de la mémoire
    free(arr);

    return 0;
}
