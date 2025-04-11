#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 20  // Total items to produce

int buffer[BUFFER_SIZE];
int count = 0;
int in = 0;  // Producer index
int out = 0; // Consumer index

sem_t empty, full;
pthread_mutex_t mutex;

void* producer(void* arg) {
    for (int i = 1; i <= MAX_ITEMS; i++) {
        sem_wait(&empty);  // Wait for empty slot
        pthread_mutex_lock(&mutex);

        // Produce item
        buffer[in] = i;
        in = (in + 1) % BUFFER_SIZE;
        count++;
        printf("Produced: %d\n", i);

        pthread_mutex_unlock(&mutex);
        sem_post(&full);  // Signal new item available
        sleep(1);  // Simulate production time
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 1; i <= MAX_ITEMS; i++) {
        sem_wait(&full);  // Wait for available item
        pthread_mutex_lock(&mutex);

        // Consume item
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;
        printf("Consumed: %d\n", item);

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);  // Signal empty slot available
        sleep(2);  // Simulate consumption time (slower than production)
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Cleanup
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    printf("Finished producing and consuming %d items\n", MAX_ITEMS);
    return 0;
}