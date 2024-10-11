#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define TAILLE 10
int tab[TAILLE];
int max = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void thread(int *debut){
    int i, depart, fin;
    depart = *debut; // Départ du parcours
    fin = depart + TAILLE/2; // Fin du parcours
    for(i = depart; i < fin; i++){
        pthread_mutex_lock(&mutex);
        if(tab[i] > max){
            max = tab[i]; // Mise à jour du maximum
        }
        pthread_mutex_unlock(&mutex);
    }
}

void remplir_tableau(int* tableau, int taille, int valeur_debut) {
    for (int i = 0; i < taille; i++) {
        tableau[i] = valeur_debut + i; // Remplit le tableau avec des valeurs successives
    }
}

int main()
{

    pthread_t debThread1, debThread2;
    pthread_attr_t attr;
    pthread_t id1, id2;
    max = 0; // Initialisation de la variable partagée du maximum

    remplir_tableau(tab, TAILLE, 0);

    debThread1 = 0; debThread2 = TAILLE/2; // Point de départ pour chaque thread

    pthread_attr_init(&attr);
    pthread_create(&id1, &attr, (void *)thread, &debThread1);
    pthread_create(&id2, &attr, (void *)thread, &debThread2);

    pthread_join(id1, NULL);
    pthread_join(id2, NULL);
    printf("Le maximum est %lu\n", max);

    pthread_mutex_destroy(&mutex); // Suppression du mutex
    exit(EXIT_SUCCESS);

    return 0;
}
