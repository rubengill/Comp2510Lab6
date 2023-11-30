#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Structure that holds a pointer to a key and value
typedef struct KeyValue {
    void *key;
    void  *value;
    size_t keySize;
    size_t valueSize;
};

// Defines a node, which can hold Key/Values
typedef struct Node {
    KeyValue keyValue;
    struct Node *nextNode;
    struct Node * previousNode;
} Node;

// Display options
void displayOptions() {
    printf("1) Print Keys");
    printf("2) Print Values");
    printf("3) Insert KV Pair");
    printf("4) Save");
    printf("5) Repair");
    printf("6) Exit\n");
}

void storeData()

// Create node, pass in needed data to make the structure
Node createNode() {


    return dataNode;
}

// Add node to the list
void addNode(Node **head, Node *newNode) {
    
}

// Insert KV Pair
void insertPair() {

    printf("Insert key: \n");
    scanf("%s", )
    printf("Key data size: \n");
    printf("Insert value: \n");
    printf("Value data size: \n");
}

// Handle the user choice
void handleOption(int *userChoice) {
    switch (*userChoice) {
        case 1:
            printKeys();
            break;
        case 2:
            printValues();
            break;
        case 3:
            char *key;
            int keySize;
            insertPair();
            break;
        case 4:
            save();
            break;
        case 5:
            repair();
            break;
        default:
            break:
    }
}

// Print keys
void printKeys() {
    printf("Print keys funcition!");

}

// Print Values
void printValues() {
    printf("Print  funcition!");
}

// Save the program
void save() {
    printf("Print save funcition!");
}

// Repair the program
void repair() {
    printf("Print repair funcition!");
}

// Drives the program
int main() {

    int choice;
    int status;

    Node *head = NULL;

    do {
        // Present user with options
        displayOptions();

        // Returns 1 if input is an int 
        status = scanf("%d", &choice);

        // Check if input is int
        while (status != 1) {
            // Clear input buffer
            while ((getchar()) != '\n');
            printf("Please enter an integer.");
            status = scanf("d", &choice);
        }

        if (choice != 6) {
            handleOption(&choice);
        }
    } while (choice != 6);

    //Exit the program 
    return 0;
}


FP *fp = (,"w");
    if (!fp) {
        printf("Could not open output file");
        return 1;
    }
