#include <stdio.h>
#include <stdlib.h>
// Find largest integer in array and return it
int largest (int arrayLength, int* array) {
    if (array == NULL) {
        printf("Invalid array parameter\n");
        exit(-1);
    }

    // Start with assuming largest is first in array and loop through
    // updating only when a larger value found.
    int largest = array[0],
        i;
    for (i = 1; i < arrayLength; i++)
        if (array[i] > largest)
            largest = array[i];

    return largest;
}

int main(int argc, char **argv) {
    int test1[] = {0,1,2,3,4,5,6,7,8};
    int test2[] = {0,0,0,0,0,0};
    int test3[] = {-1,-123,-12312,-2,1,0,0,0,0};
    int test4[] = {4034,0,0,0,0,0,1,1};

    printf("Test1: %d\n", largest(9, test1));
    printf("Test2: %d\n", largest(6, test2));
    printf("Test3: %d\n", largest(9, test3));
    printf("Test4: %d\n", largest(8, test4));
    printf("Test5: %d\n", largest(6, NULL));
}
