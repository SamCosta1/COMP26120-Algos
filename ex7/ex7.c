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

unsigned long dl(unsigned long y,unsigned long pRoot,unsigned long prime) {
    unsigned long x = 1;
    while (fme(pRoot, x, prime) != y) {
        x++;
    }
    return x;
}

unsigned long imp(unsigned long y, unsigned long p) {

}
void testfme() {
    printf("%d^%d mod %d = %lu\n", 5, 15, 7, fme(5,15,7));
    printf("%d^%d mod %d = %lu\n", 3, 10, 17, fme(3, 10, 17));
    printf("%d^%d mod %d = %lu\n", 3, 12, 257, fme(3, 12, 257));
    printf("%d^%d mod %d = %lu\n", 2, 62, 443, fme(2, 62, 443));
    printf("%d^%d mod %lu = %lu\n", 2, 16000000, 4093082899, fme(2, 16000000, 4093082899));
}

void testdl() {
    printf("%d^%lu mod %d = %d\n", 5, dl(6, 5, 7), 7, 6);
    printf("%d^%lu mod %d = %d\n", 3, dl(8, 3, 17), 17, 8);
    printf("%d^%lu mod %d = %d\n", 3, dl(222, 3, 257), 257, 222);
    printf("%d^%lu mod %lu = %lu\n", 2, dl(2952904674, 2, 4093082899), 4093082899,  2952904674);
}
int main(int argc, char **argv) {
    testfme();
    printf("\n");
    testdl();
}
