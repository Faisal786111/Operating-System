#include <stdio.h>
#include <stdbool.h>

#define P 10
#define R 3

// Create banker's structure
struct Process {
    int pNo;
    int allocation[R];
    int maxNeed[R];
    int remainingNeed[R];
};

// RN = MN - ALLOC
void calcRemainingNeed(struct Process p[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < R; j++) {
            p[i].remainingNeed[j] = p[i].maxNeed[j] - p[i].allocation[j];
        }
    }
}

void calcAvailableResource(struct Process p[], int available[], int n) {
    // Initialize available resources to the initial resources
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < R; j++) {
            available[j] -= p[i].allocation[j]; // Subtract the allocated resources from available
        }
    }

    // Print the remaining available resources
    printf("Available resources after allocation:\n");
    for (int i = 0; i < R; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");
}

bool isSafeState(int safeSeq[], struct Process p[], int available[], int n) {
    int count = 0;
    bool finish[n];  // To track finished processes
    for (int i = 0; i < n; i++) {
        finish[i] = false;
    }

    // Repeat until all processes are finished
    while (count < n) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            // Check if process is not finished and its remaining needs are less than or equal to available resources
            if (!finish[i]) {
                bool canAllocate = true;

                // Check if all the remaining needs are less than or equal to available resources
                for (int j = 0; j < R; j++) {
                    if (p[i].remainingNeed[j] > available[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                // If the process can be allocated, add its resources to the available pool
                if (canAllocate) {
                    // Add the allocated resources of process i to available
                    for (int j = 0; j < R; j++) {
                        available[j] += p[i].allocation[j];
                    }

                    // Add process number to the safe sequence
                    safeSeq[count++] = p[i].pNo;
                    finish[i] = true;
                    found = true;
                    break;
                }
            }
        }

        // If no process could be allocated, then the system is not in a safe state
        if (!found) {
            return false; // Not in a safe state
        }
    }

    return true; // Safe state
}

int main() {
    int n = 5;  // Number of processes

    // Initial available resources
    int available[] = {10, 5, 7};

    // Define processes with their allocation and max needs manually
    struct Process process[] = {
        {1, {0, 1, 0}, {7, 5, 3}, {0, 0, 0}},
        {2, {2, 0, 0}, {3, 2, 2}, {0, 0, 0}},
        {3, {3, 0, 2}, {9, 0, 2}, {0, 0, 0}},
        {4, {2, 1, 1}, {4, 2, 2}, {0, 0, 0}},
        {5, {0, 0, 2}, {5, 3, 3}, {0, 0, 0}},
    };

    // Calculate Remaining Need for each process
    calcRemainingNeed(process, n);

    // Calculate available resources after allocation
    calcAvailableResource(process, available, n);

    // Initialize the safe sequence array
    int safeSeq[n];

    // Check if the system is in a safe state
    if (isSafeState(safeSeq, process, available, n)) {
        printf("System is in a safe state.\nSafe Sequence: ");
        for (int i = 0; i < n; i++) {
            printf("P%d ", safeSeq[i]);
        }
        printf("\n");
    } else {
        printf("System is not in a safe state.\n");
    }

    return 0;
}
