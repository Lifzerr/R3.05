#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>  // Pour les sémaphores
#include <unistd.h>     // Pour la fonction sleep()

// Déclaration des sémaphores et variables globales
sem_t mutex;      // Protéger le compteur de lecteurs
sem_t boite;      // Protéger l'accès à la boîte (exclusion mutuelle)
int nb_lecteurs = 0;  // Compteur de lecteurs
char message[256];    // Boîte à lettres pour stocker un message

// Fonction pour les écrivains
void* ecrivain(void* arg) {
    while (1) {
        // Préparation du message (simulé par une pause)
        printf("Écrivain %ld prépare un message...\n", (long) arg);
        sleep(1);  // Simule la préparation du message

        // Prendre le sémaphore boite pour bloquer l'accès aux lecteurs et autres écrivains
        sem_wait(&boite);

        // Écriture du message
        printf("Écrivain %ld écrit un message.\n", (long) arg);
        snprintf(message, sizeof(message), "Message de l'écrivain %ld", (long) arg);

        // Libérer la boîte pour permettre aux lecteurs d'accéder
        sem_post(&boite);
        printf("Écrivain %ld a terminé d'écrire.\n", (long) arg);

        sleep(2);  // Pause avant de recommencer
    }
    return NULL;
}

// Fonction pour les lecteurs
void* lecteur(void* arg) {
    while (1) {
        // Prendre le sémaphore mutex pour protéger l'accès au compteur de lecteurs
        sem_wait(&mutex);
        nb_lecteurs++;
        if (nb_lecteurs == 1) {
            // Premier lecteur : bloquer l'accès aux écrivains
            sem_wait(&boite);
        }
        sem_post(&mutex);  // Libérer l'accès au compteur de lecteurs

        // Lire le message
        printf("Lecteur %ld lit le message : %s\n", (long) arg, message);

        // Prendre le mutex à nouveau pour décrémenter le compteur
        sem_wait(&mutex);
        nb_lecteurs--;
        if (nb_lecteurs == 0) {
            // Dernier lecteur : libérer l'accès aux écrivains
            sem_post(&boite);
        }
        sem_post(&mutex);  // Libérer l'accès au compteur de lecteurs

        sleep(1);  // Pause avant de relire
    }
    return NULL;
}

int main() {
    // Initialisation des sémaphores
    sem_init(&mutex, 0, 1);  // Mutex initialisé à 1
    sem_init(&boite, 0, 1);  // Boîte initialisée à 1 (libre)

    // Création des threads pour les lecteurs et écrivains
    pthread_t lecteurs[2], ecrivains[1];

    // Lancer 2 lecteurs
    for (long i = 0; i < 2; i++) {
        pthread_create(&lecteurs[i], NULL, lecteur, (void*) i);
    }

    // Lancer 1 écrivain
    for (long i = 0; i < 1; i++) {
        pthread_create(&ecrivains[i], NULL, ecrivain, (void*) i);
    }

    // Attendre les threads (même si dans ce cas, ils tournent en boucle infinie)
    for (int i = 0; i < 2; i++) {
        pthread_join(lecteurs[i], NULL);
    }
    for (int i = 0; i < 1; i++) {
        pthread_join(ecrivains[i], NULL);
    }

    // Destruction des sémaphores
    sem_destroy(&mutex);
    sem_destroy(&boite);

    return 0;
}
