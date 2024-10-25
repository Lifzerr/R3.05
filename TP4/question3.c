#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
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
        printf("Entrez des caractères (terminez avec '$') :\n");

        // V

        while ((clavier = getchar()) != '$') {
            write(fd[1], &clavier, sizeof(char)); // Écrit le caractère dans le tube
        }

        // Envoyer le caractère de terminaison '$' au processus fils
        write(fd[1], &clavier, sizeof(char));
        close(fd[1]); // Ferme l'écriture du tube
        wait(NULL);   // Attend la fin du processus fils

    } else { // Processus fils
        close(fd[1]); // Ferme l'écriture du tube

        while (read(fd[0], &ecran, sizeof(char)) > 0) {
            if (ecran == '$') break; // Sortie si le caractère '$' est lu
            ecranMaj = toupper(ecran);      // Convertit en majuscule
            printf("Caractère reçu en majuscule : %c\n", ecranMaj);
        }
        close(fd[0]); // Ferme la lecture du tube
    }

    return EXIT_SUCCESS;
}
