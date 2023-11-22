#include <stdio.h>
#include <stdlib.h>

// update this with your A number
char a_num[] = "";

void rotateArray(int arr[10][10], int n, int rows, int cols) {
    // Divide the command line int by 90 to determine how many times by 
    //90 to rotate the matrix 
    int rotations = n / 90;

    //Rotate the matrix according to the rotations number
    for (int i = 0; i < rotations; i++) {
        //j < rows / 2 determines how many rings the matrice contains
        for (int j = 0; j < rows / 2; j++) {
            //Iterate over the elements in the side of the current ring in the matrix
            //and stop at the last element 
            for (int k = j; k < rows - j - 1; k++) {

                // Save the first element being moved to keep it's value from being overwritten 
                int element = arr[j][k];

                //Take the elements from the left side of the ring, and move them to the top
                arr[j][k] = arr[rows - k -1][j];

                //Take the elements from the bottom and add them to the left
                arr[rows - k -1][j] = arr[rows - j - 1][rows - k - 1];

                //Take the elements from the right side and move them to the bottom
                arr[rows - j -1][rows - k - 1] = arr[k][rows - j - 1];

                //Move the saved element to the right 
                arr[k][rows - j -1] = element;
            }
        }
    }

    // Output the rotated array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
	    if(arr[i][j] == 0)
	      printf(" ");
	    else
	      printf("%d", arr[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_file> <input_angle_degrees>\n", argv[0]);
        return 1;
    }

    char *inputFileName = argv[1];
    int rotationAngle = atoi(argv[2]);
    int arr[10][10] = {0};  // Initialize the array with zeros
    int rows = 0, cols = 0;
    char inputChar;

    // Read the input array from the specified file
    FILE *file = fopen(inputFileName, "r");
    if (file == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Read the input array character by character
    while (rows < 10 && (inputChar = fgetc(file)) != EOF) {
        if (inputChar == '\n') {
            rows++;
            cols = 0;
        } else if (cols < 10 && inputChar >= '0' && inputChar <= '9') {
            arr[rows][cols++] = inputChar - '0';
        }
    }

    fclose(file);

    printf("A%s\n", a_num);
    
    // Determine the actual dimensions of the input array
    if (cols == 0) {
        cols = 10;
    }

    printf("Input array:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
	    if(arr[i][j] == 0)
	      printf(" ");
	    else
	      printf("%d", arr[i][j]);
        }
        printf("\n");
    }

    printf("\nRotated array (%d degrees):\n", rotationAngle);
    rotateArray(arr, rotationAngle, rows, cols);

    return 0;
}
