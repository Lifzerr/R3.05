#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>  

int main() {
    int fd[2];
    pid_t pid;
    char clavier, ecran, ecranMaj;

    // Création du tube
    if (pipe(fd) == -1) {
        perror("Erreur lors de la création du tube");
        exit(EXIT_FAILURE);
    }

    // Création du processus fils
    pid = fork();
    if (pid < 0) {
        perror("Erreur lors de la création du processus fils");
        exit(EXIT_FAILURE);
    }
    
    if (pid > 0) { // Processus père
        close(fd[0]); // Ferme la lecture du tube
        printf("Entrez des caractères (terminez avec Ctrl+D) :\n");

        // Lire les caractères du clavier jusqu'à la fin de l'entrée
        while ((clavier = getchar()) != '$') { 
            write(fd[1], &clavier, sizeof(char)); // Écrit le caractère dans le tube
        }


        // Ferme le descripteur d'écriture pour signaler la fin au processus fils
        close(fd[1]);
        wait(NULL);   // Attend la fin du processus fils

    } else { // Processus fils
        close(fd[1]); // Ferme l'écriture du tube

        // Boucle de lecture pour le processus fils
        while (read(fd[0], &ecran, sizeof(char)) > 0) {
            ecranMaj = toupper(ecran);      // Convertit en majuscule
            printf("Caractère reçu en majuscule : %c\n", ecranMaj);
        }

        // Ferme le descripteur de lecture une fois le tube vidé
        close(fd[0]);
    }

    return EXIT_SUCCESS;
}
