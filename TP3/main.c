#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
unsigned long cpteur = 0;

void* compteur() {
    unsigned long tmp;
    for (int i = 0; i < 10000000; i++) {
        pthread_mutex_lock(&mutex);
        tmp = cpteur;
        tmp++; 
        cpteur = tmp;
        pthread_mutex_unlock(&mutex);
    }
    
    printf("%lu\n", cpteur);
}

int main() {
    // Mesurer le temps de début
    clock_t debut = clock();

    // Variables
    const unsigned int NB_THREADS = 2;
    pthread_attr_t attr;

    // Créer 2 threads
    pthread_t threads[NB_THREADS];

    pthread_attr_init(&attr);
    for (int i = 0; i < NB_THREADS; i++) {
        pthread_create(&threads[i], &attr, compteur, NULL); // Passer l'adresse
    }

    // Attendre que tous les threads se terminent
    for (int i = 0; i < NB_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Mesurer le temps de fin
    clock_t fin = clock();

    // Calculer la durée d'exécution en secondes
    double duree = (double)(fin - debut) / CLOCKS_PER_SEC;
    printf("Valeur finale du compteur : %lu\n", cpteur);
    printf("Durée d'exécution : %f secondes\n", duree);

    pthread_mutex_destroy(&mutex);
    exit(EXIT_SUCCESS);
}
