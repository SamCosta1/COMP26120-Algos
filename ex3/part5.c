#include <stdio.h>
#include <stdlib.h>

#define NUM_CHARS 255

// Takes file name as parameter and outputs the number of times each character
// appears.
int main(int argc, char **argv) {
    int charCounts[NUM_CHARS] = {0};
    char chr;
    int i;

    FILE *inputStream= fopen(argv[1], "r");
    if (!inputStream) {
        fprintf(stderr, "can't open %s \n", argv[1]);
        exit(-1);
    }

    // Loop through input until end of file
    while ((chr = fgetc(inputStream)) != EOF) {
        charCounts[chr]++;
    }

    // Print result
    for (i = 0; i < NUM_CHARS; i++)
        if (charCounts[i] > 0)
            printf("%3d instances of character 0x%02x (%c)\n", charCounts[i], i, i);

    fclose(inputStream);
    return 0;
}
