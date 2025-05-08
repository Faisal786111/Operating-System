// Banker's Algorithm

#include <stdio.h>

#define P 10
#define R 3
struct Banker{
    int pNo;
    int allocation[R];
    int maxNeed[R];
    int remainingNeed[R];
};

// RN = MX - AL
void calculateRemainingNeed(struct Banker process[], int n){
    int i, j;
    for(i = 0; i < n; i++){
        for(j = 0; j < R; j++){
            process[i].remainingNeed[j] = process[i].maxNeed[j] - process[i].allocation[j];
        }
    }
}

void calculateAvailable(struct Banker process[], int n, int available[]){
    int i, j, temp[R];

    for(i = 0; i < R; i++){
        temp[i] = available[i];
    }
    
    // Calc available matrix 
    for(i = 0; i < n; i++){
        for(j = 0; j < R; j++){
            temp[j] -= process[i].allocation[j];
        }
    }

    // Initial Available Matrix
    printf("\nAvailable Matrix Before Allocation:\n");
    for(i = 0; i < R; i++){
        printf("%d ", available[i]);
    }

    printf("\nAvailable Matrix After Allocation:\n");
    for(i = 0; i < R; i++){
        available[i] = temp[i];
        printf("%d ", available[i]);
    }
}

void printMatrices(struct Banker process[], int n, int available[]){
    printf("\nProcess\tAllocation\tMax Need\tRemaining Need\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t", process[i].pNo);
        for(int j = 0; j < R; j++) printf("%d ", process[i].allocation[j]);
        printf("\t\t");
        for(int j = 0; j < R; j++) printf("%d ", process[i].maxNeed[j]);
        printf("\t\t");
        for(int j = 0; j < R; j++) printf("%d ", process[i].remainingNeed[j]);
        printf("\n");
    }
    
    printf("\nAvailable Resources: ");
    for(int i = 0; i < R; i++) printf("%d ", available[i]);
    printf("\n");
}

int isSafeState(int safeSeq[], struct Banker process[], int n, int available[]){
    int finish[P] = {0}; // For tracking how many processes are finished 
    int completed = 0;
    int i, j;

    // Loop until all the processes are completed 
    while(completed < n){
        int found = 0; // To detect deadlocked process 
        for(i = 0; i < n; i++){
            if(!finish[i]){
                int canAllocate = 1;
                for(j = 0; j < R; j++){
                    if(process[i].remainingNeed[j] > available[j]){
                        canAllocate = 0;
                        break;
                    }
                }

                // If not then we can allocate the resources
                if(canAllocate){
                    for(j = 0; j < R; j++){
                        available[j] += process[i].allocation[j];
                    }

                    // Update Safe Seq, completion , finish & found
                    safeSeq[completed++] = process[i].pNo;
                    finish[i] = 1;
                    found = 1;
                } 
            }
        }

        if(!found){
            return 0; // There is a deadlock
        }
    }

    return 1; // There is no deadlock 
}

int main(){
    // Input no of processes
    int n = 5, i, safeSeq[n];

    // Input available matrix 
    int available[] = {10, 5, 7};

    // Input process details 
    struct Banker process[] = {
        {1, {0, 1, 0}, {7, 5, 3}, {0, 0, 0}},
        {2, {2, 0, 0}, {3, 2, 2}, {0, 0, 0}},
        {3, {3, 0, 2}, {9, 0, 2}, {0, 0, 0}},
        {4, {2, 1, 1}, {4, 2, 2}, {0, 0, 0}},
        {5, {0, 0, 2}, {5, 3, 3}, {0, 0, 0}},
    };

    // Calculate Remaining Need 
    calculateRemainingNeed(process, n);

    // Calculate Available Matrix 
    calculateAvailable(process, n, available);

    // Print matrices 
    printMatrices(process, n, available);

    // Check Safe or unsafe state
    printf("\nSafety Checking:\n");
    if(isSafeState(safeSeq, process, n, available)){
        printf("System is in the safe state.\n");
        printf("Sequence: \n");
        for(i = 0; i < n; i++){
            printf("P%d ", safeSeq[i]);
            if(i < n-1){
                printf("-> ");
            }
        }
    }else{
        printf("System is not in the safe state.\n");
    }

    return 0;
}