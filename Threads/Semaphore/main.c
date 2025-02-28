#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

// Binary Semaphore
sem_t semaphore; // Declare variable

void *test(void* args){
    sem_wait(&semaphore); // Down operation
    sleep(1);
    printf("Hello from Thread %d\n",*(int *)args);
    sem_post(&semaphore); // up operation
    free(args);
    return NULL;
}


int main(){
    
    // Semaphore initialization
    // second para: 0-> for thread , 1-> porcess
    // third para: assign 1 to s
    sem_init(&semaphore, 0, 1);
    
    // Declare thread variables
    pthread_t t[4];
    
    // Thread creation
    for(int i = 0 ; i < 4 ; i++){
        int *a = malloc(sizeof(int));
        *a = i;
        if(pthread_create(&t[i], NULL, &test, a)!=0){
            printf("\nThread is not created.");   
        }
    }
    
    // Wait for thread to finish
    for(int i = 0 ; i < 4; i++){
        if(pthread_join(t[i], NULL)!=0){
            printf("\nThread is not finished");   
        }
    }
    
    sem_destroy(&semaphore);
    
    return 0;
}