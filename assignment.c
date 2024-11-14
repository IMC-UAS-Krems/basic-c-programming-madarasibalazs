#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // initialize random number generator
    srand(time(NULL));
    int minrand = 1;
    int maxrand = 100;

    // Subtask 1: checking the number of arguments
    if (argc != 3) {  // checking if argc does not equal 3 --> I have to check it with 3 since argc includes the program name as the first argument 
        printf("Incorrect usage. You provided %d arguments. The correct number of arguments is 2\n", argc-1); // The -1 is needed because argc includes the program name as the first argument 
        return 0;
    }
    
    // Subtask 2: checking whether the arguments are positive integers or not
    for (int i = 1; i < argc; i++) {
        char *end;
        long val = strtol(argv[i], &end, 10); // Convert the argument to a long integer

        // Check if conversion is successful and if value is greater than 0
        if (*end != '\0' || val <= 0) {
            printf("Incorrect usage. The parameters you provided are not positive integers\n");
            return 0;
        }
    }

    // Subtask 3: creating the matrix based on the arguments
    int nrows = (int)strtol(argv[1], NULL, 10);  // Number of rows
    int ncols = (int)strtol(argv[2], NULL, 10);  // Number of columns

    // Memory allocation
    int **theArray = (int**) malloc(nrows * sizeof(int*));
    for (int i = 0; i < nrows; i++) {
        theArray[i] = (int*) malloc(ncols*sizeof(int));
    }

    // Fill the matrix with random values between 1 and 100
    for(int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; j++) {
            theArray[i][j] = minrand + rand() % (maxrand - minrand + 1);
        }
    }

    // Print the matrix to the console (this is just for myself, solely for testing purposes)
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            printf("%d\t", theArray[i][j]);
        }
        printf("\n");
    }

    // Subtask 4: creataing the "matrix.txt" file ad writing the matrix inside
    FILE *pFile = NULL;
    pFile = fopen("matrix.txt", "w"); // Opening the file in write mode
    if (pFile == NULL) {
        printf("Failed to open file 'matrix.txt'\n");
        return -1;
    }
    
    // Writing the matrix to the file
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            fprintf(pFile, "%d", theArray[i][j]); // Write the current value
            if (j < ncols - 1) {
                fprintf(pFile, " "); // Add space between numbers, except the last one in each row
            }
        }
        fprintf(pFile, "\n");
    }
    fclose(pFile);

    
    // Free allocated memory AFTER writing in the file (free each row and then the array of row pointers)
    for (int i = 0; i < nrows; i++) {
        free(theArray[i]);
    }
    free(theArray);

    return 0;
}
