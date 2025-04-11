#include <stdio.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int item_count = 0; // Tracks how many items are in the buffer

// Producer: Adds items to the buffer
void produce(int item) {
    if (item_count >= BUFFER_SIZE) {
        printf("Buffer full! Cannot produce.\n");
        return;
    }
    buffer[item_count++] = item;
    printf("Produced: %d\n", item);
}

// Consumer: Removes and processes items from the buffer
int consume() {
    if (item_count <= 0) {
        printf("Buffer empty! Cannot consume.\n");
        return -1; // Error: No item to consume
    }
    int item = buffer[--item_count];
    printf("Consumed: %d\n", item);
    return item;
}

int main() {
    // Producer adds items
    for (int i = 1; i <= 5; i++) {
        produce(i);
    }

    // Consumer takes items
    while (item_count > 0) {
        consume();
    }

    return 0;
}