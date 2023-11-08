#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

// Checks if a string can be converted to a double 
int isValidDouble(char *str) {
    char *endptr;
    strtod(str, &endptr);
    return *endptr == '\0' || *endptr == '\n';
}

// Checks if a string can be converted to an integer
int isValidInt(char *str) {
    char *endptr;
    strtol(str, &endptr, 10);
    return *endptr == '\0' || *endptr == '\n';
}

// Parse the input line, and store the data in the appropiate variables defined in the main method 
void parseString(char *line, char **fName, char **lName, double *gpa, char *type, int *toefl, FILE *fp_out) {
    char *token;
    int tokenNum;

    // Ensure the first token is a string
    token = strtok(line, " ");
    if (token == NULL || !isalpha(*token)) {
        fprintf(fp_out, "Error: Invalid first name\n");
        exit(EXIT_FAILURE);
    }

    // Dereference double pointer to get the mem address stored in the pointer to a string, and change the string it points too 
    *fName = strdup(token);
    tokenCount++;

    token = strtok(NULL, " ");
    if (token == NULL || !isalpha(*token)) {
        fprintf(fp_out, "Error: Invalid last name\n");
        exit(EXIT_FAILURE);
    }

    *lName = strdup(token);
    tokenCount++;

    // Validate GPA 
    token = strtok(NULL, " ");
    if (token == NULL || !isValidDouble(token)) {
        fprintf(fp_out, "Error: Invalid GPA\n");
        exit(EXIT_FAILURE);
    }

    *gpa = strtod(token, NULL);
    tokenCount++;


    // Validate the type
    token = strtok(NULL, " ");
    if (token == NULL || (token[0] != 'I' && token[0] != 'i' && token[0] != 'D' && token[0] != 'd')) {
        fprintf(fp_out, "Error: Invalid student type\n");
        exit(EXIT_FAILURE);
    }

    *type = token[0];
    tokenCount++;

    // Valid toefl is student is international
    if (*type == 'I' || *type == 'i') {
        token = strtok(NULL, " ");
        if(token == NULL || !isValidInt(token)) {
            fprintf(fp_out, "Error: Invalid TOEFL\n");
            exit(EXIT_FAILURE);
        }
        *toefl = (int)strtol(token, NULL, 10);
        tokenCount++;
    }

    //Check if there are more tokens
    if(strtok(NULL, " ") != NULL) {
        fprintf(fp_out, "Error: Too many tokens in the line!\n");
        exit(EXIT_FAILURE);
    }
    
    // Gatekeeper to ensure that there are only 4 or 5 tokens 
    if (((*type == 'I' || *type == 'i') && tokenCount != 5) || ((*type == 'D' || *type == 'd') && tokenCount != 4)) {
        fprintf(fp_out, "Error: Incorrect number of data fields\n");
        exit(EXIT_FAILURE);
    }

}

// Create a domestic student 
DomesticStudent createDStudent(char *fName, char *lName, double gpa) {
    DomesticStudent *dStudent = malloc(sizeof(DomesticStudent));

    if (dStudent == NULL) {
        printf("Error: Can't create dStudent");
        exit(EXIT_FAILURE);
    }

    dStudent.firstName = fName;
    dStudent.lastName = lastName;
    dStudent.gpa = gpa;

    return dStudent;
}

// Create an international student 
InternationalStudent createIlStudent(char *fName, char *lName, double gpa, int toefl) {
    InternationalStudent *iStudent = malloc(sizeof(InternationalStudent));

    if (iStudent == NULL) {
        printf("Error: Can't craete iStudent");
        exit(EXIT_FAILURE);
    }

    iStudent.firstName = fName;
    iStudent.lName = lName;
    iStudent.gpa = gpa;
    iStudent.toefl = toefl;

    return iStudent;
}

// Create a student node depending on the type 
StudentNode *createStudentNode(StudentType studentType, void *studentStruct) {
    // Create student node,
    StudentNode *newStudent = (StudentNode *)malloc(sizeof(StudentNode));

    if (newStudent == NULL) {
        printf("Error: Can't create Node");
        exit(EXIT_FAILURE);
    }

    newStudent -> type = studentType;

    if ( studentType == INTERNATIONAL) {
        // Cast to appropiate student, and derefernce to get access the struct 
        newStudent -> student.iStudent = *(InternationalStudent*) studentStruct;
    } else if (studentType == DOMESTIC) {
        newStudent -> student.dStudent = *(DomesticStudent*) studentStruct;
    }

    newStudent -> next = NULL;

    return newStudent;
}

//Adds a student node to the end of the list 
void addToList(StudentNode **head, StudentNode *newNode) {
    StudentNode* current = *head;

    while(current -> next != NULL) {
        current = current -> next;
    }

    current -> next = newNode

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

    // Create the head of a node 
    StudentNode *head = (StudentNode*)malloc(sizeof(StudentNode));
    if (*head == NULL) {
        printf("Memory allocation failed!");
    }
    head -> next = NULL;

    char *fName = NULL;
    char *lName = NULL:

    // The following ptrs now contain a memory address which holds the value. When passed into the 
    // parseString method, the value at each ptr can be changed. 
    double gpaVal;
    double *gpaPtr = &gpaVal; 

    char typeVal;
    char *typePtr = &typeVal;

    int toeflVal;
    int *toeflPtr = &toeflVal;

    char buffer[1000];

    // Get the line from the text tile
    while (fgets(buffer, sizeof(buffer), inputFileName)) {
        // *line points to an array with no trailing white spaces, and no null terminator
        char *line = checkNewLine(buffer);

        // Parse the string, assign values to appropiate variables 
        parseString(line, &fName, &lName, gpaPtr, typePtr, toeflPtr, fp_out);

        // Create appropiate student struct, add to linked list 
        if ((typeVal == 'I' || typeVal == 'i') && gpaVal > 3.9 && toeflVal >= 0 && toeflVal <= 120) {
                // Create Structure
                InternationalStudent *iStudent = createIlStudent(fName, lName, gpaVal, toeflVal);

                // Create Node
                StudentNode *studentNode = createStudentNode(INTERNATIONAL, (void*)iStudent);

                //Add to linked list
                addToList(&head, studentNode);

        } else if ((typeVal == 'D' || typeVal == 'd') && gpaVal > 3.9) {
            // Create Structure
            DomesticStudent dStudent = createDStudent(fName, lName, gpaVal);

            // Create Node
            StudentNode *studentNode = createStudentNode(DOMESTIC, (void*)dStudent);

            //Add to linked list
            addToList(&head, studentNode);
        }
    

    free(fName);
    free(lName);
    fName = NULL;
    lName = NULL;
    
    }
     

    // Write a function to free all of the nodes in the linked list. Just need to iterate over it and free the memory 
    while (head -> next != NULL) {
        free(node)
    }

    fclose(fp);
    fclose(fp_out);

    return 0;
}