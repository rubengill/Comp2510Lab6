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
    printf("1) Print Keys\n");
    printf("2) Print Values\n");
    printf("3) Insert KV Pair\n");
    printf("4) Save\n");
    printf("5) Repair\n");
    printf("6) Exit\n");
}

// Add node to the list
void addNode(Node **head, Node *newNode) {
    // Check if the list is empty
    if (*head == NULL) {
        *head = newNode;
    } else {
        // Traverse the list to find the last node
        Node *current = *head;
        while (current->nextNode != NULL) {
            current = current->nextNode;
        }

        // Insert newNode at the end of the list
        current->nextNode = newNode;
        newNode->previousNode = current;
    }
}

// Create node, pass in needed data to make the structure
Node *createNode(void *key, size_t keySize, void *value, size_t valueSize) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Failed to allocate memory for new node");
        return NULL;
    }
    
    // Set information in the node 
    newNode -> keyValue.key = malloc(keySize);
    newNode -> keyValue.value = malloc(valueSize);

    if (newNode->keyValue.key == NULL || newNode->keyValue.value == NULL) {
        perror("Failed to allocate memory for key or value");
        free(newNode->keyValue.key);  // Free in case one allocation succeeded
        free(newNode->keyValue.value);
        free(newNode);
        return NULL;
    }

    // Assign values 
    memcpy(newNode->keyValue.key, key, keySize);
    memcpy(newNode->keyValue.value, value, valueSize);
    newNode->keyValue.keySize = keySize;
    newNode->keyValue.valueSize = valueSize;

    newNode->nextNode = NULL;
    newNode->previousNode = NULL;

    return newNode;
}

// Insert KV Pair
void insertPair(Node **head) {
    char inputOne[256];
    char inputTwo[256];
    size_t dataSizeOne;
    size_t dataSizeTwo;

    // Get the user information
    printf("Insert key: \n");
    scanf("%255s", inputOne);

    printf("Key data size: \n");
    scanf("%zu", dataSizeOne);

    printf("Insert value: \n");
    scanf("%255s", inputTwo);    

    printf("Value data size: \n");
    scanf("%zu", dataSizeTwo);

    Node *newNode = createNode(&inputOne, dataSizeOne, &inputTwo, dataSizeTwo);
    addNode(head, newNode);
}

// Handle the user choice
void handleOption(int userChoice, Node **head) {

    switch (userChoice) {
        case 1:
            printKeys(head);
            break;
        case 2:
            printValues(head);
            break;
        case 3:
            insertPair(head);
            break;
        case 4:
            save(head);
            break;
        case 5:
            repair(head);
            break;
        default:
            break;
    }

}

// Print keys
void printKeys(Node **head) {
    Node *current = *head; 
    while (current != NULL) {
        if (current->keyValue.keySize == sizeof(int)) {
            printf("%d ", *(int *)(current -> keyValue.key));
        } else if (current -> keyValue.keySize == sizeof(char)) {
            printf("%c ", *(char *)(current -> keyValue.key));
        } else if (current -> keyValue.keySize == sizeof(float)) {
            printf("%f ", *(float *)(current -> keyValue.key));
        } else if (current -> keyValue.keySize == sizeof(double)) {
            printf("%lf ", *(double *)(current -> keyValue.key));
        }

        current = current->nextNode;
    }
    printf("\n");
}

// Print Values
void printValues(Node **head) {
    Node *current = *head; 
    while (current != NULL) {
        if (current -> keyValue.valueSize == sizeof(int)) {
            printf("%d ", *(int *)(current -> keyValue.value));
        } else if (current -> keyValue.valueSize == sizeof(char)) {
            printf("%c ", *(char *)(current -> keyValue.value));
        } else if (current -> keyValue.valueSize == sizeof(float)) {
            printf("%f ", *(float *)(current -> keyValue.value));
        } else if (current -> keyValue.valueSize == sizeof(double)) {
            printf("%lf ", *(double *)(current -> keyValue.value));
        }

        current = current->nextNode;
    }
    printf("\n");
}

// Save the program
void save(Node **head) {
    char fileName[256];
    printf("Type the file name: ");
    scanf("%255s", fileName);

    // Open the file in binary write mode
    FILE *file = fopen(fileName, "wb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Iterate through the list and write the data to the file
    Node *current = *head;
    while (current != NULL) {
        // Write the key size and key data
        fwrite(&(current->keyValue.keySize), sizeof(current->keyValue.keySize), 1, file);
        fwrite(current->keyValue.key, current->keyValue.keySize, 1, file);

        // Write the value size and value data
        fwrite(&(current->keyValue.valueSize), sizeof(current->keyValue.valueSize), 1, file);
        fwrite(current->keyValue.value, current->keyValue.valueSize, 1, file);

        // Move to the next node
        current = current->nextNode;
    }

    fclose(file);
    printf("Data saved to %s\n", fileName);
}

// Repair the program
void repair(Node **head) {
    char fileName[256];
    printf("Type the file name: ");
    scanf("%255s", fileName);

    // Open the file in binary read mode
    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Clear the current list if it exists
    clearList(head);

    // Read the file and reconstruct the list
    size_t keySize
    size_t valueSize;
    while (fread(&keySize, sizeof(keySize), 1, file) == 1) {
        void *key = malloc(keySize);
        fread(key, keySize, 1, file);

        fread(&valueSize, sizeof(valueSize), 1, file);
        void *value = malloc(valueSize);
        fread(value, valueSize, 1, file);

        Node *newNode = createNode(key, keySize, value, valueSize);
        addNode(head, newNode);
    }

    // Close the file
    fclose(file);
    printf("Data restored from %s\n", fileName);
}

// Clear the linked list 
void clearList(Node **head) {
    Node *current = *head;
    while (current != NULL) {
        Node *temp = current;
        current = current->nextNode;
        free(temp->keyValue.key);
        free(temp->keyValue.value);
        free(temp);
    }
    *head = NULL;
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
            status = scanf("%d", &choice);
        }

        if (choice != 6) {
            handleOption(choice, &head);
        }
    } while (choice != 6);

    clearList(head);

    //Exit the program 
    return 0;
}
