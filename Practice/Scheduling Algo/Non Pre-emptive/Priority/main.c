// Priority algorithm
// Non-preEmptive

#include <stdio.h>
#include <limits.h>

struct priority{
    int pNo;
    int AT;
    int BT;
    int priority;
    int CT;
    int TAT;
    int WT;
    int completed;
};

void sort(struct priority arr[], int n){
    int i, j;
    struct priority temp;
    for(i = 0; i < n - 1; i++){
        for(j = i+1; j < n; j++){
            if(arr[i].AT > arr[j].AT){
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main(){
    int n, i, completed = 0, temp = 0, awt = 0, atat = 0;

    // Input no of processes
    printf("Enter the no of processes : ");
    scanf("%d" , &n);

    struct priority arr[n];
    // Input process details 
    printf("\n Enter AT, BT, & Priorty for each processes:\n");
    for(i = 0; i < n; i++){
        arr[i].pNo = i + 1;
        scanf("%d %d %d", &arr[i].AT, &arr[i].BT, &arr[i].priority);
        arr[i].completed = 0;
    }

    // Sort process as per their arrival time in increasing fashion
    sort(arr, n);

    while(completed < n){
        int p = INT_MAX , shortIndex = -1;

        // Identify process which is having smallest priority 
        for(i = 0; i < n; i++){
            if(!arr[i].completed && arr[i].priority < p && arr[i].AT <= temp){
                p = arr[i].priority;
                shortIndex = i;
            }
        }

        // If no process arrived yet 
        if(shortIndex == -1){
            // Handle idle time 
            int nextArrival = INT_MAX;

            // Identify min arrival time process 
            for(i = 0; i < n; i++){
                if(!arr[i].completed && arr[i].AT < nextArrival){
                    nextArrival = arr[i].AT;
                }
            }

            if(temp < nextArrival){
                printf("\nIdle Time: %d -> %d\n", temp, nextArrival);
                temp = nextArrival;
            }
            // Skip the current iteration
            continue;
        }

        // process selected
        // cacl ct, tat, wt, awt, atat
        arr[shortIndex].CT = temp + arr[shortIndex].BT;
        arr[shortIndex].TAT = arr[shortIndex].CT - arr[shortIndex].AT;
        arr[shortIndex].WT = arr[shortIndex].TAT - arr[shortIndex].BT;
        arr[shortIndex].completed = 1;

        atat += arr[shortIndex].TAT;
        awt += arr[shortIndex].WT;
        temp = arr[shortIndex].CT;
        completed++;
    }

    // Desplay results
    printf("\nPNO\tAT\tBT\tPT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",arr[i].pNo, arr[i].AT, arr[i].BT, arr[i].priority, arr[i].CT, arr[i].TAT, arr[i].WT);
    }

    printf("ATAT: %.2f\n", (float)atat/n);
    printf("AWT: %.2f\n", (float)awt/n);
    
    return 0;
}