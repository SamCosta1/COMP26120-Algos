#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 100

const unsigned long PRIMITIVE_ROOT = 3;
const unsigned long PRIME = 65537;
unsigned long publicKey = -1;

void memoryCheck(void *ptr) {
    if (ptr == NULL) {
        printf("Memeory issue");
        exit(0);
    }
}

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
    if (y < 1 || y >= prime)
        return -1;

    unsigned long x = 1;
    while (fme(pRoot, x, prime) != y && x < prime) {
        x++;
    }

    if (x >= prime)
        return -1;

    return x;
}

unsigned long imp(unsigned long y, unsigned long prime) {
    if (y >= 1 && y < prime)
        return fme(y, 20, prime);
    else
        return -1;
}
void testfme() {
    printf("%d^%d mod %d = %lu\n", 5, 15, 7, fme(5,15,7));
    printf("%d^%d mod %d = %lu\n", 3, 10, 17, fme(3, 10, 17));
    printf("%d^%d mod %d = %lu\n", 3, 12, 257, fme(3, 12, 257));
    printf("%d^%d mod %d = %lu\n", 2, 62, 443, fme(2, 62, 443));
    printf("%d^%d mod %lu = %lu\n", 2, 16000000, 4093082899, fme(2, 16000000, 4093082899));
    printf("\n");
}

void testdl() {
    printf("%d^%lu mod %d = %d\n", 5, dl(6, 5, 7), 7, 6);
    printf("%d^%lu mod %d = %d\n", 3, dl(8, 3, 17), 17, 8);
    printf("%d^%lu mod %d = %d\n", 3, dl(222, 3, 257), 257, 222);
    printf("%d^%lu mod %lu = %lu\n", 2, dl(2952904674, 2, 4093082899), 4093082899,  2952904674);
    printf("\n");
}

void testSingleimp(int a, int p) {
    unsigned long ans = imp(a,p);
    printf("%s\n", (ans * a) % p == 1 ? "Test Succeeded" : "Test Failed");
}

char *newInput;
char *getRawInput() {
    char *data = malloc(BUFFER_SIZE);
    memoryCheck(data);
    fgets(data, BUFFER_SIZE, stdin);

    newInput = malloc(strlen(data) + 1);
    memoryCheck(newInput);
    sscanf(data, "%[^\n]", newInput); // Extract text before newline character
    free(data);
    return newInput;
}

void testimp() {
    testSingleimp(2,3);
    testSingleimp(52,127);
    testSingleimp(34,37);
    testSingleimp(26,31);
    printf("\n");
}

unsigned long getULInput() {
    char *str = getRawInput();
    char *ptr;
    return strtoul(str, &ptr, 10);
}
void printPrompt() {
    printf("Prime modulus is %lu\n"
           "Primitive root wrt %lu is %lu\n"
           "Choose: e (encrypt) | d (decrypt) |k (get public key) | x (exit)?)\n",
            PRIME, PRIMITIVE_ROOT, PRIME);
}

void getPublicKey() {
    printf("Type private key (between 1 and %lu): ", PRIME);
    unsigned long privateKey = getULInput();

    if (privateKey < 1 || privateKey >= PRIME) {
        printf("Invalid Input\n\n");
        getPublicKey();
    }

    publicKey = fme(PRIMITIVE_ROOT, privateKey, PRIME);
    printf("Public key is %lu\n\n", publicKey);
}

void decrypt() {
    printf("Type recieved message in form (a,b): ");
    unsigned long a;
    unsigned long b;
    unsigned long privateKey;
    unsigned long aToPowerKey;

    char *input = getRawInput();
    sscanf(input, "(%lu,%lu)", &a, &b);
    printf("Type in private key: ");

    privateKey = getULInput();
    
    aToPowerKey = fme(a, privateKey, PRIME);

    if (aToPowerKey <= 0) {
        // Should never happen
        printf("Error - Please try again\n");
    } else {
        unsigned long message = b / aToPowerKey;
        printf("The decrypted secret is: %lu\n\n", message);
    }
}
void encrypt() {
    printf("Input a message (between 1 and %lu): ", PRIME);
    unsigned long message = getULInput();
    if (message < 1 || message >= PRIME) {
        printf("Invalid Input\n\n");
        encrypt();
    }

    // Note: this is not considered cryptographically secure but should suffice
    // for a lab exercise
    int random = rand() % PRIME;

    if (publicKey == -1)
        getPublicKey();

    // a & b make up the integer secret pair (a, b) to return to user
    unsigned long a = fme(PRIMITIVE_ROOT, random, PRIME);
    unsigned long b = message * fme(publicKey, random, PRIME);


    printf("The secret number to send: %lu\n", message);
    printf("The recipiant's public key: %lu\n\n", publicKey);
    printf("Encrypted secret is: (%lu, %lu)\n\n\n", a, b);
}
void cryptoInterface() {
    // Seed the random number genererator
    time_t t;
    srand((unsigned) time(&t));

    int finished = 0;
    while(!finished) {
        printPrompt();
        printf("Enter an option (e | d | k | x)\n");
        char *choice = getRawInput();

        if (strcmp(choice, "x") == 0)
            finished = 1;
        else if (strcmp(choice, "e") == 0)
            encrypt();
        else if (strcmp(choice, "d") == 0)
            decrypt();
        else if (strcmp(choice, "k") == 0)
            getPublicKey();
    }
}

int main(int argc, char **argv) {
 /*   testfme();
    testdl();
    testimp();*/
    
     printf("%d^%d mod %d = %lu\n", 5, 15, 7, fme(40781,40000,65537));
    cryptoInterface();
}
