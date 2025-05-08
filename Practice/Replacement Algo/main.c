// Page replacement algorithm
#include <stdio.h>
#include <string.h>
#define MAX 100

void printFrames(int frames[], int frameSize, int isPageFault)
{
    int i;
    for (i = 0; i < frameSize; i++)
    {
        if (frames[i] == -1)
        {
            printf("- ");
        }
        else
        {
            printf("%d ", frames[i]);
        }
    }

    printf("%s\n", isPageFault ? "(Page Fault)" : "(Page Hit)");
}

int isPagePresent(int frames[], int frameSize, int page)
{
    int i;
    for (i = 0; i < frameSize; i++)
    {
        if (frames[i] == page)
        {
            return 1;
        }
    }
    return 0;
}

void fifo(int pages[], int pageSize, int frameSize)
{
    int frames[frameSize];
    int pointer = 0; // Replace page in a circular fashion
    int i, j;
    int pageFaults = 0, pageHits = 0;

    // Initialize frame as -1
    for (i = 0; i < frameSize; i++)
    {
        frames[i] = -1;
    }
    printf("\nFIFO Page Replacement:\n");

    for (i = 0; i < pageSize; i++)
    {
        printf("\nReference %d (page %d): ", i + 1, pages[i]);
        // Page fault?
        if (!isPagePresent(frames, frameSize, pages[i]))
        {
            frames[pointer] = pages[i];
            pointer = (pointer + 1) % frameSize;
            pageFaults++;
            printFrames(frames, frameSize, 1);
        }
        else
        {
            pageHits++;
            printFrames(frames, frameSize, 0);
        }
    }

    printf("\nPage Faults: %d\n", pageFaults);
    printf("Page Hits: %d\n", pageHits);
}

void lru(int pages[], int pageSize, int frameSize)
{
    int frames[frameSize];
    int counter[frameSize];
    int i, j;
    int pageFaults = 0, pageHits = 0;
    int time = 0;

    // Initialize Frame as -1 & counter as 0
    for (i = 0; i < frameSize; i++)
    {
        frames[i] = -1;
        counter[i] = 0;
    }
    printf("\nLRU Page Replacement:\n");

    for (i = 0; i < pageSize; i++)
    {
        printf("\nReference %d (Page %d): ", i + 1, pages[i]);
        time++;

        if (!isPagePresent(frames, frameSize, pages[i]))
        {
            int lruIndex = 0;
            // Find the least recently used page
            for (j = 1; j < frameSize; j++)
            {
                if (counter[j] < counter[lruIndex])
                {
                    lruIndex = j;
                }
            }

            frames[lruIndex] = pages[i];
            counter[lruIndex] = time;
            pageFaults++;
            printFrames(frames, frameSize, 1);
        }
        else
        {
            // Update counter for exisiting page
            for (j = 0; j < frameSize; j++)
            {
                if (frames[j] == pages[i])
                {
                    counter[j] = time;
                    break;
                }
            }
            pageHits++;
            printFrames(frames, frameSize, 0);
        }
    }

    printf("\nPage Faults: %d\n", pageFaults);
    printf("Page Hits: %d\n", pageHits);
}

void optimal(int pages[], int pageSize, int frameSize)
{
    int i, j, k;
    int pageFaults = 0, pageHits = 0;
    int frames[frameSize];

    for (i = 0; i < frameSize; i++)
    {
        frames[i] = -1;
    }

    printf("\nOptimal Page Replacement:\n");

    for (i = 0; i < pageSize; i++)
    {
        printf("\nReference %d (Page %d): ", i + 1, pages[i]);

        // Page present or not
        if (!isPagePresent(frames, frameSize, pages[i]))
        {
            int farPage = i;
            int index = 0;
            int found;

            for (j = 0; j < frameSize; j++)
            {
                found = 0;
                for (k = i + 1; k < pageSize; k++)
                {
                    if (frames[j] == pages[k])
                    {
                        if (farPage < k)
                        {
                            farPage = k;
                            index = j; // Page to replace with new page
                        }
                        found = 1;
                        break;
                    }
                }

                // If a page is never referenced again
                if (!found)
                {
                    index = j;
                    break;
                }
            }

            frames[index] = pages[i];
            pageFaults++;
            printFrames(frames, frameSize, 1);
        }
        else
        {
            pageHits++;
            printFrames(frames, frameSize, 0);
        }
    }

    printf("\nPage Faults: %d\n", pageFaults);
    printf("Page Hits: %d\n", pageHits);
}

void lfu(int pages[], int pageSize, int frameSize)
{
    int i, j;
    int pageFaults = 0, pageHits = 0;
    int frames[frameSize], freq[frameSize];

    // Initialize Frames as -1 and freq 0
    for (i = 0; i < frameSize; i++)
    {
        frames[i] = -1;
        freq[i] = 0;
    }

    printf("\nLFU Page Replacement:\n");

    for (int i = 0; i < pageSize; i++) {
        printf("Reference %d (Page %d): ", i + 1, pages[i]);
        
        if (!isPagePresent(frames, frameSize, pages[i])) {
            // Find the least frequently used page
            int lfuIndex = 0;
            for (int j = 1; j < frameSize; j++) {
                if (freq[j] < freq[lfuIndex]) {
                    lfuIndex = j;
                }
                // If frequencies are equal, use FIFO
                else if (freq[j] == freq[lfuIndex]) {
                    // We could add additional logic here for tie-breaking
                    // but keeping it simple by using the first found
                }
            }
            
            frames[lfuIndex] = pages[i];
            freq[lfuIndex] = 1; // New page gets freq 1
            pageFaults++;
            printFrames(frames, frameSize, 1);
        } else {
            // Update the freq for the existing page
            for (int j = 0; j < frameSize; j++) {
                if (frames[j] == pages[i]) {
                    freq[j]++;
                    break;
                }
            }
            pageHits++;
            printFrames(frames, frameSize, 0);
        }
    }
    printf("\nPage Faults: %d\n", pageFaults);
    printf("Page Hits: %d\n", pageHits);
}

int main()
{
    int pageSize, frameSize, i;
    int pages[MAX];

    printf("Enter the size of pages: ");
    scanf("%d", &pageSize);

    printf("Enter the page stream:\n");
    for (i = 0; i < pageSize; i++)
    {
        scanf("%d", &pages[i]);
    }

    printf("Enter the size of frame:");
    scanf("%d", &frameSize);

    fifo(pages, pageSize, frameSize);
    lru(pages, pageSize, frameSize);
    optimal(pages, pageSize, frameSize);
    lfu(pages, pageSize, frameSize);

    return 0;
}
