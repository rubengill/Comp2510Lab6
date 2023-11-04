#include <stdlib.h>
#include <stdio.h>

// Node
typedef Node { 
    ? data;
    struct Node *link;
}

//Domestic student structure
typedef struct {
    char *firstName;
    char *lastName;
    struct DomesticStudent *link;
    
} DomesticStudent;

//International student structure 
typedef struct {
    char *firstName;
    char *lastName;
    int toefl;
    struct InternationalStudent *link;

} InternationalStudent;

int main(int argc, char *argv[]) {

    if (argv != 4) {
        printf("There must be 4 command line arguments");
    }

    // Get command line arguments
    char *inputFileName = argv[1];
    char *outputFileName = argv[2];
    int option = atoi(argv[3]);

    // Handle edge cases, gets written to the output file 
    if (option < 0) {
        printf("Error. Option must be greater than 3")
    }

    // If the in/out files are null / empty ? 
    if
    
    FILE *fp = fopen(inputFileName, "r");
    if (!fp) { 
        perror("Can't find the file pal!")
        return 1;
    }

    fseek



    return 0;

}