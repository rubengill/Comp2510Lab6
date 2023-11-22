#include <stdio.h>
#include <stdlib.h>

// Function to rotate a 2D array by a given angle (in degrees)
void rotateArray(char **arr, int n, int rows, int cols) {
    
    int size = n;
    // Divide the command line int by 90 to determine how many times by 
    //90 to rotate the matrix 
    int rotations = n / 90;

    // If rotations > 0, rotate the array clockwise, if not then counter clockwise 
    if (rotations >= 0) {
        //Rotate the matrix according to the rotations number
        for (int i = 0; i < rotations; i++) {
            //j < rows / 2 determines how many rings the matrice contains
            for (int j = 0; j < rows / 2; j++) {
                //Iterate over the elements in the side of the current ring in the matrix
                //and stop at the last element 
                for (int k = j; k < rows - j - 1; k++) {

                    // Save the first element being moved to keep it's value from being overwritten 
                    char element = arr[j][k];

                    //Take the elements from the left side of the ring, and move them to the top, -1 to deal with array indexing 
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
    } else { 
        // Use the absolute value of the rotations if it is negative for the loop calculations
        for (int i = 0; i < abs(rotations); i++) {
            for (int j = 0; j < rows / 2; j++) {
                for (int k = j; k < rows - j - 1; k++) {
                
                    // Save the top side of the ring to avoid overwriting
                    char element = arr[j][k];

                    // Take the elements from the right and move them to the top
                    arr[j][k] = arr[k][rows - j - 1];

                    // Take the elements from the bottom and move them to the right
                    arr[k][rows - j - 1] = arr[rows - j - 1][rows - k - 1];

                    // Take the elements from the left side and move them to the bottom
                    arr[rows - j - 1][rows - k - 1] = arr[rows - k - 1][j];

                    // Move the saved element to the left
                    arr[rows - k - 1][j] = element;
                }
            }
        }
    }
}

// Function to zoom (expand or shrink) a 2D array by a given factor
void zoomArray(char **arr, double zoomFactor, int *rows, int *cols) {
    
    if (zoomFactor == 0) {
        return;
    }
    
    // Logic for if the array is being enlarged (zoomed out) 
    if (zoomFactor >= 1.0) {

        //Cast to a double since we need the int value for row and column calculations
        int zoomOut = (int) zoomFactor;

        //Point to the new row and column number so the correct array is printed
        *rows = *rows * zoomOut;
        *cols = *cols * zoomOut;

        //Start from the bottom right of the array and iterate backwards
        for (int i = *rows - 1; i >= 0; --i) {
            for (int j = *cols -1; j >= 0; j--) {
                //Element that will be duplicated
                char element = arr[i][j];

                //Determine how many times to duplicate the element
                for (int x = 0; x < zoomOut; x++) {
                    for (int y = 0; y < zoomOut; y++) {
                        //Place in correct array position
                        arr[i * zoomOut + x][j * zoomOut + y] = element;
                    }
                }
            }
        }

    } else { 
        //Factor to shrink the array 
        int zoomFactorIn = (int) (1.0 / zoomFactor);
        //Keep track of indices of zoomed out array
        int newRow = 0;
        int newCol = 0;

        //Iterate over the array selecting the correct element (determined by zoomFactorIn)
        for (int i = 0; i < *rows; i += zoomFactorIn) {
            //Reset after each row 
            newCol = 0;
            for (int j = 0; j < *cols; j += zoomFactorIn) {
                //Assign element to the zoomed in array
                arr[newRow][newCol] = arr[i][j];
                newCol++;
            }
            newRow++;
        } 

        //Point to the new row and column number so the correct array is printed 
        *rows = newRow;
        *cols = newCol;
    }   
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <input_file> <angle_degrees> <zoom_factor>\n", argv[0]);
        return 1;
    }

    char *inputFileName = argv[1];
    int angle = atoi(argv[2]);
    double zoomFactor = atof(argv[3]); // Use atof to convert the zoom factor to a double

    // Initialize a 2D array of size 30x30 as a pointer-to-pointer
    char **arr = (char **)malloc(30 * sizeof(char *));
    for (int i = 0; i < 30; i++) {
        arr[i] = (char *)malloc(30 * sizeof(char));
    }

    // Open the input file for reading
    FILE *file = fopen(inputFileName, "r");
    if (file == NULL) {
        printf("Failed to open the input file.\n");
        return 1;
    }

    // Read the input array from the specified file and populate arr
    int rows = 0;
    int cols = 0;
    char c;

    while (rows < 30 && cols < 30 && fscanf(file, "%c", &arr[rows][cols]) == 1) {
        if (arr[rows][cols] == '\n') {
          rows++;
          cols = 0;
        } else {
          cols++;
        }
    }
    cols = rows;
    
    // Close the input file
    fclose(file);

    // Print the array
    printf("Input Array:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          printf("%c ", arr[i][j]);
        }
        printf("\n");
    }

    
    // Call rotateArray or zoomArray based on the angle and zoomFactor
    // For example:
    rotateArray(arr, angle, rows, cols);
    zoomArray(arr, zoomFactor, &rows, &cols);

    // Print the array
    printf("Output %dx%d Array:\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          printf("%c ", arr[i][j]);
        }
        printf("\n");
    }

    // Free dynamically allocated memory when done
    for (int i = 0; i < 30; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}
