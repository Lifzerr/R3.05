#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

void traiter_sigtstp(int sig) {
    printf("\nLoupé !!\n");

    // Boucle infinie sans affichage
    while (true) {
        // Boucle vide
    }
}

int main() {
    // Définition du gestionnaire pour SIGTSTP
    struct sigaction sig_tstp;
    sig_tstp.sa_handler = traiter_sigtstp;
    sig_tstp.sa_flags = 0;
    sigemptyset(&sig_tstp.sa_mask);

    // Associer SIGTSTP au gestionnaire
    sigaction(SIGTSTP, &sig_tstp, NULL);

    // Boucle infinie d'affichage de points
    while (1) {
        printf(".");
        fflush(stdout); // Assurer l'affichage immédiat des points
        sleep(1);
    }

    return 0;
}
