#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

unsigned long hcf(unsigned long a, unsigned long b) {
    if (b == 0)
        return a;
    else
        return hcf(b, a % b);
}

unsigned long fme(unsigned long primitiveRoot, unsigned long exponent,
                  unsigned long prime) {
    unsigned long d = primitiveRoot;
    unsigned long e = exponent;
    unsigned long accumulator = 1;

    while (e != 0) {
        if ((e % 2) != 0)
            accumulator = (accumulator * d) % prime;
        d = (d * d) % prime;
        e = e / 2;
    }

    return accumulator;
}

void testfme() {
    printf("%lu^%lu mod %lu | %lu\n", 5, 15, 7, fme(5,15,7));
    printf("%lu^%lu mod %lu | %lu\n", 3, 10, 17, fme(3, 10, 17));
    printf("%lu^%lu mod %lu | %lu\n", 3, 12, 257, fme(3, 12, 257));
    printf("%lu^%lu mod %lu | %lu\n", 2, 62, 443, fme(2, 62, 443));
    printf("%lu^%lu mod %lu | %lu\n", 2, 34, 4093082899, fme(2, 34, 4093082899));

}
int main(int argc, char **argv) {
    testfme();
}
