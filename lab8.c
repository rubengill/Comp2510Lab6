#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Add the two numbers
void logicalLadder(void *ptrNumOne, void *ptrNumTwo, size_t nbytes) {
    long numOne = 0;
    long numTwo = 0;
    long carry = 0;

    // Copy data 
    memcpy(&numOne, ptrNumOne, nbytes);
    memcpy(&numTwo, ptrNumTwo, nbytes);

    // Perform addition 
    while (numTwo != 0) {
        carry = numOne & numTwo;
        numOne = numOne ^ numTwo;
        numTwo = carry << 1;
    }

    // ptrNumOne points to added result
    memcpy(ptrNumOne, &numOne, nbytes);
}

// Use bidwitdth to detect overflow 
void detectOverFlow(void *resultPtr, int bitwidth, int shift, size_t nbytes) {
    long result = 0;
    memcpy(&result, resultPtr, nbytes);

    long maxVal = (1L << (bitwidth - 1)) - 1;
    long minVal = -(1L << (bitwidth - 1));

    // Check for overflow
    if (result > maxVal || result < minVal) {
        result >>= shift;
        printf("Result after right shift: %ld\n", result);
        printf("Overflow detected within the specified %d-bit width\n", bitwidth);
    } else {
        printf("Result of addition: %ld\n", result);
    }

    // Copy the result back to the pointer
    memcpy(resultPtr, &result, nbytes);
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
    if (bitwidth != 8 && bitwidth != 16 && bitwidth != 32 && bitwidth != 64) {
        printf("Bitwidth must be: 8, 16, 32 or 64");
        return 1;
    }

    short numOne = atol(argv[2]);
    short numTwo = atol(argv[3]);

    // Shift number
    int shift = atoi(argv[4]);

    logicalLadder(&numOne, &numTwo, sizeof(short));

    // Detect and handle overflow
    detectOverFlow(&numOne, bitwidth, shift, sizeof(short));

    return 0;
}
