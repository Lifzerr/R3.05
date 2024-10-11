#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* compteur(void* arg) {
    unsigned long* cpteur = (unsigned long*)arg; // Cast de l'argument en pointeur
    for (int i = 0; i < 10000000; i++) {
        pthread_mutex_lock(&mutex);
        (*cpteur)++; // Incrémente la valeur pointée par cpteur
        pthread_mutex_unlock(&mutex);
    }
    printf("%lu", arg, "\n");
}

int main() {
    // Variables
    unsigned long compteur_valeur = 0;
    const unsigned int NB_THREADS = 2;
    pthread_attr_t attr;

    // Créer 2 threads
    pthread_t threads[NB_THREADS];

    pthread_attr_init(&attr);
    for (int i = 0; i < NB_THREADS; i++) {
        pthread_create(&threads[i], &attr, compteur, &compteur_valeur); // Passer l'adresse
    }

    // Attendre que tous les threads se terminent
    for (int i = 0; i < NB_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Valeur finale du compteur : %lu\n", compteur_valeur);

    pthread_mutex_destroy(&mutex);
    exit(EXIT_SUCCESS);
}
