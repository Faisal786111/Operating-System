#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // for unix system call funcitons like sleep etc

void *test(void* arg){
    printf("\nThread is created");
    sleep(3);
    printf("\nEnding thread.");
    return NULL;
}

int main(){
    
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
    
    printf("\nMain funciton terminated");

    return 0;
    
}