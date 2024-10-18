
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main() {
    // Variables
    pid_t pidFils;


    // Pipe
    int tube[2];
    if (pipe(tube) == -1) {
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


            break;
        default:
            // Processus père


            break;
    }

}
