#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* boucle_infinie(void* arg) {
    setbuf(stdout, NULL); // Désactive la bufferisation de stdout
    while (1) {
        printf(".\n");
        sleep(1); // Attend 1 seconde
    }
    return NULL;
}

void* attendre_entree(void* arg) {
    printf("Tapez un caractère : ");
    getchar(); // Attend un caractère
    return NULL;
}


int main() {
    pthread_t thread1, thread2;
    pthread_attr_t attr;

    // Initialiser les attributs du thread
    pthread_attr_init(&attr);
    // Définir l'état de détachement
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // Crée le premier thread
    pthread_create(&thread1, &attr, boucle_infinie, NULL);
    // Crée le deuxième thread
    pthread_create(&thread2, &attr, attendre_entree, NULL);

    // Libérer les attributs après leur utilisation
    pthread_attr_destroy(&attr);

    printf("Les 2 threads sont lancés\n");

    // Attendre que le deuxième thread se termine
    pthread_join(thread2, NULL);

    // Terminer le programme proprement
    return 0;
}
