#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>

#define THREAD_NUM 16

sem_t semaphore; // semaphore declaration

void *test(void *args){
    printf("(%d) Waiting in login queue\n", *(int*)args);

    sem_wait(&semaphore); // Down Operation

    printf("(%d) Logged in\n", *(int*)args);
    sleep(rand() % 5 + 1);
    printf("(%d) Logged out\n", *(int*)args);

    sem_post(&semaphore); // Up Operation

    free(args);
}

int main(){
    pthread_t t[THREAD_NUM]; // Thread declaration
    // 12 threads can access critical section
    // 0 is for thread
    sem_init(&semaphore, 0, 12); // Semaphore initializationi

    // Thread creation 
    for(int i=0 ;i<THREAD_NUM ;i++){
        int *a = malloc(sizeof(int));
        *a = i;
        if(pthread_create(&t[i], NULL, &test, a)!= 0){
            printf("Thread is not created\n");
        }
    }

    // wait for the thread to finish    
    for(int i =0; i<THREAD_NUM ;i++){
        if(pthread_join(t[i], NULL)!= 0){
            printf("Thread is not finished\n");
        }
    }

    // Destory Semaphore
    sem_destroy(&semaphore);

    return 0;
}