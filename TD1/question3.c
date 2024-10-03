
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>

#define SIZE 1000000  // Taille du tableau
#define TARGET 123456 // Élément à rechercher

// Fonction de recherche d'un élément dans un tableau
bool search2(int *arr, int start, int end, const char *who) {
    for (int i = start; i < end; i++) {
        if (arr[i] == TARGET) {
            printf("%s a trouvé en position : %d\n", who, i);
            return true;
        }
    }
    return false;  // Si l'élément n'est pas trouvé
}


// Type de données pour les arguments de la fonction de recherche
typedef struct {
    int *arr;
    int start;
    int end;
    const char *who;
} ThreadData;

int main(){

    // Question 3
    int *arr = malloc(SIZE * sizeof(int));

    if (arr == NULL) {
        perror("Erreur d'allocation de mémoire");
        exit(EXIT_FAILURE);
    }

    // Initialisation du tableau avec des valeurs quelconques
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i;
    }

    pthread_t thread1, thread2;
    bool found1 = false, found2 = false;
    
    // Création des données pour les threads
    ThreadData data1 = {arr, 0, SIZE / 2, "Thread 1"};
    ThreadData data2 = {arr, SIZE / 2, SIZE, "Thread 2"};

    // Création des threads
    pthread_create(&thread1, NULL, search2, &data1);
    pthread_create(&thread2, NULL, search2, &data2);

    // Attente de la fin des threads
    pthread_join(thread1, &found1);
    pthread_join(thread2, &found2);

    if (found1 || found2) {
        printf("L'élément a été trouvé\n");
    } else {
        printf("L'élément n'a pas été trouvé\n");
    }

    free(arr);
    return 0;
}