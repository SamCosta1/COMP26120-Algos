#include <stdio.h>
#include <ctype.h>
int main(int argc, char **argv)
{
    int numToUpperCase = 0,
        numToLowerCase = 0,
        chr;
    printf("\n");

    // Loop through input until terminated
    while((chr = getchar()) != EOF) {
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

    return 0;
}
