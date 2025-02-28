#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int mails = 0;
pthread_mutex_t mutex; // Declare variable
void *test(void* arg){
    for(int i = 0 ; i < 1000000 ;i++){
        pthread_mutex_lock(&mutex); // avoid race condition
        mails++; // leads to race condition
        pthread_mutex_unlock(&mutex);
        // read mails
        // increment
        // write mails
    }
    return NULL;
}

int main(){
    
    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);
    
    // Declare thread variable
    pthread_t t1, t2;
    
    // Initialize thread 
    if(pthread_create(&t1, NULL, &test, NULL)!=0){
        printf("\nThread is not created.");
    }
    if(pthread_create(&t2, NULL, &test, NULL)!=0){
        printf("\nThread is not created.");
    }
    
    
    // wait for thread termination
    if(pthread_join(t1, NULL)!= 0){
        printf("\nThread not finished it's execution");
    }
    
    if(pthread_join(t2, NULL)!= 0){
        printf("\nThread not finished it's execution");
    }
    
    // Destroy mutex
    pthread_mutex_destroy(&mutex);
    
    printf("\nNumber of mails: %d", mails);

    return 0;
    
}