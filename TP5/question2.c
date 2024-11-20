#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>


void traiter_sigint(int sig){
}


void main(){
    // Définition du signal
    struct sigaction sig_a;
    sig_a.sa_handler = SIG_IGN;
    sig_a.sa_flags = 0;
    sigemptyset(&sig_a.sa_mask);  

    // Créer le signal
    sigaction(SIGINT, &sig_a, NULL);

    // Boucle infinie d'affichage de points
    while(1){
        printf(".");
    }
}