#include <stdio.h>

struct fcfs {
    int pNo;
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
};

void sort(struct fcfs arr[], int n) {
    struct fcfs temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) { 
            if (arr[i].AT > arr[j].AT) { 
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main() {
    int n, atat = 0, awt = 0, temp = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct fcfs arr[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        arr[i].pNo = i + 1; 
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &arr[i].AT);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &arr[i].BT);
    }

    sort(arr, n); // Sort by arrival time

    // Calculate Completion Time, Turnaround Time, and Waiting Time
    for (int i = 0; i < n; i++) {
        if (temp < arr[i].AT) { // CPU is idle
            printf("\nIdle time: %d -> %d\n", temp, arr[i].AT);
            temp = arr[i].AT; // Update current time
        }

        arr[i].CT = temp + arr[i].BT; // Compute Completion Time
        arr[i].TAT = arr[i].CT - arr[i].AT; // Turnaround Time
        arr[i].WT = arr[i].TAT - arr[i].BT; // Waiting Time

        atat += arr[i].TAT; // Accumulate Turnaround Time
        awt += arr[i].WT;   // Accumulate Waiting Time

        temp = arr[i].CT; // Update temp to latest Completion Time
    }

    // Display process details
    printf("\nProcess No\tArrival Time\tBurst Time\tCompletion Time\tTAT\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t%d\n",
               arr[i].pNo, arr[i].AT, arr[i].BT, arr[i].CT, arr[i].TAT, arr[i].WT);
    }

    // Display average times
    printf("\nAverage Turnaround Time: %.2f\n", (float)atat / n);
    printf("Average Waiting Time: %.2f\n", (float)awt / n);

    return 0;
}
