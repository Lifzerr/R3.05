/*
Question 1
Il y aura eu 4 processus quand le programme sera terminé.
A : 1 B: 2 C : 4
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define SIZE 1000000  // Taille du tableau
#define TARGET 123456 // Élément à rechercher

void search(int *arr, int start, int end, const char *who, bool *indicator) {
    for (int i = start; i < end; i++) {
        if (arr[i] == TARGET) {
            printf("%s a trouvé en position : %d\n", who, i);
            *indicator = true;
            exit(EXIT_SUCCESS);  // On termine dès qu'on a trouvé l'élément
        }
    }
    exit(EXIT_FAILURE);  // Si l'élément n'est pas trouvé
}


bool search2(int *arr, int start, int end, const char *who) {
    for (int i = start; i < end; i++) {
        if (arr[i] == TARGET) {
            printf("%s a trouvé en position : %d\n", who, i);
            return true;
        }
    }
    return false;  // Si l'élément n'est pas trouvé
}

int main() {

    // Question 2a) & b-- Fonctionnels 

    int *arr = malloc(SIZE * sizeof(int));

    if (arr == NULL) {
        perror("Erreur d'allocation de mémoire");
        exit(EXIT_FAILURE);
    }

    // Initialisation du tableau avec des valeurs quelconques
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i;
    }

    pid_t pid = fork();  // Création d'un processus fils

    if (pid < 0) {
        perror("Erreur lors de la création du processus");
        exit(EXIT_FAILURE);
    }

    /* Version 1 - Question 2a) 
    if (pid == 0) {
        // Code du processus fils : il explore la 2ème moitié du tableau
        search(arr, SIZE / 2, SIZE, "Le fils", &found);
    } else {
        // Code du processus père : il explore la 1ère moitié du tableau
        search(arr, 0, SIZE / 2, "Le père", &found);
    } */


    // Version 2 - Question 2b)
        bool pere_trouve = false;
    bool fils_trouve = false;

    if (pid == 0) {
        // Code du processus fils : il explore la 2ème moitié du tableau
        fils_trouve = search2(arr, SIZE / 2, SIZE, "Le fils");
        exit(EXIT_SUCCESS);  // Le fils termine après sa recherche
    } else {
        // Code du processus père : il explore la 1ère moitié du tableau
        pere_trouve = search2(arr, 0, SIZE / 2, "Le père");

        // Le père attend que le fils ait fini
        wait(NULL);

        // Vérification finale
        if (!pere_trouve && !fils_trouve) {
            printf("L'élément n'a pas été trouvé\n");
        }
    }


    
    free(arr);  // Libération de la mémoire
    return 0;
}
