#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUM 8
#define BUFFER_SIZE 10

// Buffer creation
int buffer[BUFFER_SIZE];
int count = 0;

// Semaphore declaration
sem_t semEmpty, semFull;

pthread_mutex_t mutexBuffer;
void *producer(void* args){
    while(1){
        // Produce
        int x = rand() % 100; // Generates 0 -> 99 numbers 
        sleep(1);
        sem_wait(&semEmpty); // Down operation
        pthread_mutex_lock(&mutexBuffer);
        // Add to buffer
        buffer[count++] = x;
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semFull); // Up operation
    }

    return NULL;
}

void *consumer(void* args){
    while(1){
        int y = -1;
        sem_wait(&semFull);
        pthread_mutex_lock(&mutexBuffer);
        // Remove an item from the buffer 
        y = buffer[count-1]; // FILO fashion
        count--;
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semEmpty);
        // Consume 
        printf("\nGot: %d", y);
        // sleep(1);
    }
    return NULL;
}

int main(){
    // Initialize mutexBuffer
    pthread_mutex_init(&mutexBuffer, NULL);

    // Semaphore Initialilzation
    sem_init(&semEmpty, 0, 10);
    sem_init(&semFull, 0, 0);

    // Thread Declaration 
    pthread_t t[THREAD_NUM];

    // Thread Creation
    for(int i = 0 ; i< THREAD_NUM ;i++){
        // Creation of producer
        if(i % 2 == 0){
            if(pthread_create(&t[i], NULL, &producer, NULL)!=0){
                printf("Thread is not created\n");
            }
        }else{
            if(pthread_create(&t[i], NULL, &consumer, NULL)!=0){
                printf("Thread is not created\n");
            }
        }
    }

    // Wait for the thread to finish
    for(int i = 0 ; i<THREAD_NUM ;i++){
        if(pthread_join(t[i], NULL)!=0){
            printf("Thread is not finished\n");
        }
    }

    // Destroy mutex 
    pthread_mutex_destroy(&mutexBuffer);

    return 0;
}