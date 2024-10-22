#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

// Structure sigaction
struct sigaction sig_abandon;




void msgAlarm(int sig){
    printf("\nAlors ça vient ?\n");$
    // odification du signal 
    sig_abandon.sa_handler = msgAlarm2;
    sig_abandon.sa_flags = SA_RESETHAND;
    sigemptyset(&sig_abandon.sa_mask);
    sigaction(SIGALRM, &sig_abandon, NULL);
    alarm(30);
}


void msgAlarm2(int sig){
    printf("\nBon j'abandonne !\n");
    exit(0);
}  


int main(){
    // Variables
    char c;
    struct sigaction sig_relance, ancien;
    sig_relance.sa_handler = msgAlarm;
    sig_relance.sa_flags = SA_RESTART;
    sigemptyset(&sig_relance.sa_mask);

    // Créer le signal
    sigaction(SIGALRM, &sig_relance, &ancien);

    // Créer l'alarme
    alarm(15);

    // Attendre la saisie utilisateur
    printf("Entrez quelque chose : ");
    scanf("%c", &c);

    // Annuler l'alarme
    alarm(0);

    // Simuler un calcul
    printf("Traitement en cours...\n");
    sigaction(SIGALRM, &ancien, NULL);
    sleep(10);
}