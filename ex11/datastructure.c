#include "graph.h"
#define DFS
#undef BFS
void copy_array(int *from, int *to);
void increaseListSize();

int *list;
int listSize;
int ptr = 0;

// ------ QUEUE ----------------------------------

int queuePop() {
    int toReturn = list[0];
    int i;
    for (i = 1; i < listSize; i++)
        list[i-1] = list[i];
    ptr--;
    return toReturn;
}


void queuePush(int index) {
    list[ptr++] = index;
}

// ------ STACK ----------------------------------

int stackPop() {
    if (ptr <= 0)
        return -1;

    return list[--ptr];
}

void stackPush(int index) {
    list[ptr++] = index;
}


// Interface Functions  --------------------------

int sizeOfStructure() {
    return ptr;    
}

void initStructure(int maxSize) {
    list = malloc(maxSize * sizeof(int));
    listSize = maxSize;
}


int pop() {
    #ifdef BFS
        return queuePop();
    #endif

    #ifdef DFS
        return stackPop();
    #endif

    // Should never happen
    return -1;
}

void push(int index) {
    #ifdef BFS
        queuePush(index);
    #endif

    #ifdef DFS
       stackPush(index);
    #endif
}