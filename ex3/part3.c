#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prog takes list of paramaters and prints out the longest by character count
// if two params are equal in length the first is printed.
int main(int argc, char **argv) {
    int i;
    if (argc < 2) {
        printf("Invalid parameters\n");
        exit(-1);
    }

    int maxLengthIndex = 1;

    for (i = 2; i < argc; i++) {
        if (strlen(argv[maxLengthIndex]) < strlen(argv[i]))
            maxLengthIndex = i;
    }

    printf("Longest param is \"%s\"\n", argv[maxLengthIndex]);

    /////// Newlines added for ease of marking //////
    printf("\n\n");
    return 0;
}
