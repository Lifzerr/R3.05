#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

// Variable globale pour le processus fils
volatile sig_atomic_t attente = 0;

// Gestionnaire pour SIGUSR1
void traiter_sigusr1(int sig) {
    attente = 1; // Met la variable globale à 1 pour sortir de la boucle
}

int main() {
    pid_t pid;

    // Création du processus fils
    pid = fork();

    if (pid == -1) {
        perror("Erreur lors du fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Code du processus fils

        // Associer SIGUSR1 à traiter_sigusr1
        struct sigaction sa;
        sa.sa_handler = traiter_sigusr1;
        sa.sa_flags = 0;
        sigemptyset(&sa.sa_mask);
        sigaction(SIGUSR1, &sa, NULL);

        printf("Fils : en attente du signal SIGUSR1...\n");

        // Boucle tant que 'attente' est à 0
        while (!attente) {
            // Boucle vide
        }

        printf("Fils : signal reçu, fin du processus fils.\n");
        exit(EXIT_SUCCESS);
    } else {
        // Code du processus père
        printf("Père : PID du fils = %d\n", pid);

        // Attendre 5 secondes
        sleep(5);

        // Envoyer SIGUSR1 au fils
        printf("Père : envoi du signal SIGUSR1 au fils.\n");
        kill(pid, SIGUSR1);

        // Attendre la terminaison du fils
        wait(NULL);
        printf("Père : fils terminé, fin du processus père.\n");
    }

    return 0;
}
