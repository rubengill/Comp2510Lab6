#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *lastName;
    char *firstName;
    char studentNum[9];
    int midtermGrade;
    int finalGrade;

} Student;

// Count the number of lines in the student 
int countLines(FILE *fp) {
    int lines = 0;
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), fp)) {
        lines++;
    }

    // Have the pointer point to the beginning of the file again 
    rewind(fp);

    return lines;
}


// Parse the input token 
void parseString(char *line, char **fName, char **lName, char *stuNum, int *midVal, int *finalVal) {
    
    // Parse first name
    char *token = strtok(line, " ");
    *fName = strdup(token);
    
    // Parse last name
    token = strtok(NULL, " ");
    *lName = strdup(token);

    // Parse student number
    token = strtok(NULL, " ");
    strncpy(stuNum, token, 8);
    stuNum[8] = '\0'; 

    // Parse midterm grade
    token = strtok(NULL, " ");
    *midVal = atoi(token);

    // Parse final grade
    token = strtok(NULL, " ");
    *finalVal = atoi(token);
}

// Create a student structure 
Student createStudent(char *fName, char *lName, char *stuNum, int midterm, int final) {
    Student newStudent;
    
    // Deep print student information 
    newStudent.firstName = strdup(fName);
    newStudent.lastName = strdup(lName);
    strcpy(newStudent.studentNum, stuNum);
    newStudent.midtermGrade = midterm;
    newStudent.finalGrade = final;
    
    return newStudent;
}

// Compare the students based on their variable values 
int compareStudents(const void *a, const void *b) {
    const Student *student1 = (const Student *)a;
    const Student *student2 = (const Student *)b;

    // Compare by last name
    int lastNameComparison = strcmp(student1->lastName, student2->lastName);
    if (lastNameComparison != 0) return lastNameComparison;

    // Compare by first name
    int firstNameComparison = strcmp(student1->firstName, student2->firstName);
    if (firstNameComparison != 0) return firstNameComparison;

    // Compare by student number 
    int studentNumComparison = strcmp(student1 -> studentNum, student2 -> studentNum);
    if (studentNumComparison != 0) return studentNumComparison;

    // Compare by midterm grade 
    if (student1 -> midtermGrade < student2 -> midtermGrade) return -1;
    if (student1 -> midtermGrade > student2 -> midtermGrade) return 1;

    // Compare by final grade 
    if (student1 -> finalGrade < student2 -> finalGrade) return -1;
    if (student1 -> finalGrade > student2 -> finalGrade) return 1;
    
    
    return 0; 
}

// Print the students based on the option
void printStudents(Student *studentArr, int studentCount, FILE *fp_out, int option) {
    for (int i = 0; i < studentCount; i++) {
        // Calculate the average 
        float average = (float)(studentArr[i].midtermGrade + studentArr[i].finalGrade) / 2;

        switch (option) {
            // Average higher than 90%
            case 1: 
                if (average > 90) {
                    fprintf(fp_out, "%s %s %s %d %d\n", 
                            studentArr[i].firstName,
                            studentArr[i].lastName,  
                            studentArr[i].studentNum, 
                            studentArr[i].midtermGrade, 
                            studentArr[i].finalGrade);
                }
                break;
            // Average between 80% and 90%
            case 2:
                if (average > 80 && average <= 90) {
                    fprintf(fp_out, "%s %s %s %d %d\n", 
                            studentArr[i].firstName,
                            studentArr[i].lastName,
                            studentArr[i].studentNum, 
                            studentArr[i].midtermGrade, 
                            studentArr[i].finalGrade);
                }
                break;
            // Average between 70% and 80%
            case 3:
                if (average > 70 && average <= 80) {
                    fprintf(fp_out, "%s %s %s %d %d\n", 
                            studentArr[i].firstName,
                            studentArr[i].lastName,
                            studentArr[i].studentNum, 
                            studentArr[i].midtermGrade, 
                            studentArr[i].finalGrade);
                }
                break;
            // Average between 60% and 70%
            case 4:
                if (average > 60 && average <= 70) {
                    fprintf(fp_out, "%s %s %s %d %d\n", 
                            studentArr[i].firstName,
                            studentArr[i].lastName, 
                            studentArr[i].studentNum, 
                            studentArr[i].midtermGrade, 
                            studentArr[i].finalGrade);
                }
                break;
            // Average below 60%
            case 5: 
                if (average < 60) {
                    fprintf(fp_out, "%s %s %s %d %d\n", 
                            studentArr[i].firstName,
                            studentArr[i].lastName,
                            studentArr[i].studentNum, 
                            studentArr[i].midtermGrade, 
                            studentArr[i].finalGrade);
                }
                break;
            default:
                fprintf(stderr, "Invalid option: %d\n", option);
                break;
        }
    }
}

// Drives the program 
int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("You must have 4 command line arguments!\n");
        return 1;
    }

    char *inputFileName = argv[1];
    char *outputFileName = argv[2];
    int option = atoi(argv[3]);

    FILE *fp = fopen(inputFileName, "r");
    if (!fp) {
        perror("Couldn't open input file");
        return 1;
    }

    FILE *fp_out = fopen(outputFileName, "w");
    if (!fp_out) {
        perror("Couldn't open output file");
        fclose(fp);
        return 1;
    }

    if (option < 1 || option > 5) {
        fprintf(stderr, "Option must be between 1 and 5\n");
        fclose(fp);
        fclose(fp_out);
        return 1;
    }

    char *fName = NULL;
    char *lName = NULL;
    char stuNum[9];
    int midVal;
    int finalVal;

    int numLines = countLines(fp);
    // Get the number of students from the input file 
    Student *stuArr = malloc(numLines * sizeof(Student));
    if (!stuArr) {
        perror("Failed to allocate memory for students");
        fclose(fp);
        fclose(fp_out);
        return 1;
    }

    char buffer[1000];
    int currentIndex = 0;
    while (fgets(buffer, sizeof(buffer), fp)) {
        parseString(buffer, &fName, &lName, stuNum, &midVal, &finalVal);
        // Use pointer arithmetic to add students to the array 
        stuArr[currentIndex++] = createStudent(fName, lName, stuNum, midVal, finalVal);

        free(fName); 
        free(lName);
    }
    // Sort the array 
    qsort(stuArr, numLines, sizeof(Student), compareStudents);

    printStudents(stuArr, numLines, fp_out, option);

    for (int i = 0; i < numLines; i++) {
    free(stuArr[i].lastName);
    free(stuArr[i].firstName);
    }
    free(stuArr);
    
    fclose(fp);
    fclose(fp_out);
    return 0;
}
