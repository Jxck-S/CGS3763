#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Jack Sweeney 3/26/23
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

int displayMenu(){
    int choice = -1;
    printf(" \nSelect the OS program to run, enter a selection\n");
    printf("1. Memory Management\n");
    printf("2. File Management\n");
    printf("3. Multithreading\n");
    printf("0. Exit\n");
    scanf("%d", &choice);
    if (choice < 0 || choice > 3) choice = -1;
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
        else if (choice == EXIT){
            exit(0);
        }
    }
    return 0;
}