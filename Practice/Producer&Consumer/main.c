// Producer & Consumer problem (Sequential case)

#include <stdio.h>

#define MAX 5

int buffer[MAX];
int itemCount = 0;

// Producer : produces the item 
void Producer(int item){
    // if buffer is full 
    if(itemCount >= MAX){
        printf("Buffer is full. More items cannot produce.\n");
        return;
    }
    buffer[itemCount++] = item;
    printf("Item Produced: %d\n", item);
}

// Consumer : consumer consumes the item
void Consumer(){
    // if buffere is empty 
    if(itemCount <= 0){
        printf("Buffere is full.\n");
    }
    int consumedItem = buffer[--itemCount];
    printf("Consumed Item: %d\n", consumedItem);
}

int main(){
    int i;
    for(i = 0; i < MAX; i++){
        Producer(i);
    }

    for(i = 0; i < MAX; i++){
        Consumer();
    }

    return 0;
}