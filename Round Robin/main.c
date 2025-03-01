#include <stdio.h>
#include <stdbool.h>

#define Q_SIZE 1000

int Q[Q_SIZE], front = -1, rear = -1;

struct RR {
    int pNo;
    int AT;
    int BT;
    int original_BT;
    int CT;
    int TAT;
    int WT;
};

// Function to sort processes based on arrival time
void sort(struct RR arr[], int n) {
    struct RR temp;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i].AT > arr[j].AT) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

// Function to add a process to the queue
void Enqueue(int value) {
    if (rear == Q_SIZE - 1) {
        printf("\nQueue is full.");
        return;
    }
    if (front == -1) {
        front = 0;
    }
    rear++;
    Q[rear] = value;
}

// Function to remove a process from the queue
int Dequeue() {
    if (front == -1 || front > rear) {
        return -1; // Queue is empty
    }
    int x = Q[front];
    front++;
    return x;
}

// Function to check if the queue is empty
bool isEmpty() {
    return front == -1 || front > rear;
}

// Function to check if a process is already in the queue
bool contains(int value) {
    for (int i = front; i <= rear; i++) {
        if (Q[i] == value) {
            return true;
        }
    }
    return false;
}

int main() {
    int n, TQ, atat = 0, awt = 0, temp = 0;

    // Take Time Quantum
    printf("\nEnter the Time Quantum: ");
    scanf("%d", &TQ);

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct RR arr[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        arr[i].pNo = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &arr[i].AT);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &arr[i].BT);
        arr[i].original_BT = arr[i].BT; // Store original burst time
    }

    // Sort processes as per the arrival time
    sort(arr, n);

    // Initially add the first process to the queue
    Enqueue(0); // 0 index contains the first process

    // Process the queue
    while (!isEmpty()) {
        int i = Dequeue();

        // Handle idle time if no process is ready
        if (temp < arr[i].AT) {
            printf("\nIdle time: %d -> %d\n", temp, arr[i].AT);
            temp = arr[i].AT;
        }

        // Execute the process for the time quantum or its remaining burst time
        if (arr[i].BT <= TQ) {
            temp += arr[i].BT;
            arr[i].BT = 0; // Process finishes
            arr[i].CT = temp;
        } else {
            temp += TQ;
            arr[i].BT -= TQ;
        }

        // Add newly arrived processes to the queue
        for (int j = 0; j < n; j++) {
            if (arr[j].AT <= temp && arr[j].BT > 0 && !contains(j)) {
                Enqueue(j);
            }
        }

        // If the current process is not finished, add it back to the queue
        if (arr[i].BT > 0) {
            Enqueue(i);
        }
    }

    // Calculate TAT, WT, ATAT, and AWT
    for (int i = 0; i < n; i++) {
        arr[i].TAT = arr[i].CT - arr[i].AT;
        arr[i].WT = arr[i].TAT - arr[i].original_BT;

        atat += arr[i].TAT;
        awt += arr[i].WT;
    }

    // Print results
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", arr[i].pNo, arr[i].AT, arr[i].original_BT, arr[i].CT, arr[i].TAT, arr[i].WT);
    }

    printf("\nAverage Turnaround Time (ATAT): %.2f", (float)atat / n);
    printf("\nAverage Waiting Time (AWT): %.2f\n", (float)awt / n);

    return 0;
}