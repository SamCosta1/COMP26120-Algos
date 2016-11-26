#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

unsigned long hcf(unsigned long a, unsigned long b) {
    if (b == 0)
        return a;
    else
        return hcf(b, a % b);
}

int main(int argc, char **argv) {
    printf("%d %d | %d\n", 100, 1734128, hcf(100, 1734128));
}
