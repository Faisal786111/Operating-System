// FCFS algorithm
#include <stdio.h>

struct fcfs{
    int pNo;
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
};

void sort(struct fcfs arr[], int n){
    int i, j;
    struct fcfs temp;
    for(i = 0; i < n - 1; i++){
        for(j = i+1; j < n;j++){
            if(arr[j].AT < arr[i].AT){
                temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }
}



int main()
{
    int n, i, atat = 0, awt = 0, temp = 0;
    printf("Enter the no of processes: ");
    scanf("%d", &n);
    
    struct fcfs arr[n];
    
    printf("Enter the AT and BT For each processes: \n");
    for(i= 0; i < n; i++){
        arr[i].pNo = i+1;
        scanf("%d %d", &arr[i].AT, &arr[i].BT);
    }
    
    // Sort process as per their AT in increasing fashion 
    sort(arr, n);
    
    // Cacl CT, TAT, WT, ATAT, AWT 
    for(i = 0; i < n; i++){
        // handle idle time case 
        if(temp < arr[i].AT){
            printf("Idle time: %d -> %d", temp, arr[i].AT);
            temp = arr[i].AT;
        }
        
        arr[i].CT = temp + arr[i].BT;
        arr[i].TAT = arr[i].CT - arr[i].AT;
        arr[i].WT = arr[i].TAT - arr[i].BT;
        
        atat += arr[i].TAT;
        awt += arr[i].WT;
        
        temp = arr[i].CT;
    }
    
    printf("\nPNO\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               arr[i].pNo, arr[i].AT, arr[i].BT, arr[i].CT, arr[i].TAT, arr[i].WT);
    }

    printf("\nATAT: %.2f\n", (float)atat/n);
    printf("\nawt: %.2f\n", (float)awt/n);
    return 0;
}
