#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Jack Sweeney 4/5/23
// OS Concepts

//Macros Global Consts
#define EXIT  0
#define INVALID -1
#define MEMORY 1
#define FILES 2
#define THREAD 3
#define FIRST 0
#define BEST 1
#define WORST 2
#define NEXT 3
//Page Replacement
#define PAGE 4
#define FIFO 0
#define LRU 1
#define FRAMES 3


//Prototypes
int displayMenu();
void clearScreen();
void clearScreen();
void memoryManagement();
void firstFit(int blockSize[], int blocks, int processSize[], int processes);
void bestFit(int blockSize[], int blocks, int processSize[], int processes);
void worstFit(int blockSize[], int blocks, int processSize[], int processes);
void nextFit(int blockSize[], int blocks, int processSize[], int processes);
void displayProcess(int allocation[], int processes, int processSize[]);
//New Prototypes for Page Replacement
void displayPages(int, int[]);
void lru();
int findLRU(int time[]);
void pageReplacement();
void fifo();

int displayMenu(){
    int choice = -1;
    printf(" \nSelect the OS program to run, enter a selection\n");
    printf("1. Memory Management\n");
    printf("2. File Management\n");
    printf("3. Multithreading\n");
    printf("4. Page Replacement\n"); // added option for page replacement
    printf("0. Exit\n");
    scanf("%d", &choice);
    if (choice < 0 || choice > 4) choice = -1; // updated validation for new option
    return choice;
}
//Clear screen function
void clearScreen(){
    fflush(stdin);
    char inp;
    printf("Hit enter to move onto next screen");
    while (inp != '\n'){
            scanf("%c", &inp);
    }
    system("cls");
    //system("clear");
}
//Displays the pages in a table, right aligned, one row at a time
void displayPages(int pages, int allocation[]) {
    printf("\t%4d\t", pages);
    for (int i = 0; i < FRAMES; i++) {
        if (allocation[i] == -1) {
            printf("%7s\t", "-");
        } else {
            printf("%7d\t", allocation[i]);
        }
    }
    printf("\n");
}
// Core of lru algorithm used in the lru implementation function
int findLRU(int time[]) {
    int position = 0;
    int minimum = time[0];
    // Iterated to find oldest
    for (int i = 1; i < FRAMES; i++) {
        if (time[i] < minimum) {
            minimum = time[i];
            position = i;
        }
    }
    //Returning index of oldest
    return position;
}
// Implements the Least Recently used algo
void lru() {
    printf("\n\n  ********** Least Recently Used **********\n\n");
    printf("\tPage\t");
    for (int i = 0; i < FRAMES; i++) {
        printf("Frame %d\t", i+1);
    }
    printf("\n");

    int pageRequests[] = {4, 1,2, 4, 2, 5, 1, 3, 6};
    int pageFaults = 0;
    int allocation[FRAMES];
    int pages = sizeof(pageRequests) / sizeof(pageRequests[0]);
    int counter = 0;
    int time[FRAMES];
    int flag1, flag2;
    int position = 0;

    memset(allocation, INVALID, sizeof(allocation));

    //Iterate pages
    for (int i = 0; i < pages; i++) {
        flag1 = 0;
        flag2 = 0;

        // Check if page already has a frame
        for (int j = 0; j < FRAMES; j++) {
            if (allocation[j] == pageRequests[i]) {
                counter++;
                time[j] = counter;
                flag1 = 1;
                flag2 = 1;
                break;
            }
        }

        // If page not in frame add it to one
        if (flag1 == 0) {
            for (int j = 0; j < FRAMES; j++) {
                if (allocation[j] == INVALID) {
                    counter++;
                    pageFaults++;
                    allocation[j] = pageRequests[i];
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }
        }

        //If frames full put page in the oldest one
        if (flag2 == 0) {
            position = findLRU(time);
            counter++;
            pageFaults++;
            allocation[position] = pageRequests[i];
            time[position] = counter;
        }

        // Print current row
        displayPages(pageRequests[i], allocation);
    }

    printf("Total Page Faults: %d\n", pageFaults);
}


//Implements the First In First Out page algorithm
void fifo() {
    printf("\n\n  ********** First In First Out **********\n\n");

    int pageRequests[] = {4, 1, 2, 4, 2, 5, 1, 3, 6};
    int allocation[FRAMES];
    int present = 0;
    int pageFaults = 0;
    int pages = sizeof(pageRequests) / sizeof(pageRequests[0]);

    memset(allocation, -1, sizeof(allocation));

    // Print header for page and frames
    printf("\tPage\t");
    for (int i = 0; i < FRAMES; i++) {
        printf("Frame %d\t", i+1);
    }
    printf("\n");

    // Iterate over page requests
    for (int i = 0; i < pages; i++) {
        present = 0;
        // Check if page request is already in a frame
        for (int j = 0; j < FRAMES; j++) {
            if (allocation[j] == pageRequests[i]) {
                present = 1;
                pageFaults--;
                break;
            }
        }
        // If page is not present and there is still space in frames, add it
        pageFaults++;

        if (pageFaults <= FRAMES && present == 0) {
            allocation[i] = pageRequests[i];
        // Replace oldest if full
        } else if (present == 0) {
            allocation[(pageFaults - 1) % FRAMES] = pageRequests[i];
        }
        //Add row to table output
        displayPages(pageRequests[i], allocation);
    }
    printf("Total Page Faults: %d", pageFaults);
}
//Runs both page replacements FIFO and LRU
void pageReplacement(void) {
    clearScreen();
    printf("\n  ********** Page Replacement **********\n");
    for (int algorithm = FIFO; algorithm <= LRU; algorithm++) {
        if (algorithm == FIFO) {
            fifo();
        } else if (algorithm == LRU) {
            lru();
        }
    }
}
// Runs the memory management  algorithms
void memoryManagement() {
    clearScreen();
    int algorithm;
    printf("\n\n  ********** Memory Management **********\n\n");
    // Loop through each of the memory management algorithms
    for (algorithm = 0; algorithm <= 3; algorithm++) {
        // Declare arrays to store memory block sizes and process sizes
        int blockSize[5] = {80, 10, 65, 35, 70};
        int processSize[5] = {25, 70, 5, 45, 60};
        int blocks = 5; // Number of memory blocks
        int processes = 5; // Number of processes
        switch(algorithm) {
            case FIRST:
                printf("  ********** First Fit **********\n\n");
                firstFit(blockSize, blocks, processSize, processes);
                break;
            case BEST:
                printf("\n\n  ********** Best Fit **********\n\n");
                bestFit(blockSize, blocks, processSize, processes);
                break;
            case WORST:
                printf("\n\n  ********** Worst Fit **********\n\n");
                worstFit(blockSize, blocks, processSize, processes);
                break;
            case NEXT:
                printf("\n\n  ********** Next Fit **********\n\n");
                nextFit(blockSize, blocks, processSize, processes);
                break;
            default:
                printf("Invalid algorithm choice.\n");
                exit(1);
        }
    }
}
//Display a table for processes
void displayProcess(int allocation[], int processes, int processSize[]) {
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < processes; i++) {
        printf(" %d \t\t %d \t\t", i+1, processSize[i]);
        // Only display when allocated
        if (allocation[i] != INVALID) {
            printf(" %d\n", allocation[i]+1);
        } else {
            printf(" Not allocated\n");
        }
    }
}
// Implements the first fit algorithm
void firstFit(int blockSize[], int blocks, int processSize[], int processes){
    int allocation[processes];
    // Initialize all elements of the array to -1
    memset(allocation, INVALID, sizeof(allocation));
    // Loop processes
    for(int i = 0; i < processes; i++){
        // Loop blocks
        for(int j = 0; j < blocks; j++){
            // Comparing to check if the current block has enough space for the current process
            if(blockSize[j] >= processSize[i]){
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }
    displayProcess(allocation, processes, processSize);
}
// Implements the next fit algorithm
void nextFit(int blockSize[], int blocks, int processSize[], int processes){
    int allocation[processes];
    int id = 0;
    // Initialize all elements of the array to -1
    memset(allocation, INVALID, sizeof(allocation));
    // Loop processes
    for (int i = 0; i < processes; i++) {
        // Loop blocks
        while (id < blocks) {
            // Compare block size and process size
            if (blockSize[id] >= processSize[i]) {
                allocation[i] = id;
                blockSize[id] -= processSize[i];
                break;
            }
            id = (id + 1) % blocks;
        }
    }
    displayProcess(allocation, processes, processSize);
}
// Implements the best fit algorithm
void bestFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[processes];
    // Initialize all elements of the array to -1
    memset(allocation, INVALID, sizeof(allocation));
    // Loop processes
    for (int i = 0; i < processes; i++) {
        int bestIdx = INVALID;
        // Look blocks
        for (int j = 0; j < blocks; j++) {
            // Compare block size and process size
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == INVALID) {
                    bestIdx = j;
                } else if (blockSize[bestIdx] > blockSize[j]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != INVALID) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    displayProcess(allocation, processes, processSize);
}
// Implements the worst fit algorithm
void worstFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[processes];
    // Initialize all elements of the array to -1
    memset(allocation, INVALID, sizeof(allocation));
    // Look processes
    for (int i = 0; i < processes; i++) {
        int wstIdx = INVALID;
        // Loop Blocks
        for (int j = 0; j < blocks; j++) {
            // Compare block size and process size
            if (blockSize[j] >= processSize[i]) {
                if (wstIdx == INVALID)
                    wstIdx = j;
                else if (blockSize[wstIdx] < blockSize[j])
                    wstIdx = j;
            }
        }
        if (wstIdx != INVALID) {
            allocation[i] = wstIdx;
            blockSize[wstIdx] -= processSize[i];
        }
    }
    displayProcess(allocation, processes, processSize);
}

int main() {
    int choice = -1;
    while (choice != 0){
        choice = displayMenu();
        if (choice == MEMORY){
            memoryManagement();
        }
        else if (choice == FILES){
            clearScreen();
            printf("Error! Reference source not found.");
        }
        else if (choice == THREAD){
            clearScreen();
            printf("Error! Reference source not found.");
        }
        else if (choice == PAGE){
            pageReplacement();
        }
        else if (choice == EXIT){
            exit(0);
        }
    }
    return 0;
}