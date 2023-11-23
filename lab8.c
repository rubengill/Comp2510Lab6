#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Add the two numbers
void logicalLadder(void *ptrNumOne, void *ptrNumTwo, size_t nbytes) {
    char numOne[nbytes];
    char numTwo[nbytes];
    //char result[nbytes]
    char carry = 0;

    // Copying data from pointers to local arrays
    memcpy(numOne, ptrNumOne, nbytes);
    memcpy(numTwo, ptrNumTwo, nbytes);

    for (size_t i = 0; i < (nbytes); ++i) {
        char result = numOne[i] ^ numTwo[i] ^ carry;
        //Iterates through each bit in the byte
        carry = (numOne[i] & numTwo[i]) | (numOne[i] & carry) | (numTwo[i] & carry);
        numOne[i] = result;
    }

    // Copy the result back to ptrNumOne
    memcpy(ptrNumOne, numOne, nbytes);
}


// Use bidwitdth to detect overflow 
void detectOverFlow(void *resultPtr, int bitwidth, int shift, size_t nbytes) {
    long result = 0;
    memcpy(&result, resultPtr, nbytes);

    long maxVal = (1L << (bitwidth - 1)) - 1;;
    long minVal = -(1L << (bitwidth - 1));;

    // Check for overflow
    if (result > maxVal || result < minVal) {
        printf("Overflow detected within the specified %d-bit width\n", bitwidth);
        // Perform right shift
        result >>= shift;
        printf("Result after right shift: %ld\n", result);
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
    if (bitWidth != 8 && bitWidth != 16 && bitWidth != 32 && bitWidth != 64) {
        perror("Bitwidth must be: 8, 16, 32 or 64");
        return 1;
    }

    long numOne = atol(argv[2]);
    long numTwo = atol(argv[3]);

    // Shift number
    int shift = atoi(argv[4]);

    // Calculate the size needed based on the bitwidth
    size_t nbytes = bitwidth / 8;

    //Preform the addition 
    logicalLadder(&numOne, &numTwo, nbytes);

    return 0;
}
