#include <stdio.h>

// Lesser no higher priority
struct priority{
    int pNo;
    int AT;
    int BT;
    int priority;
    int CT;
    int TAT;
    int WT;
};

void sort(struct priority arr[], int n){
    struct priority temp;
    for(int i =0 ; i < n ; i++){
        for(int j = i + 1; j < n ; j++){
            // Sort as per the priority and AT
            if(arr[i].priority > arr[j].priority || (arr[i].priority == arr[j].priority && arr[i].AT >arr[j].AT)){
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main(){
    int n, atat = 0, awt = 0 , temp = 0;

    printf("Enter the no of process:");
    scanf("%d", &n);
    struct priority arr[n];

    for(int i = 0 ; i < n ; i++){
        arr[i].pNo = i+1;
        printf("Enter the AT, BT & Priority for the process %d: ", i+1);
        scanf("%d %d %d", &arr[i].AT, &arr[i].BT, &arr[i].priority);
    }

    sort(arr, n);

    // Calculate CT, TAT, WT, ATAT & AWt
    for(int i = 0 ; i < n ; i++){
        // Handle idle time 
        if(temp < arr[i].AT){
            printf("Idle time: %d -> %d\n", temp, arr[i].AT);
            temp = arr[i].AT;
        }

        arr[i].CT = temp + arr[i].BT;
        arr[i].TAT = arr[i].CT - arr[i].AT;
        arr[i].WT = arr[i].TAT - arr[i].BT;
        temp = arr[i].CT;

        atat += arr[i].TAT;
        awt += arr[i].WT;
    }

    // Display results
    printf("\nProcess No\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTAT\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t%d\n",
               arr[i].pNo, arr[i].AT, arr[i].BT, arr[i].priority, arr[i].CT, arr[i].TAT, arr[i].WT);
    }

    // Display average times
    printf("\nAverage Turnaround Time: %.2f\n", (float)atat / n);
    printf("Average Waiting Time: %.2f\n", (float)awt / n);

    return 0;
}