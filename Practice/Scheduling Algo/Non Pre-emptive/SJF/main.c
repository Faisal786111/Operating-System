// SJF algorithm
#include <stdio.h>
#include <limits.h>

struct sjf{
    int pNo;
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
    int completed;
};

void sort(struct sjf arr[], int n){
    int i, j;
    struct sjf temp;
    for(i = 0; i < n - 1; i++){
        for(j = i+1; j < n;j++){
            if(arr[j].AT < arr[i].AT){
                temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }
}



int main()
{
    int n, i, atat = 0, awt = 0, temp = 0;
    printf("Enter the no of processes: ");
    scanf("%d", &n);
    
    struct sjf arr[n];
    
    printf("Enter the AT and BT For each processes: \n");
    for(i= 0; i < n; i++){
        arr[i].pNo = i+1;
        scanf("%d %d", &arr[i].AT, &arr[i].BT);
        arr[i].completed = 0;
    }
    
    // Sort process as per their AT in increasing fashion 
    sort(arr, n);
    
    int completed = 0;

    while(completed < n){
        // Identify process which is having min burst time
        int min = INT_MAX, shortIndex = -1;

        for(i = 0; i < n; i++){
            if(!arr[i].completed && arr[i].BT < min && arr[i].AT <= temp){
                min = arr[i].BT;
                shortIndex = i;
            }
        }

        // No process has arrived yet 
        if(shortIndex == -1){
            // Handle Idle time case 
            int nextArrival = INT_MAX;

            // Identify min arrival time process which are not completed
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

        // calc ct, tat, wt, atat, awt
        // process selected
        arr[shortIndex].CT = temp + arr[shortIndex].BT;
        arr[shortIndex].TAT = arr[shortIndex].CT - arr[shortIndex].AT;
        arr[shortIndex].WT = arr[shortIndex].TAT - arr[shortIndex].BT;
        arr[shortIndex].completed = 1;

        atat += arr[shortIndex].TAT;
        awt += arr[shortIndex].WT;
        temp = arr[shortIndex].CT;
        completed++;
    }

    printf("\nPNO\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               arr[i].pNo, arr[i].AT, arr[i].BT, arr[i].CT, arr[i].TAT, arr[i].WT);
    }

    printf("\nATAT: %.2f\n", (float)atat/n);
    printf("\nawt: %.2f\n", (float)awt/n);
    return 0;
}
