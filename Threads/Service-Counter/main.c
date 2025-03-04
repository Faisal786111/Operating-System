#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_QUEUE_SIZE 10
#define NUM_CUSTOMERS 20
#define NUM_SERVICE_PERSONNEL 2

int queue[MAX_QUEUE_SIZE];
int count = 0;
int is_counter_open = 0; // 0 means closed, 1 means open

pthread_mutex_t mutexQueue; // Ensure adding/remove customer safely
sem_t queue_sem, service_sem; 

void *customer(void *args) {
    int id = *(int *)args;
    free(args);
    sleep(rand() % 3 + 1);

    pthread_mutex_lock(&mutexQueue);
    if (count == MAX_QUEUE_SIZE) {
        printf("Customer %d left as the queue is full.\n", id);
        pthread_mutex_unlock(&mutexQueue);
        return NULL;
    }

    if (!is_counter_open) {
        is_counter_open = 1;
        printf("Customer %d woke up the service personnel!\n", id);
        sem_post(&service_sem);
    }
    
    queue[count++] = id;
    printf("Customer %d joined the queue.\n", id);
    pthread_mutex_unlock(&mutexQueue);
    sem_post(&queue_sem);
    
    return NULL;
}

void *service_personnel(void *args) {
    while (1) { // waiting for work
        sem_wait(&service_sem);
        printf("Service personnel is now working.\n");
        
        while (1) { // serving customers
            sem_wait(&queue_sem);
            pthread_mutex_lock(&mutexQueue);
            
            if (count == 0) {
                is_counter_open = 0;
                printf("Queue is empty. Service personnel is sleeping.\n");
                pthread_mutex_unlock(&mutexQueue);
                break;
            }
            
            int customer_id = queue[0];
            for (int i = 1; i < count; i++) {
                queue[i - 1] = queue[i];
            }
            count--;
            
            printf("Serving customer %d.\n", customer_id);
            pthread_mutex_unlock(&mutexQueue);
            sleep(2);
        }
    }
    return NULL;
}

int main() {
    pthread_mutex_init(&mutexQueue, NULL);
    sem_init(&queue_sem, 0, 0);
    sem_init(&service_sem, 0, 0);
    
    pthread_t service_threads[NUM_SERVICE_PERSONNEL];
    for (int i = 0; i < NUM_SERVICE_PERSONNEL; i++) {
        pthread_create(&service_threads[i], NULL, service_personnel, NULL);
    }
    
    pthread_t customer_threads[NUM_CUSTOMERS];
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&customer_threads[i], NULL, customer, id);
        sleep(rand() % 2 + 1);
    }
    
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        pthread_join(customer_threads[i], NULL);
    }
    
    for (int i = 0; i < NUM_SERVICE_PERSONNEL; i++) {
        pthread_join(service_threads[i], NULL);
    }
    
    pthread_mutex_destroy(&mutexQueue);
    sem_destroy(&queue_sem);
    sem_destroy(&service_sem);
    
    return 0;
}
