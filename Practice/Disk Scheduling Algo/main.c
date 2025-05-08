#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

// Fifo: Accept req as a serial manner 
void fifo(int n, int req[], int head){
    int i, movement = 0;
    int current = head;
    
    printf("\nFIFO Algorithm\n");
    printf("Movement sequence: %d", head);
    
    for(i = 0; i < n; i++){
        printf(" -> %d", req[i]);
        movement += abs(current - req[i]);
        current = req[i];
    }
    
    printf("\nSeek Time: %d\n", movement);
}

// SSTF: Identify nearest shortest seektime and move head towards that seek time 
void sstf(int n, int req[], int head){
    int i,j, movement= 0;
    int current = head;
    int completed[n];
    
    for(i = 0; i < n; i++){
        completed[i] = 0;
    }
    
    printf("\nSSTF Algorithm\n");
    printf("Head movement seq: %d", head);
    
    for(i = 0; i <n; i++){
        int min = INT_MAX;
        int index = -1;
        
        // Identify nearest shortest seek time and move head towards that
        for(j = 0; j < n; j++){
            if(!completed[j]){
                int dist = abs(current - req[j]);
                
                if(dist < min){
                    min = dist;
                    index = j;
                }
            }   
        }
        
        printf("-> %d", req[index]);
        movement += min;
        current = req[index];
        completed[index] = 1;
    }
    
    printf("\nSeek time: %d\n", movement);
}

// SCAN (Elevator): As per the direction head will and it also include maxNo track 
void scan(int n, int req[], int head, int maxNo, int direction){
    int i, j, movement = 0, temp;
    int current = head;
    
    printf("\nSCAN Algorithm\n");
    printf("Head movement seq: %d", head);
    
    // Sort req as ascending order
    for(i = 0; i < n - 1; i++){
        for(j = i+1; j < n; j++){
            if(req[j] < req[i]){
                temp = req[j];
                req[j] = req[i];
                req[i] = temp;
            }
        }
    }
    
    // Right side 
    if(direction == 1){
        // Move heads towards largest tracks greater than current head 
        for(i = 0; i < n; i++){
            if(req[i] >= current){
                printf(" -> %d", req[i]);
                movement += abs(current - req[i]);
                current = req[i];
            }
        }
        
        // Include max track no 
        printf(" -> %d", maxNo);
        movement += abs(current - maxNo);
        current = maxNo;
        
        // Move head towards the lowest tracks than Original head
        for(i = n-1; i >=0;i--){
            if(req[i] < head){
                printf(" -> %d", req[i]);
                movement += abs(current - req[i]);
                current = req[i];
            }
        }
        
        
    }
    // left side
    else{
        // Move heads towards lowest tracks  than current head 
        for(i = n-1; i >=0;i--){
            if(req[i] <= current){
                printf(" -> %d", req[i]);
                movement += abs(current - req[i]);
                current = req[i];
            }
        }
        
        // Accept 0th track 
        printf(" -> 0");
        movement += abs(current - 0);
        current = 0;
        
        // Move heads towards the greater tracks than Original head 
        for(i = 0; i < n; i++){
            if(req[i] > head){
                printf(" -> %d", req[i]);
                movement += abs(current - req[i]);
                current = req[i];
            }
        }
    }
    printf("\nSeek time: %d", movement);
}


// Look: It doesn't include last track and move head as per the direction 
void look(int n, int req[], int head, int maxNo, int direction){
    int i, j, movement = 0;
    int current = head, temp;
    
    printf("\nLOOK Algorithm\n");
    printf("Head movement seq: %d", head);
    
    // Sort req as ascending
    for(i = 0; i < n-1; i++){
        for(j = i + 1; j < n; j++){
            if(req[j] < req[i]){
                temp= req[j];
                req[j]= req[i];
                req[i] =temp;
            }
        }
    }
    
    // right 
    if(direction == 1){
        // Move heads towards that largest tracks than current head 
        for(i = 0; i < n; i++){
            if(req[i] >= current){
                printf(" -> %d", req[i]);
                movement += abs(current - req[i]);
                current = req[i];
            }   
        }
        
        // Now move head towards the smallest tracks than Original head
        for(i = n-1; i >= 0; i--){
            if(req[i] < head){
                printf("-> %d", req[i]);
                movement += abs(current - req[i]);
                current = req[i];
            }
        }
    }   
    // left 
    else{
        // Move heads towareds the lowest tracks than current head 
        for(i = n-1; i >= 0; i--){
            if(req[i] <= current){
                printf(" -> %d", req[i]);
                movement += abs(current - req[i]);
                current = req[i];
            }
        }
        
        // Now move heads towards the largest tracks than original head 
        for(i = 0; i < n ;i++){
            if(req[i] > head){
                printf("-> %d", req[i]);
                movement += abs(current - req[i]);
                current = req[i];
            }
        }
    }
    
    printf("\nSeek time: %d", movement);
}


// cscan: Move heads as per the direction and include last tracks too after that it will move to starting track(0) without accepting any req and then move heads as per the direction 
void cscan(int n, int req[], int head, int maxNo, int direction){
    int i, j, movement = 0;
    int current = head, temp;
      
    printf("\nCSCAN Algorithm\n");
    printf("Head movement seq: %d", head);
    // Sort req as ascending
    for(i = 0; i < n-1; i++){
        for(j = i + 1; j < n; j++){
            if(req[j] < req[i]){
                temp= req[j];
                req[j]= req[i];
                req[i] =temp;
            }
        }
    }
    
    // right 
    if(direction == 1){
        // Move heads towards largest tracks greater than current head 
        for(i = 0; i < n; i++){
            if(req[i] >= current){
                printf(" -> %d", req[i]);
                movement += abs(current - req[i]);
                current = req[i];
            }
        }
        
        // Include max track no 
        printf(" -> %d", maxNo);
        movement += abs(current - maxNo);
        current = maxNo;
        
        // Now move head to the starting track(0)
        printf(" -> 0");
        movement += abs(current - 0);
        current = 0;
        
        // Move head towards the lowest tracks than Original head
        for(i = 0; i < n;i++){
            if(req[i] < head){
                printf(" -> %d", req[i]);
                movement += abs(current - req[i]);
                current = req[i];
            }
        }
    }
    //left 
    else{
     // Move heads towards lowest tracks  than current head 
        for(i = n-1; i >=0;i--){
            if(req[i] <= current){
                printf(" -> %d", req[i]);
                movement += abs(current - req[i]);
                current = req[i];
            }
        }
        
        // Accept 0th track 
        printf(" -> 0");
        movement += abs(current - 0);
        current = 0;
        
        // Move heads to starting track(maxNo)
        printf(" -> %d", maxNo);
        movement += abs(current - maxNo);
        current = maxNo;
        
        // Move heads towards the greater tracks than Original head 
        for(i = 0; i < n; i++){
            if(req[i] > head){
                printf(" -> %d", req[i]);
                movement += abs(current - req[i]);
                current = req[i];
            }
        }
    }
    printf("\nSeek time: %d", movement);
}

// CLook: It doesn't include last track and move head as per the direction after reaching the last req then it move to the starting req without accepting any req 
void clook(int n, int req[], int head, int maxNo, int direction){
    int i, j, movement = 0;
    int current = head, temp;
    
    printf("\nCLOOK Algorithm\n");
    printf("Head movement seq: %d", head);
    
    // Sort req as ascending
    for(i = 0; i < n-1; i++){
        for(j = i + 1; j < n; j++){
            if(req[j] < req[i]){
                temp= req[j];
                req[j]= req[i];
                req[i] =temp;
            }
        }
    }
    
    // right 
    if(direction == 1){
        // Move heads towards that largest tracks than current head 
        for(i = 0; i < n; i++){
            if(req[i] >= current){
                printf(" -> %d", req[i]);
                movement += abs(current - req[i]);
                current = req[i];
            }   
        }
        
        // Move Starting req 
        movement += abs(current - req[0]);
        current = req[0];
        
        // Now move head towards the smallest tracks than Original head
        for(i = 0; i < n; i++){
            if(req[i] < head){
                printf("-> %d", req[i]);
                movement += abs(current - req[i]);
                current = req[i];
            }
        }
    }   
    // left 
    else{
        // Move heads towareds the lowest tracks than current head 
        for(i = n-1; i >= 0; i--){
            if(req[i] <= current){
                printf(" -> %d", req[i]);
                movement += abs(current - req[i]);
                current = req[i];
            }
        }
        
        // Now move ending req 
        movement += abs(current - req[n-1]);
        current = req[n-1];
        
        // Now move heads towards the largest tracks than original head 
        for(i = n; i >= 0 ;i--){
            if(req[i] > head){
                printf("-> %d", req[i]);
                movement += abs(current - req[i]);
                current = req[i];
            }
        }
    }
    
    printf("\nSeek time: %d", movement);
}



int main()
{
    int n , req[MAX], head, maxNo, i, direction;
    
    printf("Enter the size of the tracks: ");
    scanf("%d", &n);
    
    printf("Enter no of track req:\n");
    for(i = 0 ;i <n; i++){
        scanf("%d", &req[i]);
    }
    
    printf("Enter the current head: ");
    scanf("%d", &head);
    
    printf("Enter max track no: ");
    scanf("%d", &maxNo);
    
    // fifo(n, req, head);
    // sstf(n, req, head);
    printf("Enter the direction 0(left) , 1(right)");
    scanf("%d", &direction);
    
    // scan(n, req, head, maxNo, direction);
    
    // look(n, req,head, maxNo, direction);
    //  cscan(n, req,head, maxNo, direction);
    clook(n, req,head, maxNo, direction);
    
    return 0;
}