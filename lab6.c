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
    char gpa[6];
} DomesticStudent;

//International student structure 
typedef struct {
    char *firstName;
    char *lastName;
    char gpa[6];
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
} StudentNode;

// Trim leaing and trailing white space 
char* trimWhiteSpace(char *buffer, FILE *fp_out) {
    char *start = buffer;
    char *end;

    // Trim leading space
    while(isspace((unsigned char)*start)) start++;

    // All spaces
    if(*start == 0) {
        // String is all spaces or empty
        fprintf(fp_out, "Error: Input string is empty or contains only whitespace!\n");
        exit(EXIT_FAILURE); // Exit immediately, no need to allocate emptyStr
    }

    // Trim trailing space
    end = start + strlen(start) - 1;
    while(end > start && isspace((unsigned char)*end)) end--;

    // Write new null terminator
    *(end + 1) = '\0';

    // Allocate memory for the trimmed string
    int trimmedLength = end - start + 2; // +2 for the character and null terminator
    char *newStr = (char*)malloc(trimmedLength);
    if (newStr == NULL) {
        printf("Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newStr, start);
    return newStr;
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
void parseString(char *line, char **fName, char **lName, char *gpaArr, double *gpa, char *type, int *toefl, FILE *fp_out) {
    char *token;
    int tokenCount = 0;
    
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
    // Store the gpa String in gpaStr, so it can be passed into student structure. 
    strncpy(gpaArr, token, 5);
    gpaArr[5] = '\0';
    *gpa = strtod(token, NULL);
    if (*gpa < 0.0 || *gpa > 4.33) {
        fprintf(fp_out, "Error: GPA cannot be negative or greater than 4.33\n");
        exit(EXIT_FAILURE);
    }
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
        if (*toefl < 0) {
            fprintf(fp_out, "Error: TOEFL score cannot be negative\n");
            exit(EXIT_FAILURE);
        } else if (*toefl > 120) {
	    fprintf(fp_out, "Error: TOEFL score cannot be more than 120\n");
	    exit(EXIT_FAILURE);
        }
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
DomesticStudent *createDStudent(char *fName, char *lName, char *gpaArr) {
    DomesticStudent *dStudent = (DomesticStudent *)malloc(sizeof(DomesticStudent));

    if (dStudent == NULL) {
        printf("Error: Can't create dStudent");
        exit(EXIT_FAILURE);
    }

    // Create another duplicate of names so when memory is freed there is no dangling pointers
    dStudent -> firstName = strdup(fName);
    if (dStudent -> firstName == NULL) {
        printf("Memory allocation failed for firstname\n");
        free(dStudent);
        exit(EXIT_FAILURE);
    }    
    dStudent -> lastName = strdup(lName);
    strncpy(dStudent -> gpa, gpaArr, sizeof(dStudent->gpa) - 1);
    dStudent -> gpa[sizeof(dStudent->gpa) - 1] = '\0';

    return dStudent;
}

// Create an international student 
InternationalStudent *createIStudent(char *fName, char *lName, char *gpaArr, int toefl) {
    InternationalStudent *iStudent = (InternationalStudent *)malloc(sizeof(InternationalStudent));

    if (iStudent == NULL) {
        printf("Error: Can't craete iStudent");
        exit(EXIT_FAILURE);
    }

    iStudent -> firstName = strdup(fName);
    iStudent -> lastName = strdup(lName);
    strncpy(iStudent -> gpa, gpaArr, sizeof(iStudent -> gpa) - 1);
    iStudent -> gpa[sizeof(iStudent->gpa) - 1] = '\0';
    iStudent -> toefl = toefl;

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

    if (studentType == INTERNATIONAL) {
        // Cast to appropiate student, and derefernce to get access the struct 
        InternationalStudent *original = (InternationalStudent *) studentStruct;
        // Deep copy each string
        newStudent -> student.iStudent.firstName = strdup(original -> firstName);
        newStudent -> student.iStudent.lastName = strdup(original -> lastName);
        strcpy(newStudent -> student.iStudent.gpa, original -> gpa);
        newStudent -> student.iStudent.toefl = original -> toefl;
    } else if (studentType == DOMESTIC) {
        DomesticStudent *original = (DomesticStudent *) studentStruct;
        newStudent -> student.dStudent.firstName = strdup(original -> firstName);
        newStudent -> student.dStudent.lastName = strdup(original -> lastName);
        strcpy(newStudent -> student.dStudent.gpa, original -> gpa);
    }

    newStudent -> next = NULL;

    return newStudent;
}

//Adds a student node to the end of the list 
void addToList(StudentNode **head, StudentNode *newNode) {
    if (*head == NULL) {
        *head = newNode;
    } else {
        StudentNode* current = *head;
        while(current -> next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to print information of an international student
void printInternationalStudent(InternationalStudent *student, FILE *fp_out) {
    fprintf(fp_out, "%s %s %s I %d\n", student -> firstName, student -> lastName, student -> gpa, student -> toefl);
}

// Function to print information of a domestic student
void printDomesticStudent(DomesticStudent *student, FILE *fp_out) {
    fprintf(fp_out, "%s %s %s D\n", student -> firstName, student -> lastName, student -> gpa);
}

//Print the Students
void printStudents(StudentNode *head, FILE *fp_out, int option) {
    // Iterate through the linked list
    for (StudentNode *current = head; current != NULL; current = current->next) {
        // Print based on the option provided
        switch (option) {
            // Domestic students only
            case 1: 
                if (current -> type == DOMESTIC) {
                    printDomesticStudent(&(current -> student.dStudent), fp_out);
                }
                break;
            // International students only
            case 2: 
                if (current -> type == INTERNATIONAL) {
                    printInternationalStudent(&(current -> student.iStudent), fp_out);
                }
                break;
            // / All students
            case 3: 
                if (current -> type == INTERNATIONAL) {
                    printInternationalStudent(&(current -> student.iStudent), fp_out);
                } else if (current -> type == DOMESTIC) {
                    printDomesticStudent(&(current -> student.dStudent), fp_out);
                }
                break;
            default:
                fprintf(fp_out, "Invalid option\n");
                break;
        }
    }
}

// Free the nodes in the list 
void freeList(StudentNode *head) {
    StudentNode *current = head;
    while (current != NULL) {
        StudentNode *next = current -> next;

        // Free student structs 
        if (current -> type == INTERNATIONAL) {
            free(current -> student.iStudent.firstName);
            free(current -> student.iStudent.lastName);
        } else if (current -> type == DOMESTIC) {
            free(current -> student.dStudent.firstName);
            free(current -> student.dStudent.lastName);
        }
        free(current);
        current = next;
    }
}

// Entry to the program
int main(int argc, char *argv[]) {

    if (argc != 4) {
        perror("Error: There must be 4 command line arguments");
        return 1;
    }

    // Get command line arguments
    char *inputFileName = argv[1];
    char *outputFileName = argv[2];
    int option = atoi(argv[3]);

    FILE *fp = fopen(inputFileName, "r");
    if (!fp) { 
        perror("Error: Can't find the output file");
        // Exits the program
        return 1;
    }

    FILE *fp_out = fopen(outputFileName, "w");
    if (!fp_out) {
        perror("Error: Can't open the output file.");
        fclose(fp);
        return 1;
    }

    // Gets written to the output file 
    if (option < 1 || option > 3) {
        fprintf(fp_out, "Error: Option must be between 1 and 3\n");
        fclose(fp_out);
        fclose(fp);
        return 1;
    }

    // Create the head of a node 
    StudentNode *head = NULL;

    char *fName = NULL;
    char *lName = NULL;
    char gpaArr[6] = " ";

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
    while (fgets(buffer, sizeof(buffer), fp)) {
        typeVal = '\0';
        strcpy(gpaArr, " ");
        
        // *line points to an array with no trailing white spaces
        char *line = trimWhiteSpace(buffer, fp_out);
        
        if (line[0] == '\0') {
        free(line);
        continue;
    }
 
        // Parse the string, assign values to appropiate variables 
        parseString(line, &fName, &lName, gpaArr, gpaPtr, typePtr, toeflPtr, fp_out);

        // Create appropiate student struct, add to linked list 
        if ((typeVal == 'I' || typeVal == 'i') && gpaVal >= 3.9 && toeflVal >= 70) {
           // Create Structure
            InternationalStudent *iStudent = createIStudent(fName, lName, gpaArr, toeflVal);

            // Create Node
            StudentNode *studentNode = createStudentNode(INTERNATIONAL, (void*)iStudent);

            //Add to linked list
            addToList(&head, studentNode);
        } else if ((typeVal == 'D' || typeVal == 'd') && gpaVal >= 3.9) {
            // Create Structure
            DomesticStudent *dStudent = createDStudent(fName, lName, gpaArr);
            
            // Create Node
            StudentNode *studentNode = createStudentNode(DOMESTIC, (void*)dStudent);

            //Add to linked list
            addToList(&head, studentNode);
        }
        //Free cleared trailing white space memory 
        free(line);
	line = NULL;
        free(fName);
        free(lName);
        fName = NULL;
        lName = NULL;
    }

    printStudents(head, fp_out, option);

    freeList(head);
    
    fclose(fp);
    fclose(fp_out);

    return 0;
}
