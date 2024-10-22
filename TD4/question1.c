#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>


// Gestionnaire du signal pour afficher le message
void alarm_handler(int sig) {
    printf("\nalors ça vient ?\n");
    alarm(15); // Redéclencher l'alarme toutes les 15 secondes
}

int main() {
    // Configuration du gestionnaire de signal
    signal(SIGALRM, alarm_handler);

    // Déclencher l'alarme dans 15 secondes
    alarm(2);

    // Attendre la saisie utilisateur
    char buffer[128];
    printf("Entrez quelque chose : ");
    fgets(buffer, sizeof(buffer), stdin);

    // Annuler l'alarme après la saisie
    alarm(0);

    // Simuler un calcul (attente de 50 secondes)
    printf("Traitement en cours...\n");
    sleep(10);

    // Fin du programme
    printf("Terminé.\n");
    return 0;
}
