
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void lireWav(int* droit, int* gauche);

int main() {
    // Variables
    pid_t pidFils;
    int tube_resultat[2];
    int tube_donnees[2];

    // Pipe
    if (pipe( tube_resultat) == -1 || pipe( tube_donnees) == -1) {
        perror("Erreur lors de la création du tube");
        exit(EXIT_FAILURE);
    }

    // Fork
    pidFils = fork();
    switch(pidFils){
        case -1:
            perror("Erreur lors de la création du processus");
            exit(EXIT_FAILURE);
            break;
        case 0:
            // Processus fils
            int val;
            read(tube_donnees[0], &val, sizeof(int));
            while (val != -1)
            {
                
            }
            

            break;
        default:
            // Processus père
            int droite, gauche;
            lireWav(droite, gauche);

            write(tube_donnees[1], &droite, sizeof(int));

            
            break;
    }

}
