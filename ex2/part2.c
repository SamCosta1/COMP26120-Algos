#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int main(int argc, char **argv)
{
    int numToUpperCase = 0,
        numToLowerCase = 0,
        chr;

    char *filename = "input.txt";
    printf("\n");

    // ---- Taken from SalaryAnalysis.c --- //

    // A stream for getting data from the user.
    FILE *stream= fopen(filename, "r");
    if (!stream) {
        fprintf(stderr, "can't open %s for reading\n", filename);
        exit(-1);
    }

    // ------------------------------- //

    // Loop through input until terminated
    while ((chr = fgetc(stream)) != EOF) {
        if (isupper(chr)) {
            numToUpperCase++;
            putchar(tolower(chr));
        }
        else {
            numToLowerCase++;
            putchar(toupper(chr));
        }
    }

    printf( "\nRead %d characters in total, %d converted to"
            "upper-case, %d to lower case\n",
            numToUpperCase + numToLowerCase,
            numToUpperCase,
            numToLowerCase);

    fclose(stream);
    return 0;
}
