#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>


volatile sig_atomic_t sigtstp_count = 0;

void traiter_sigtstp(int sig) {
    printf("\nLoupé !!\n");
}

int main() {
    // Définition du gestionnaire pour SIGTSTP
    struct sigaction sig_tstp;
    sig_tstp.sa_handler = traiter_sigtstp;
    sig_tstp.sa_flags = SA_RESETHAND;
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
