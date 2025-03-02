#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pNo, AT, BT, remain_BT, CT, TAT, WT;
    bool completed;
};

void sortProcessesByArrival(struct Process p[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].AT > p[j].AT) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int findShortestRemainingTime(struct Process p[], int n, int currentTime) {
    int shortestIndex = -1;
    int shortestTime = 9999; // A large number

    for (int i = 0; i < n; i++) {
        if (!p[i].completed && p[i].AT <= currentTime && p[i].remain_BT < shortestTime) {
            shortestTime = p[i].remain_BT;
            shortestIndex = i;
        }
    }

    return shortestIndex;
}

void srtfPreemptive(struct Process p[], int n) {
    int currentTime = 0, completedProcesses = 0;
    int totalTAT = 0, totalWT = 0;

    sortProcessesByArrival(p, n); // Sort processes by arrival time

    while (completedProcesses < n) {
        int shortestIndex = findShortestRemainingTime(p, n, currentTime);

        if (shortestIndex == -1) {
            // No process available, CPU is idle
            printf("Idle Time: %d -> %d\n", currentTime, currentTime + 1);
            currentTime++;
        } else {
            // Execute the process for 1 unit of time
            p[shortestIndex].remain_BT--;
            currentTime++;

            if (p[shortestIndex].remain_BT == 0) {
                // Process completed
                p[shortestIndex].completed = true;
                p[shortestIndex].CT = currentTime;
                p[shortestIndex].TAT = p[shortestIndex].CT - p[shortestIndex].AT;
                p[shortestIndex].WT = p[shortestIndex].TAT - p[shortestIndex].BT;

                totalTAT += p[shortestIndex].TAT;
                totalWT += p[shortestIndex].WT;

                completedProcesses++;
            }
        }
    }

    // Display results
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pNo, p[i].AT, p[i].BT, p[i].CT, p[i].TAT, p[i].WT);
    }

    printf("\nAverage Turnaround Time: %.2f\n", (float)totalTAT / n);
    printf("Average Waiting Time: %.2f\n", (float)totalWT / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pNo = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &p[i].AT, &p[i].BT);
        p[i].remain_BT = p[i].BT;
        p[i].completed = false;
    }

    srtfPreemptive(p, n);

    return 0;
}