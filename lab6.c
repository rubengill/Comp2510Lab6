#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Flag that we can use to determine what type of student 
typedef enum {
    DOMESTIC,
    INTERNATIONAL
} StudentType;

//Domestic student structure
typedef struct {
    char *firstName;
    char *lastName;
    double gpa;
} DomesticStudent;

//International student structure 
typedef struct {
    char *firstName;
    char *lastName;
    double gpa;
    int toefl;
} InternationalStudent;

// Defines a node in the linked list, which can either be a dStudent or iStudent
typedef struct StudentNode {
    // Flag to determine the type of student it is
    StudentType type;

    // Sets aside memory for an international student, which a domestic student can also occupy
    union {
        DomesticStudent dStudent;
        InternationalStudent iStudent;
    } student;

    // Link to the next node
    struct StudentNode *next;
}

// Ensure every line ends in a new line character 
char* checkNewLine(char *buffer) {
    // Number of elements before the new line 
    int bufferElements = (int) strlen(buffer);

    // 1 if has a new line
    int hasNewLine = (bufferElements > 0 && buffer[bufferElements - 1] == '\n');

    // Add another byte if does not contain a new line 
    char *newArr = (char*)malloc((bufferElements + 1 + !hasNewLine)* sizeof(char));

    // Copies bytes from the desired string, minus the null terminator
    memcpy(newArr, buffer, bufferElements);

    if (!hasNewLine) {
        newArr[bufferElements] = '\n';
        bufferElements++;
    }

    newArr[bufferElements] = '\0'

    return newArr;
}

StudentNode *createStudentNode(char *arr, FILE *fp_out) {
    StudentNode *newStudent = (StudentNode *)malloc(sizeof(StudentNode));

    newStudent -> next = NULL;

    if (arr == NULLL) {
        printf("Error: There is no arr being passed in to create a student node !");
    }

    char *token = (arr, " ");
}



int main(int argc, char *argv[]) {

    if (argv != 4) {
        printf("Error: There must be 4 command line arguments");
    }

    // Get command line arguments
    char *inputFileName = argv[1];
    char *outputFileName = argv[2];
    int option = atoi(argv[3]);

    FILE *fp_out = fopen(outputFileName, "w");
    if (!fp_out) {
        perror("Error: Can't open the output file.");
        fclose(fp);
        return 1;
    }

    // Gets written to the output file 
    if (option < 1 || > 3) {
        fprintf("Error: Option must be greater than 0");
        fclose(fp_out_);
        return 1;
    }
    
    FILE *fp = fopen(inputFileName, "r");
    if (!fp) { 
        perror("Error: Can't find the output file")
        // Exits the program
        return 1;
    }

    char buffer[500];

    // Get the line
    while (fgets(buffer, sizeof(buffer), inputFileName)) {
        // *line points to an array with no trailing white spaces, and no null terminator
        char *line = removeWhiteSpace(buffer);



    }

    // Need to create node for the head of the linked list 

    fclose(fp);
    fclose(fp_out);

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
2. READ in the input file using: fgets = RETURNS A STRING (NULL TERMINATED) FOR EACH LINE IN THE FILE. A LINE CORRESPONDS TO A STUDENT. Print error message to text file if does not follow specified format 
3. We are using struct. so that means the students will be connected to one another via Nodes. So we need a method to take the input data, and create a node with it. 
4. Ok so we take the data, create a node, and then add it to the linked list. After that is all done, we can iterate through the linked list, and print the data for each list on a line. 
5. Since we use fgets to create a string from each line of data, we need to parse this string somehow to assign the correct values to the variables in the struct node. 
    - For Examnple: For Mike Johnson 3.125 D, We need to assign fName: Mike, lName: Johnson, gpa: 3.125, link: link -> link;
    - Use the white space to parse the string ? and treat the number as a string and then convert it when printing it ? 

    - strtok will replace every delimeter with a new line character. Is this what we want ? 

