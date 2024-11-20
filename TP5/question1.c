#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

void main(){
    // Boucle infinie d'affichage de points
    while(1){
        printf(".");
    }
}