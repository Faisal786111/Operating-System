// Preemptive Priority Scheduling Algorithm
#include <stdio.h>
#include <limits.h>

struct priority{
    int pNo;
    int AT;
    int BT;
    int rem_bt;
    int priority;
    int CT;
    int TAT;
    int WT;
    int completed;
};

void sort(struct priority arr[], int n){
    int i, j;
    struct priority temp;

    for(i = 0; i < n-1; i++){
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
    int n, i, completed = 0, currentTime = 0, awt = 0, atat = 0;

    // input no of processes
    printf("Enter the no of processes: ");
    scanf("%d" , &n);

    struct priority arr[n];
    // inpurt process details 
    printf("Enter the AT, BT, & Priorty for each processes:\n");
    for(i = 0; i < n; i++){
        arr[i].pNo = i+1;
        scanf("%d %d %d", &arr[i].AT, &arr[i].BT, &arr[i].priority);
        arr[i].rem_bt = arr[i].BT;
        arr[i].completed = 0;
    }

    // Sort processes as per their arrival time in increasing fashion
    sort(arr, n);

    while(completed < n){
        // Identify highest priority process 
        int p = INT_MAX , shortIndex = -1;
        for(i = 0; i < n; i++){
            if(!arr[i].completed && arr[i].priority < p && arr[i].AT <= currentTime){
                p = arr[i].priority; 
                shortIndex = i;
            }
        }

        // if no process arrived yet
        if(shortIndex == -1){
            // handle idle time case 
            printf("\nIdle Time: %d -> %d\n", currentTime, currentTime + 1);
            currentTime++;
        }else{
            // process selected 
            // it will execute for 1 unit of time 
            arr[shortIndex].rem_bt--;
            currentTime++;

            // if process completed it's execution 
            if(arr[shortIndex].rem_bt == 0){
                // calc ct wt tat atat awt 
                arr[shortIndex].CT = currentTime;
                arr[shortIndex].TAT = arr[shortIndex].CT - arr[shortIndex].AT;
                arr[shortIndex].WT = arr[shortIndex].TAT - arr[shortIndex].BT;
                arr[shortIndex].completed = 1;

                atat += arr[shortIndex].TAT;
                awt += arr[shortIndex].WT;

                completed++;
            }
        }
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