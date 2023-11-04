#include <stdlib.h>
#include <stdio.h>

// Node
typedef struct Node { 
    int data;
    struct Node *link;
} Node;

//Domestic student structure
typedef struct DomesticStudent {
    char *firstName;
    char *lastName;
    struct DomesticStudent *link;
    
} DomesticStudent;

//International student structure 
typedef struct InternationalStudent {
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

    fgets 



    return 0;

}








1. HOW TO SOLVE THE PROBLEM. WHAT IS THE PROBLEM ? 
    - We need to READ the contents of a file, and then we need to WRITE the results to an output file. 
    - THE PROBLEM IS: WRITE TO THE OUTPUT FILE: 
        - STUDENTS WHOSE GPA IS GREATER THAN 3.9. Can store up TO 3 DECIMAL PLACES. STORE ORIGINAL DEC VALUE IF POSSIBLE
        - INTERNATIONAL STUDENT HAS A TOEFL SCORE. IF LESS THAN 70 ( < 70) do NOT write to the output file 
        - DOMESTIC STUDENT: NO TOEFL
        - ORDER OF STUDENTS IS SAME AS ORDER IN THE FILE
        - IF FORMAT OF STUDENT DOESNT FIT SPECIFIED FORMAT, OUTPUT APROPIATE ERROR MESSAGE
        - OPTION FIELD: 1 = Save filtered output of domestic students, 2 = filtered output of inter students, 3 = output of all STUDENTS
        - Assume everyone has a first and last name 
        - every line ends in a new line character 
        - WE NEED TO HANDLE CORNER CASES 
2. READ in the input file using: fgets = RETURNS A STRING (NULL TERMINATED) FOR EACH LINE IN THE FILE. A LINE CORRESPONDS TO A STUDENT 
3. 