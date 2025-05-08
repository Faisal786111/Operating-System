// Placement Algo

#include <stdio.h>
#include <limits.h>
#define MAX 100

// typedef gives a new name (Student in this case) to the structure type.
typedef struct {
    int pId;
    int size;
    int allocated;
    int remaining;
} MemoryBlock;

void displayResults(MemoryBlock parts[], int numParts, int processes[], int numProcesses){
    int i,j;
    printf("\nProcess Allocation:\n");

    for(i = 0; i < numParts; i++){
        if(parts[i].allocated){
            printf("Partitions %d (size %d): P%d (size %d)\n", i+1 , parts[i].size, parts[i].pId, processes[parts[i].pId-1]);

            // Handle hole case 
            if(parts[i].remaining > 0){
                printf("Hole created: %d \n", parts[i].remaining);

                int holeUsed = 0;

                for(j = 0; j < numProcesses; j++){
                    if(processes[j] <= parts[i].remaining && processes[j] != -1){
                        printf("hole used by P%d (size %d)\n", j+1, processes[j]);
                        holeUsed=1;
                    }
                }

                if(!holeUsed){
                    printf("Hole cannnot be used by any process\n");
                }
            }
        }else{
            printf("Partitions %d (size %d): Unallocated\n", i+1 , parts[i].size);
        }
    }
}   

void resetAllocation(MemoryBlock parts[], int numParts){
    int i;
    for(i = 0; i < numParts; i++){
        parts[i].pId = -1;
        parts[i].remaining = 0;
        parts[i].allocated = 0;
    }
}

// First fit: Allocate first memory block to the process which is large enough
void firstFit(MemoryBlock parts[], int numParts, int processes[], int numProcesses){
    int i, j;
    resetAllocation(parts, numParts);

    for(i = 0; i <numProcesses; i++){
        int allocated = 0;
        for(j = 0; j< numParts ; j++){
            if(!parts[j].allocated && parts[j].size >= processes[i]){
                // allocate process 
                parts[j].pId = i + 1;
                parts[j].allocated = 1;
                parts[j].remaining = parts[j].size - processes[i];
                // Print process size before setting it to -1
                allocated = 1;
                break;
            }
        }

        if(!allocated){
            printf("P%d (size %d) -> Unallocated\n", i+1, processes[i]);
        }
    }
    

    displayResults(parts, numParts, processes, numProcesses);
}

// Next fit: Allocate Next to last  allocated memory block to the process which is large enough
void nextFit(MemoryBlock parts[], int numParts, int processes[], int numProcesses){
    int i, j, lastAllocated = 0;
    resetAllocation(parts, numParts);

    for(i = 0; i < numProcesses; i++){
        int allocated = 0;
        for(j =0; j <numParts; j++){
            int index = (lastAllocated + j) %  numParts;

            if(!parts[index].allocated && parts[index].size >= processes[i]){
                // allocate process 
                parts[index].pId = i + 1;
                parts[index].allocated = 1;
                parts[index].remaining = parts[index].size - processes[i];
                lastAllocated = index;
                break; // exit the loop once the process is allocated
            }
        }
        if(!allocated){
             printf("P%d (size %d) -> Unallocated\n", i+1, processes[i]);
        }
    }

    displayResults(parts, numParts, processes, numProcesses);
}

// Best fit: Allocate Smallest Memory block to the process which satify the size of process
void bestFit(MemoryBlock parts[], int numParts, int processes[], int numProcesses){
    int i ,j;
    resetAllocation(parts, numParts);

    for(i = 0; i < numProcesses; i++){
        int min = INT_MAX, index = -1;

        // identify min size memory block 
        for(j = 0; j < numParts; j++){
            // idenitfy
            if(!parts[j].allocated && parts[j].size >= processes[i] && parts[j].size < min){
                min = parts[j].size;
                index = j;
            }
        }

        if(index != -1){
            parts[index].allocated = 1;
            parts[index].remaining = parts[index].size - processes[i];
            parts[index].pId = i +1;
        }else{
            printf("P%d (size %d) -> Unallocated\n", i+1, processes[i]);
        }

    }

    displayResults(parts, numParts, processes, numProcesses);
}

// Worst fit : Allocate largest memory block to the process which satisfy process  size
void worstFit(MemoryBlock parts[], int numParts, int processes[], int numProcesses){
    int i, j;
    resetAllocation(parts, numParts);

    for(i = 0; i < numProcesses; i++){
        int max = INT_MIN , index = -1;

        // Identify max memory block which can satisfy process size
        for(j = 0; j < numParts; j++){
            if(!parts[j].allocated && parts[j].size >= processes[i] && parts[j].size > max){
                max = parts[j].size;
                index = j;
            }
        }

        if(index != -1){
            parts[index].allocated = 1;
            parts[index].remaining = parts[index].size - processes[i];
            parts[index].pId = i +1;
        }else{
            printf("P%d (size %d) -> Unallocated\n", i+1, processes[i]);
        }

    }

    displayResults(parts, numParts, processes, numProcesses);
}


int main(){
    int numParts, numProcesses, i , j , choice;
    MemoryBlock parts[MAX];
    int processes[MAX];

    printf("Enter the no of partitions: ");
    scanf("%d", &numParts);

    printf("Enter the partitions size:\n");
    for(i = 0; i < numParts; i++){
        scanf("%d", &parts[i].size);
        parts[i].pId = -1;
        parts[i].remaining = 0;
        parts[i].allocated = 0;
    }

    printf("Enter the no of processes: ");
    scanf("%d", &numProcesses);

    printf("Enter the size of processes:\n");
    for(i = 0; i < numProcesses; i++){
        scanf("%d", &processes[i]);
    }

    // menu driven 
    while(1){
        printf("\nChoose Memory Allocation Algorithm:\n"
               "1. First Fit\n"
               "2. Best Fit\n"
               "3. Worst Fit\n"
               "4. Next Fit\n"
               "5. Exit\n"
               "Enter choice (1-5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n--- First Fit Allocation ---\n");
                firstFit(parts, numParts, processes, numProcesses);
                break;
            case 2:
                printf("\n--- Best Fit Allocation ---\n");
                bestFit(parts, numParts, processes, numProcesses);
                break;
            case 3:
                printf("\n--- Worst Fit Allocation ---\n");
                worstFit(parts, numParts, processes, numProcesses);
                break;
            case 4:
                printf("\n--- Next Fit Allocation ---\n");
                nextFit(parts, numParts, processes, numProcesses);
                break;
            case 5: 
                printf("\nExiting program...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}