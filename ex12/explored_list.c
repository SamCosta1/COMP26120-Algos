#include "graph.h"

int *exploredList;
int endptr = 0;

void addToExploredList(int index) {
    exploredList[endptr++] = index;
}

int isInExploredList(int index) {
    int i = 0;
    for (i = 0; i <= endptr; i++)
        if (index == exploredList[i])
            return TRUE;

    return FALSE;
}

void initExploredList(int maxSize) {
    exploredList = malloc(maxSize * sizeof(int));
}