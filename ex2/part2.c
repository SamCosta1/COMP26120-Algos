#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int main(int argc, char **argv)
{
    int numToUpperCase = 0,
        numToLowerCase = 0,
        chr;

    char *inputFilename = "input.txt",
         *outputFilename = "output.txt";
    printf("\n");

    // Open input and output file streams

    // ---- Taken from SalaryAnalysis.c --- //

    FILE *inputStream= fopen(inputFilename, "r");
    if (!inputStream) {
        fprintf(stderr, "can't open %s \n", inputFilename);
        exit(-1);
    }

    FILE *outputStream= fopen(outputFilename, "w");
    if (!outputStream) {
        fprintf(stderr, "can't open %s \n", outputFilename);
        exit(-1);
    }


    // ------------------------------- //

    // Loop through input until end of file
    while ((chr = fgetc(inputStream)) != EOF) {
        if (isupper(chr)) {
            numToUpperCase++;
            fprintf(outputStream, "%c", tolower(chr));
        }
        else {
            numToLowerCase++;
            fprintf(outputStream, "%c", toupper(chr));
        }
    }

    // print out summary to file
    fprintf(outputStream,
            "\nRead %d characters in total, %d converted to"
            "upper-case, %d to lower case\n",
            numToUpperCase + numToLowerCase,
            numToUpperCase,
            numToLowerCase);

    fclose(inputStream);
    fclose(outputStream);
    return 0;
}
