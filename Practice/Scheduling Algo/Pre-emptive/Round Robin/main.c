// Preemptive Round Robin Scheduling algorithm 

#include <stdio.h>
#include <limits.h>

#define SIZE 1000

// Queue
int Q[SIZE] , front = -1 , rear = -1;

void Enqueue(int value){
    // Full?
    if(rear == SIZE - 1){
        printf("\nQ is full.\n");
        return;
    }   

    if(front == -1){
        front = 0;
    }

    rear++;
    Q[rear] = value;
}

int Dequeue(){
    // isEmpty?
    if(front == -1){
        return -1;
    }
    return Q[front++];
}

int isEmpty(){
    return (front == -1 || front > rear) ? 1 : 0;
}

struct RR{
    int pNo;
    int AT;
    int BT;
    int original_BT;
    int CT;
    int TAT;
    int WT;
};

void sort(struct RR arr[], int n){
    struct RR temp;
    int i, j;

    for(i = 0; i < n - 1; i++){
        for(j = i +1; j < n ;j++){
            if(arr[i].AT > arr[j].AT){
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main(){
    int n, tq, temp = 0, atat = 0, awt = 0, i , j, completed = 0;

    // Input TQ 
    printf("Enter the TQ: ");
    scanf("%d", &tq);

    // Input no of process
    printf("Enter the no of processes: ");
    scanf("%d", &n);

    // Input process details
    struct RR arr[n];
    printf("Enter AT & BT for each processes: ");
    for(i = 0; i < n; i++){
        arr[i].pNo = i +1;
        scanf("%d %d", &arr[i].AT, &arr[i].BT);
        arr[i].original_BT = arr[i].BT;
    }

    // sort processes as per their arrival time in increasing fashion
    sort(arr, n);

    // Initially add one process in the queue 
    int visited[n];

    for(i = 0; i < n; i++)
        visited[i] = 0;

    Enqueue(0);
    visited[0] = 1; // visited 

    // loop till all the processes are executed 
    while(completed < n){
        if(!isEmpty()){
            i = Dequeue();
            if(temp < arr[i].AT){
                printf("\nIdle Time: %d -> %d\n", temp, arr[i].AT);
                temp = arr[i].AT;
            }

            // Process completed it's execution
            if(arr[i].BT <= tq){
                temp += arr[i].BT;
                arr[i].BT = 0;
                arr[i].CT = temp;
                completed++; 
            }else{
                temp += tq;
                arr[i].BT -= tq;
            }

            // Identify remaining process which are arrived 
            for(j = 0; j < n; j++){
                if(!visited[j] && arr[j].AT <= temp && arr[j].BT > 0){
                    Enqueue(j);
                    visited[j] = 1;
                }
            }            

            // if the current process not finished yet 
            if(arr[i].BT > 0){
                Enqueue(i);
            }
        }else{
            // if the arrival time is too high 
            for(j = 0; j < n; j++){
                if(!visited[j]){
                    Enqueue(j);
                    visited[j] = 1;
                }
            }
        }
    }

    // calculate tat, wt , atat , awt 
    for(i = 0; i < n; i++){
        arr[i].TAT = arr[i].CT - arr[i].AT;
        arr[i].WT = arr[i].TAT - arr[i].original_BT;

        atat += arr[i].TAT;
        awt += arr[i].WT;
    }

    // Display results 
   printf("\nProcess\tArrival\tBurst\tCompletion\tTAT\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n",
               arr[i].pNo, arr[i].AT, arr[i].original_BT,
               arr[i].CT, arr[i].TAT, arr[i].WT);
    }

    printf("\nAverage Turnaround Time: %.2f", (float)atat / n);
    printf("\nAverage Waiting Time: %.2f\n", (float)awt / n);
    
    return 0;
}