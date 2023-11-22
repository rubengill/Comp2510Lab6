#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Failed to open the file: %s\n", filename);
        return 1;
    }

    char line[256]; // Buffer to hold each line

    // Read and print each line in the file
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    // Close the file when done
    fclose(file);

    return 0;
}
