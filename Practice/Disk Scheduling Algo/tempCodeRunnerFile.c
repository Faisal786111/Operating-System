// Disk Scheduling Algorithm
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Fifo: Accept req as a serial manner 
void fifo(int n, int request[], int head){
    int movement = 0, i;
    int current = head;

    printf("\nFIFO Algorithm:\n");
    printf("Head moement: %d\n", current);

    for(i = 0; i <n; i++){
        printf("-> %d", request[i]);
        movement += abs(current - request[i]);
        current = request[i];
    }

    printf("\nSeek Time: %d", movement);
}

int main(){
    // Input details
    int n, request[MAX], maxNo, head,i;

    printf("Enter the no of track request : ");
    scanf("%d", &n);

    printf("Enter the request: \n");
    for(i = 0; i < n; i){
        scanf("%d", &request[i]);
    }

    printf("Enter the current head position: ");
    scanf("%d", &head);

    printf("Enter the max track no: ");
    scanf("%d", &maxNo);

    fifo(n, request, head);

}