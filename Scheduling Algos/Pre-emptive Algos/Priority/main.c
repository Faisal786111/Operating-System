#include <stdio.h>
#include <stdbool.h>

// Lesser number means higher priority
struct priority {
    int pNo;
    int AT;
    int BT;
    int remain_BT;
    int priority;
    int CT;
    int TAT;
    int WT;
    bool completed;
};

void sort(struct priority arr[], int n) {
    struct priority temp;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // Sort by arrival time
            if (arr[i].AT > arr[j].AT) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int findHighestPriority(struct priority arr[], int n, int currentTime) {
    int highestPriorityIndex = -1;
    int highestPriority = 9999; // Assuming lower number means higher priority

    for (int i = 0; i < n; i++) {
        if (!arr[i].completed && arr[i].AT <= currentTime && arr[i].priority < highestPriority) {
            highestPriority = arr[i].priority;
            highestPriorityIndex = i;
        }
    }

    return highestPriorityIndex;
}

int main() {
    int n, atat = 0, awt = 0, currentTime = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct priority arr[n];

    for (int i = 0; i < n; i++) {
        arr[i].pNo = i + 1;
        printf("Enter the AT, BT & Priority for process %d: ", i + 1);
        scanf("%d %d %d", &arr[i].AT, &arr[i].BT, &arr[i].priority);
        arr[i].remain_BT = arr[i].BT;
        arr[i].completed = false;
    }

    sort(arr, n);

    int completedProcesses = 0;
    while (completedProcesses < n) {
        int highestPriorityIndex = findHighestPriority(arr, n, currentTime);

        if (highestPriorityIndex == -1) {
            // No process available, CPU is idle
            printf("Idle time: %d -> %d\n", currentTime, currentTime + 1);
            currentTime++;
        } else {
            // Execute the process for 1 unit of time
            arr[highestPriorityIndex].remain_BT--;
            currentTime++;

            if (arr[highestPriorityIndex].remain_BT == 0) {
                // Process completed
                arr[highestPriorityIndex].completed = true;
                arr[highestPriorityIndex].CT = currentTime;
                arr[highestPriorityIndex].TAT = arr[highestPriorityIndex].CT - arr[highestPriorityIndex].AT;
                arr[highestPriorityIndex].WT = arr[highestPriorityIndex].TAT - arr[highestPriorityIndex].BT;

                atat += arr[highestPriorityIndex].TAT;
                awt += arr[highestPriorityIndex].WT;

                completedProcesses++;
            }
        }
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