#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

void fifo(int requests[], int n, int head) {
    printf("\nFIFO (FCFS) Disk Scheduling:\n");
    printf("Head movement sequence: %d", head);
    int total_movement = 0;
    int current = head;
    
    for (int i = 0; i < n; i++) {
        printf(" -> %d", requests[i]);
        total_movement += abs(requests[i] - current);
        current = requests[i];
    }
    
    printf("\nTotal head movement: %d cylinders\n", total_movement);
}

void sstf(int requests[], int n, int head) {
    printf("\nSSTF Disk Scheduling:\n");
    printf("Head movement sequence: %d", head);
    int total_movement = 0;
    int current = head;
    bool completed[n];
    
    for (int i = 0; i < n; i++) {
        completed[i] = false;
    }
    
    for (int i = 0; i < n; i++) {
        int min_dist = INT_MAX;
        int min_index = -1;
        
        for (int j = 0; j < n; j++) {
            if (!completed[j]) {
                int dist = abs(requests[j] - current);
                if (dist < min_dist) {
                    min_dist = dist;
                    min_index = j;
                }
            }
        }
        
        printf(" -> %d", requests[min_index]);
        total_movement += min_dist;
        current = requests[min_index];
        completed[min_index] = true;
    }
    
    printf("\nTotal head movement: %d cylinders\n", total_movement);
}

void scan(int requests[], int n, int head, int max_cylinder, int direction) {
    printf("\nSCAN Disk Scheduling:\n");
    printf("Head movement sequence: %d", head);
    int total_movement = 0;
    int current = head;
    
    // Sort requests
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (requests[j] > requests[j+1]) {
                int temp = requests[j];
                requests[j] = requests[j+1];
                requests[j+1] = temp;
            }
        }
    }
    
    if (direction == 1) { // Moving towards higher cylinders
        // Requests larger than current head position
        for (int i = 0; i < n; i++) {
            if (requests[i] >= current) {
                printf(" -> %d", requests[i]);
                total_movement += abs(requests[i] - current);
                current = requests[i];
            }
        }
        // Go to end
        printf(" -> %d", max_cylinder);
        total_movement += abs(max_cylinder - current);
        current = max_cylinder;
        // Requests smaller than original head position (reverse direction)
        for (int i = n-1; i >= 0; i--) {
            if (requests[i] < head) {
                printf(" -> %d", requests[i]);
                total_movement += abs(requests[i] - current);
                current = requests[i];
            }
        }
    } else { // Moving towards lower cylinders
        // Requests smaller than current head position
        for (int i = n-1; i >= 0; i--) {
            if (requests[i] <= current) {
                printf(" -> %d", requests[i]);
                total_movement += abs(requests[i] - current);
                current = requests[i];
            }
        }
        // Go to start
        printf(" -> 0");
        total_movement += abs(0 - current);
        current = 0;
        // Requests larger than original head position (reverse direction)
        for (int i = 0; i < n; i++) {
            if (requests[i] > head) {
                printf(" -> %d", requests[i]);
                total_movement += abs(requests[i] - current);
                current = requests[i];
            }
        }
    }
    
    printf("\nTotal head movement: %d cylinders\n", total_movement);
}

void cscan(int requests[], int n, int head, int max_cylinder) {
    printf("\nC-SCAN Disk Scheduling:\n");
    printf("Head movement sequence: %d", head);
    int total_movement = 0;
    int current = head;
    
    // Sort requests
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (requests[j] > requests[j+1]) {
                int temp = requests[j];
                requests[j] = requests[j+1];
                requests[j+1] = temp;
            }
        }
    }
    
    // Requests larger than current head position
    for (int i = 0; i < n; i++) {
        if (requests[i] >= current) {
            printf(" -> %d", requests[i]);
            total_movement += abs(requests[i] - current);
            current = requests[i];
        }
    }
    // Go to end and then to start
    printf(" -> %d -> 0", max_cylinder);
    total_movement += abs(max_cylinder - current) + max_cylinder;
    current = 0;
    // Requests smaller than original head position
    for (int i = 0; i < n; i++) {
        if (requests[i] < head) {
            printf(" -> %d", requests[i]);
            total_movement += abs(requests[i] - current);
            current = requests[i];
        }
    }
    
    printf("\nTotal head movement: %d cylinders\n", total_movement);
}

void look(int requests[], int n, int head, int direction) {
    printf("\nLOOK Disk Scheduling:\n");
    printf("Head movement sequence: %d", head);
    int total_movement = 0;
    int current = head;
    
    // Sort requests
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (requests[j] > requests[j+1]) {
                int temp = requests[j];
                requests[j] = requests[j+1];
                requests[j+1] = temp;
            }
        }
    }
    
    if (direction == 1) { // Moving towards higher cylinders
        // Requests larger than current head position
        for (int i = 0; i < n; i++) {
            if (requests[i] >= current) {
                printf(" -> %d", requests[i]);
                total_movement += abs(requests[i] - current);
                current = requests[i];
            }
        }
        // Requests smaller than original head position (reverse direction)
        for (int i = n-1; i >= 0; i--) {
            if (requests[i] < head) {
                printf(" -> %d", requests[i]);
                total_movement += abs(requests[i] - current);
                current = requests[i];
            }
        }
    } else { // Moving towards lower cylinders
        // Requests smaller than current head position
        for (int i = n-1; i >= 0; i--) {
            if (requests[i] <= current) {
                printf(" -> %d", requests[i]);
                total_movement += abs(requests[i] - current);
                current = requests[i];
            }
        }
        // Requests larger than original head position (reverse direction)
        for (int i = 0; i < n; i++) {
            if (requests[i] > head) {
                printf(" -> %d", requests[i]);
                total_movement += abs(requests[i] - current);
                current = requests[i];
            }
        }
    }
    
    printf("\nTotal head movement: %d cylinders\n", total_movement);
}

void clook(int requests[], int n, int head) {
    printf("\nC-LOOK Disk Scheduling:\n");
    printf("Head movement sequence: %d", head);
    int total_movement = 0;
    int current = head;
    
    // Sort requests
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (requests[j] > requests[j+1]) {
                int temp = requests[j];
                requests[j] = requests[j+1];
                requests[j+1] = temp;
            }
        }
    }
    
    // Requests larger than current head position
    for (int i = 0; i < n; i++) {
        if (requests[i] >= current) {
            printf(" -> %d", requests[i]);
            total_movement += abs(requests[i] - current);
            current = requests[i];
        }
    }
    // Jump to smallest request
    int smallest = requests[0];
    printf(" -> %d", smallest);
    total_movement += abs(current - smallest);
    current = smallest;
    // Continue with remaining requests
    for (int i = 0; i < n; i++) {
        if (requests[i] < head && requests[i] >= smallest) {
            printf(" -> %d", requests[i]);
            total_movement += abs(requests[i] - current);
            current = requests[i];
        }
    }
    
    printf("\nTotal head movement: %d cylinders\n", total_movement);
}

int main() {
    int n, head, max_cylinder, direction;
    int *requests;
    
    printf("Enter number of disk requests: ");
    scanf("%d", &n);
    
    requests = (int *)malloc(n * sizeof(int));
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    
    printf("Enter initial head position: ");
    scanf("%d", &head);
    
    printf("Enter maximum cylinder number: ");
    scanf("%d", &max_cylinder);
    
    int choice;
    do {
        printf("\nDisk Scheduling Algorithms\n");
        printf("1. FIFO (FCFS)\n");
        printf("2. SSTF\n");
        printf("3. SCAN\n");
        printf("4. C-SCAN\n");
        printf("5. LOOK\n");
        printf("6. C-LOOK\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                fifo(requests, n, head);
                break;
            case 2:
                sstf(requests, n, head);
                break;
            case 3:
                printf("Enter direction (0 for decreasing, 1 for increasing): ");
                scanf("%d", &direction);
                scan(requests, n, head, max_cylinder, direction);
                break;
            case 4:
                cscan(requests, n, head, max_cylinder);
                break;
            case 5:
                printf("Enter direction (0 for decreasing, 1 for increasing): ");
                scanf("%d", &direction);
                look(requests, n, head, direction);
                break;
            case 6:
                clook(requests, n, head);
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 7);
    
    free(requests);
    return 0;
}