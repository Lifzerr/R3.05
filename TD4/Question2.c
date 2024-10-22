
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>


// Variables globales pour le contrôle du signal
int saisie_faite = 0;

// Gestionnaire du signal pour afficher le message ou terminer
void alarm_handler(int sig) {
    if (!saisie_faite) {
        static int alarm_count = 0;
        if (alarm_count == 0) {
            printf("alors ça vient\n");
            alarm(5); // Attendre 30 secondes supplémentaires
            alarm_count++;
        } else {
            printf("Bon j'abandonne !\n");
            exit(0); // Quitter le programme
        }
    }
}

int main() {
    // Configuration du gestionnaire de signal
    signal(SIGALRM, alarm_handler);

    // Déclencher l'alarme après 15 secondes
    alarm(3);

    // Attendre la saisie utilisateur
    char buffer[128];
    printf("Entrez quelque chose : ");
    fgets(buffer, sizeof(buffer), stdin);

    // Si la saisie est faite avant l'alarme
    saisie_faite = 1;

    // Annuler l'alarme après la saisie
    alarm(0);

    // Simuler un calcul (attente de 50 secondes)
    printf("Traitement en cours...\n");
    sleep(5);

    // Fin du programme
    printf("Terminé.\n");
    return 0;
}