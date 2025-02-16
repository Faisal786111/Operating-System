#include <stdio.h>

struct Process {
    int pNo, AT, BT, CT, TAT, WT;
};

void sortProcesses(struct Process p[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            // Sort based on Burst Time (if same, sort by Arrival Time)
            if ((p[i].BT > p[j].BT) || (p[i].BT == p[j].BT && p[i].AT > p[j].AT)) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void sjfNonPreemptive(struct Process p[], int n) {
    int temp = 0, totalTAT = 0, totalWT = 0;
    
    sortProcesses(p, n);  // Sort by burst time

    for (int i = 0; i < n; i++) {
        if (temp < p[i].AT) {
            printf("Idle Time: %d -> %d", temp , p[i].AT);
            temp = p[i].AT;  // CPU remains idle
        }
        p[i].CT = temp + p[i].BT;  // Completion Time
        p[i].TAT = p[i].CT - p[i].AT;  // Turnaround Time
        p[i].WT = p[i].TAT - p[i].BT;  // Waiting Time

        totalTAT += p[i].TAT;
        totalWT += p[i].WT;
        temp = p[i].CT;
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pNo, p[i].AT, p[i].BT, p[i].CT, p[i].TAT, p[i].WT);
    }

    printf("\nAverage Turnaround Time: %.2f", (float)totalTAT / n);
    printf("\nAverage Waiting Time: %.2f\n", (float)totalWT / n);
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
    }
    
    sjfNonPreemptive(p, n);

    return 0;
}
