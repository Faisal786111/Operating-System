#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// Function to find if a page exists in frames
bool isPagePresent(int frames[], int n, int page) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

// Function to print the frames
void printFrames(int frames[], int n, bool isPageFault) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1) {
            printf("- ");
        } else {
            printf("%d ", frames[i]);
        }
    }
    printf("%s\n", isPageFault ? "(Page Fault)" : "(Page Hit)");
}

// FIFO Page Replacement Algorithm
void fifo(int pages[], int n, int frameCount) {
    int frames[frameCount];
    int pageFaults = 0, pageHits = 0;
    int pointer = 0; // Points to the next frame to be replaced
    
    // Initialize frames as empty
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
    }
    
    printf("\nFIFO Page Replacement:\n");
    
    for (int i = 0; i < n; i++) {
        printf("Reference %d (Page %d): ", i + 1, pages[i]);
        
        if (!isPagePresent(frames, frameCount, pages[i])) {
            frames[pointer] = pages[i];
            pointer = (pointer + 1) % frameCount;
            pageFaults++;
            printFrames(frames, frameCount, true);
        } else {
            pageHits++;
            printFrames(frames, frameCount, false);
        }
    }
    
    printf("Total Page Faults: %d\n", pageFaults);
    printf("Total Page Hits: %d\n", pageHits);
}

// LRU Page Replacement Algorithm
void lru(int pages[], int n, int frameCount) {
    int frames[frameCount];
    int counter[frameCount]; // To store the time when each page was last used
    int pageFaults = 0, pageHits = 0;
    int time = 0;
    
    // Initialize frames as empty and counters to 0
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
        counter[i] = 0;
    }
    
    printf("\nLRU Page Replacement:\n");
    
    for (int i = 0; i < n; i++) {
        time++;
        printf("Reference %d (Page %d): ", i + 1, pages[i]);
        
        if (!isPagePresent(frames, frameCount, pages[i])) {
            // Find the least recently used page
            int lruIndex = 0;
            for (int j = 1; j < frameCount; j++) {
                if (counter[j] < counter[lruIndex]) {
                    lruIndex = j;
                }
            }
            
            frames[lruIndex] = pages[i];
            counter[lruIndex] = time;
            pageFaults++;
            printFrames(frames, frameCount, true);
        } else {
            // Update the counter for the existing page
            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == pages[i]) {
                    counter[j] = time;
                    break;
                }
            }
            pageHits++;
            printFrames(frames, frameCount, false);
        }
    }
    
    printf("Total Page Faults: %d\n", pageFaults);
    printf("Total Page Hits: %d\n", pageHits);
}

// Optimal Page Replacement Algorithm
void optimal(int pages[], int n, int frameCount) {
    int frames[frameCount];
    int pageFaults = 0, pageHits = 0;
    
    // Initialize frames as empty
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
    }
    
    printf("\nOptimal Page Replacement:\n");
    
    for (int i = 0; i < n; i++) {
        printf("Reference %d (Page %d): ", i + 1, pages[i]);
        
        if (!isPagePresent(frames, frameCount, pages[i])) {
            // Find the page that won't be used for the longest time
            int farthest = i;
            int replaceIndex = 0;
            bool found;
            
            for (int j = 0; j < frameCount; j++) {
                found = false;
                for (int k = i + 1; k < n; k++) {
                    if (frames[j] == pages[k]) {
                        if (k > farthest) {
                            farthest = k;
                            replaceIndex = j;
                        }
                        found = true;
                        break;
                    }
                }
                // If a page is never referenced again, replace it
                if (!found) {
                    replaceIndex = j;
                    break;
                }
            }
            
            frames[replaceIndex] = pages[i];
            pageFaults++;
            printFrames(frames, frameCount, true);
        } else {
            pageHits++;
            printFrames(frames, frameCount, false);
        }
    }
    
    printf("Total Page Faults: %d\n", pageFaults);
    printf("Total Page Hits: %d\n", pageHits);
}

// LFU (Least Frequently Used) Page Replacement Algorithm
void lfu(int pages[], int n, int frameCount) {
    int frames[frameCount];
    int frequency[frameCount]; // To store frequency counts
    int pageFaults = 0, pageHits = 0;
    
    // Initialize frames as empty and frequencies to 0
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
        frequency[i] = 0;
    }
    
    printf("\nLFU Page Replacement:\n");
    
    for (int i = 0; i < n; i++) {
        printf("Reference %d (Page %d): ", i + 1, pages[i]);
        
        if (!isPagePresent(frames, frameCount, pages[i])) {
            // Find the least frequently used page
            int lfuIndex = 0;
            for (int j = 1; j < frameCount; j++) {
                if (frequency[j] < frequency[lfuIndex]) {
                    lfuIndex = j;
                }
                // If frequencies are equal, use FIFO
                else if (frequency[j] == frequency[lfuIndex]) {
                    // We could add additional logic here for tie-breaking
                    // but keeping it simple by using the first found
                }
            }
            
            frames[lfuIndex] = pages[i];
            frequency[lfuIndex] = 1; // New page gets frequency 1
            pageFaults++;
            printFrames(frames, frameCount, true);
        } else {
            // Update the frequency for the existing page
            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == pages[i]) {
                    frequency[j]++;
                    break;
                }
            }
            pageHits++;
            printFrames(frames, frameCount, false);
        }
    }
    
    printf("Total Page Faults: %d\n", pageFaults);
    printf("Total Page Hits: %d\n", pageHits);
}

int main() {
    int n, frameCount;
    
    printf("Enter the number of pages: ");
    scanf("%d", &n);
    
    int pages[n];
    printf("Enter the page reference sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    
    printf("Enter the number of frames: ");
    scanf("%d", &frameCount);
    
    // Run all four algorithms
    fifo(pages, n, frameCount);
    lru(pages, n, frameCount);
    optimal(pages, n, frameCount);
    lfu(pages, n, frameCount);
    
    return 0;
}