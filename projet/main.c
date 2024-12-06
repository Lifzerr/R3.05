#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

// Variables globales
int nbThreadsPresents = 0;
int X;
pthread_mutex_t mutexPersonnes = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexTps = PTHREAD_MUTEX_INITIALIZER;
int nbPersonnes;
int nbSec = 0;
int MAX_SEC;

// Fonction exécutée par chaque thread
void* travail(void* arg) {
    // Obtenir un ID unique pour le thread (facultatif ici)
    pthread_t id = pthread_self();

    // Récupérer le temps maximal d'attente
    int MAX_SEC = *((int*) arg);

    // Simuler un délai avant d'arriver
    sleep(2);
    printf("Je suis là (Thread %lu)\n", id);

    // Mettre à jour le nombre de threads présents
    pthread_mutex_lock(&mutexPersonnes);
    nbThreadsPresents++;
    nbPersonnes = nbThreadsPresents;
    pthread_mutex_unlock(&mutexPersonnes);

    // Boucle principale
    while (1) {
        sleep(1);

        // Vérifier le temps écoulé
        pthread_mutex_lock(&mutexTps);
        nbSec++;
        if (nbSec >= MAX_SEC) {
            pthread_mutex_unlock(&mutexTps);
            printf("Thread %lu : je suis banni :/\n", id);
            pthread_exit(NULL);
        }
        pthread_mutex_unlock(&mutexTps);

        // Vérifier si tout le monde est présent
        pthread_mutex_lock(&mutexPersonnes);
        if (nbPersonnes == X) {
            pthread_mutex_unlock(&mutexPersonnes);
            printf("Thread %lu : Tout le monde est là !\n", id);
            break;
        }
        pthread_mutex_unlock(&mutexPersonnes);
    }

    // Tous les threads commencent leur tâche
    printf("Thread %lu : J'effectue ma tâche\n", id);
    pthread_exit(NULL);
}

int main(void) {
    // Variables
    pthread_attr_t attr;

    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL));

    // Demander le nombre de threads
    printf("Combien de personnes ? ");
    scanf("%d", &X);

    // Création du tableau de threads
    pthread_t threads[X];

    // Définir un temps maximal aléatoire pour ce thread
    MAX_SEC = 5 + rand() % 5 + 1;
    printf("Temps d'attente maximal : %d secondes\n", MAX_SEC);

    // Créer les threads
    pthread_attr_init(&attr);
    for (int i = 0; i < X; i++) {
        pthread_create(&threads[i], NULL, travail, &MAX_SEC);
    }

    // Attendre la terminaison de tous les threads
    for (int i = 0; i < X; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Tous les threads ont terminé.\n");
    return 0;
}