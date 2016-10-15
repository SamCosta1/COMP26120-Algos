#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float c2f (float c) {

    if (c <= -273.15){
        printf("Temperature below absolute 0\n");
        exit(-1);
    }
    return (c * 9/5) + 32;
}

float f2c (float f) {
    float c = (f - 32) * 5/9;

    if (c <= -273.15){
        printf("Temperature below absolute 0\n");
        exit(-1);
    }

    return c;
}

// Supply either -f flag followed by a valid farenheit value to convert to
// celcius, or -c flag followed by valid celcius value to convert to farenheit.
int main(int argc, char **argv) {

    // Handle errenous cases
    if (argc != 3) {
        printf("invalid parameters - to few supplied\n");
        exit(-1);
    } else if (strcmp(argv[1],"-f")  && strcmp(argv[1],"-c")) {
        printf("invalid parameters - unknown unit flag %s\n", argv[1]);
        exit(-1);
    }

    if (strcmp(argv[1], "-f") == 0) {
        float f;
        sscanf(argv[2], "%f", &f);
        printf("%f°C = %s°F\n", f2c(f), argv[2]);
    } else {
        float c;
        sscanf(argv[2], "%f", &c);
        printf("%s°C = %f°F\n", argv[2], c2f(c));
    }

    return 0;
}
