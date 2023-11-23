#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Add the two numbers
void logicalLadder(char *ptrNumOne, char *ptrNumTwo, size_t nbytes) {
    char tempOne[nbytes];
    char tempTwo[nbytes];

    // Copy the command line numbers into the char arrays since we do not know the type 
    memcpy(numOne, ptrNumOne, nbytes);
    memcpy(numTwo, ptrNumTwo, nbytes);

    // Get bit represenation of numbers
    long numOne = atol(tempOne);
    long numTwo = atol(tempTwo);

}

// Use bidwitdth to detect overflow 
detectOverFlow() {

}


// Drives the program
int main(int argc, char *argv[]) {
    
    // Checks if the number of command line arguments are correct 
    if (argc != 5) {
        perror("You need the correct number of command line arguments !");
        return 1;
    }

    int bitwidth = atoi(argv[1]);

    // Check if the bitwidth is the correct number 
    if (bitWidth != 8 && bitWidth != 16 && bitWidth != 32 && bitWidth != 64) {
        perror("Bitwidth must be: 8, 16, 32 or 64");
        return 1;
    }

    // Calculate the size needed based on the bitwidth
    size_t nbytes = bitwidth / 8;

    // Shift number
    int shift = atoi(argv[4]);

    //Preform the addition 
    logicalLadder(argv[2], argv[3], nbytes);
    // logicalLadder(&numOne, &numTwo, nbytes);

    return 0;
}

