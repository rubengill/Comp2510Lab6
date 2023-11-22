#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the maximum number of characters a line can hold, including the terminating null character
#define MAX_LINE_LEN 100

// Function to reverse the order of words in a given string
void reverse_words(char* str, int len) {
    // Base case: if the string is empty (length is 0 or negative), we can't reverse anything
    if (len <= 0) {
        return;
    }

    // Initialize a variable to store the index of the last space found in the string
    int last_space = -1;

    // Traverse the string from the beginning to search for spaces
    for (int i = 0; i < len; i++) {
        if (str[i] == ' ') {
            // Update the index whenever a space is found
            last_space = i;
        }
    }

    // If the string has no spaces, it means it contains only one word
    if (last_space == -1) {
        // Print the single word and return
        printf("%s", str);
        return;
    }

    // If a space was found, print the word following that space (substring starting after the space)
    printf("%s ", &str[last_space + 1]);

    // Split the string into two parts: terminate at the last space found
    str[last_space] = '\0';

    // Recurse on the first part of the string to reverse the order of the preceding words
    reverse_words(str, last_space);
}

// Recursive function to reverse the order of lines in an array of strings
void reverse_rows(char** lines, int rows) {
    // Base case: if no rows are left, return immediately
    if (rows <= 0) {
        return;
    }

    // Reverse the words within the current row
    reverse_words(lines[rows - 1], strlen(lines[rows - 1]));

    // Print a newline to separate the output of different rows
    printf("\n");

    // Recurse for the remaining rows
    reverse_rows(lines, rows - 1);
}

int main() {
    // Attempt to open the input file in read mode
    FILE *fp = fopen("input.txt", "r");
    
    // If the file couldn't be opened, print an error message and terminate
    if (!fp) {
        perror("Error opening input.txt");
        return 1;
    }

    // Count the total number of rows (lines) read from the file
    int total_rows = 0;

    // Create a pointer for an array of strings. This will be dynamically allocated as we read lines from the file.
    char** lines = NULL;

    // Allocate a fixed-size buffer on the stack to hold a single line from the file as it's read
    char buffer[MAX_LINE_LEN];

    // Read each line from the file into the buffer
    while (fgets(buffer, sizeof(buffer), fp)) {
        // If the line ends with a newline character, replace it with a null terminator to form a proper string
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
        }

        // Allocate memory for a new bigger array
        char** new_lines = malloc((total_rows + 1) * sizeof(char*));

        // Copy pointers from the old array to the new array
        for (int i = 0; i < total_rows; i++) {
            new_lines[i] = lines[i];
        }

    // Free the old array
    free(lines);

    // Update the lines pointer to point to the new array
    lines = new_lines;

    // Duplicate the content of the buffer and store the pointer in the `lines` array
    lines[total_rows] = strdup(buffer);

    total_rows++;
}

    fclose(fp);

    reverse_rows(lines, total_rows);

    // Cleanup: free the memory allocated for each line and the lines array itself
    for (int i = 0; i < total_rows; i++) {
        free(lines[i]);
    }
    free(lines);

    return 0;
}
