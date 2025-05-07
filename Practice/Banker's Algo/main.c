// Banker's Algorithm 
#include <stdio.h>

#define P 10
#define R 3

struct banker{
    int pNo;
    int allocation[R];
    int maxNeed[R];
    int remainingNeed[R];
};

// RN = MN - A
void calculateRemainingNeed(struct banker process[], int n){
    int i, j;

    for(i = 0; i < n; i++){
        for(j = 0; j < R; j++){
            process[i].remainingNeed[j] = process[i].maxNeed[j] - process[i].allocation[j];
        }
    }
}

void calculateAvailableMatrix(struct banker process[], int n, int available[]){
    int temp[R];
    int i, j;
    for(i = 0; i < R; i++){
        temp[i] = available[i];
    }

    // calc available matrix 
    for(i = 0; i < n; i++){
        for(j = 0; j < R; j++){
            temp[j] -= process[i].allocation[j];
        }
    }

     printf("\nInitial Available Resources: ");
    for(int i = 0; i < R; i++) printf("%d ", available[i]);
    
    printf("\nAvailable after allocation: ");
    for (int i = 0; i < R; i++) {
        available[i] = temp[i];
        printf("%d ", available[i]);
    }
    printf("\n");
}

void printMatrices(struct banker process[], int n, int available[]){
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

int isSafeState(int safeSeq[], struct banker process[], int n, int available[]){
    int completed = 0, i, j;
    int finish[P] = {0};

    while(completed < n){
        int found = 0;

        for(i = 0; i < n; i++){
            if(!finish[i]){
                int canAllocate = 1;
                for(j = 0; j < R; j++){
                    if(process[i].remainingNeed[j] > available[j]){
                        canAllocate = 0;
                        break;
                    }
                }

                if(canAllocate){
                    for(j = 0; j < R; j++){
                        available[j] += process[i].allocation[j];
                    }

                    safeSeq[completed++] = process[i].pNo;
                    found = 1;
                    finish[i] = 1;
                }
            }
        }

        if(!found){
            return 0; // systen is in the unsafe state 
        }
    }

    return 1; // system is in the safe sate
}




int main(){
    int n = 5, i; // No of process 

    int available[R] = {10, 5, 7};

    // Input Banker's details 
    struct banker process[] = {
        {1, {0, 1, 0}, {7, 5, 3}, {0, 0, 0}},
        {2, {2, 0, 0}, {3, 2, 2}, {0, 0, 0}},
        {3, {3, 0, 2}, {9, 0, 2}, {0, 0, 0}},
        {4, {2, 1, 1}, {4, 2, 2}, {0, 0, 0}},
        {5, {0, 0, 2}, {5, 3, 3}, {0, 0, 0}},
    };

    // Calculate remaining need 
    calculateRemainingNeed(process, n);

    // Calculate available matrix 
    calculateAvailableMatrix(process, n, available);

    // Print matrix
    printMatrices(process, n, available);

    // Check Safe or Unsafe state
    int safeSeq[n];
    printf("\nSafety checking:\n");
    if(isSafeState(safeSeq, process, n, available)){
        printf("\nSystem is in the safe state\n");
        printf("\nSafe sequence is:\n");
        for(i = 0; i < n; i++){
            printf("P%d", safeSeq[i]);
            if(i < n-1){
                printf("->");
            }
        }
    }else {
        printf("\nSystem is in the unsafe state.\n");
    }
    return 0;
}