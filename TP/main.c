#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>



int main(){
    //exercice1();

    exercice2();
    return 0;
}
/*
void exercice1(){
    printf("Exercice 1\n");

    printf("Je suis le processus numéro %x \n", getpid());
    int pid = fork();
    int pid2 = fork();
    printf ("Fork m'a renvoyé la valeur : %x \n", pid);
    printf("Je suis le processus, mon pid est %x et mon père est %x\n", getpid(), getppid());

    if (pid == 0){
        printf("Je suis le fils, mon pid est %x et mon père est %x\n", getpid(), getppid());
    } else {
        printf("Je suis le père, mon pid est %x et mon fils est %x\n", getpid(), pid);
    }
    exit(EXIT_SUCCESS);
}*/


void exercice2(){
    // Créer le processus fils
    int son = fork();

    // Traitements
    if(son < 0){
        printf("Erreur lors de la création du processus fils");
        exit(EXIT_FAILURE);
    }
    if(son == 0){
        printf("Processus fils");
        print_pairs(10);


    }
    else{
        printf("Processus père");
        print_impairs();
    }
    exit(EXIT_SUCCESS);
}


void print_pairs(int nbr){
    for(int i = 0; i < 10; i++){
        printf("Valeur = %d \n",2*i);
                sleep(1);
    }
    exit(EXIT_SUCCESS);
}

void print_impairs(int nbr){
    for(int i = 0; i < 10; i++){
        printf("Valeur = %d \n", 2*i+1);

    }
    exit(EXIT_SUCCESS);
}



