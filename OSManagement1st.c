#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Jack Sweeney 3/2/23
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
void clearScreen(){
    fflush(stdin);
    printf("Error! Reference source not found.");
    char inp;
    while (inp != '\n'){
            scanf("%c", &inp);
    }
    system("cls");
    //system("clear");
}
int main() {
    int choice = -1;
    clearScreen();
    while (choice != 0){
        choice = displayMenu();
        if (choice == 1){
            clearScreen();
        }
        else if (choice == 2){
            clearScreen();
        }
        else if (choice == 3){
            clearScreen();
        }
        else if (choice == 0){
            exit(0);
        }
    }
    return 0;
}