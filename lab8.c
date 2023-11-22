#include <stdio.h>
#include <stdlib.h>
#include <string.h>




// Drives the program
int main(int argc, char *argv[]) {
    
    // Checks if the number of command line arguments are correct 
    if (argc != 5) {
        perror("You need the correct number of command line arguments !");
        return 1;
    }

    // Command line args
    int bitwidth;
    int numOne;
    int numTwo;
    int shift;

    // Check if the bitwidth is the correct number 
    if (bitWidth != 8 || bitWidth != 16 || bitWidth != 32 || bitWidth != 64) {
        perror("Bitwidth must be: 8, 16, 32 or 64");
        return 1;
    }

}

