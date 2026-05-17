#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int data = 0, readcount = 0;

sem_t mutex, wrt;

void *reader(void *arg) {

    sem_wait(&mutex);
    readcount++;

    if (readcount == 1)
        sem_wait(&wrt);

    sem_post(&mutex);

    printf("Reader reads: %d\n", data);

    sem_wait(&mutex);
    readcount--;

    if (readcount == 0)
        sem_post(&wrt);

    sem_post(&mutex);

    return NULL;
}

void *writer(void *arg) {

    sem_wait(&wrt);

    data++;
    printf("Writer writes: %d\n", data);

    sem_post(&wrt);

    return NULL;
}

int main() {

    pthread_t r1, r2, w1;

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    // Writer first
    pthread_create(&w1, NULL, writer, NULL);
    pthread_join(w1, NULL);

    // Readers after writer
    pthread_create(&r1, NULL, reader, NULL);
    pthread_create(&r2, NULL, reader, NULL);

    pthread_join(r1, NULL);
    pthread_join(r2, NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
