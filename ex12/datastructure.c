#include "graph.h"

struct heapNode {
    struct heapNode* left;
    struct heapNode* right;
    
    int node;
};
typedef struct heapNode* HeapNode;

typedef struct heap {
    HeapNode tree;
    HeapNode end_ptr;
    int size;
} heap;

heap h;

void copy_array(int *from, int *to);
void increaseListSize();


void initHeap() {
    h.size = 0;
}
HeapNode newNode(int index) {
    HeapNode new = malloc(sizeof(struct heapNode));
    new->node = index;
    return new;
}

int sizeOfStructure() {
    return h.size;  
}


int pop() {
    return 0;
}

void push(int index) {
    if (sizeOfStructure() == 0)
        h.tree = newNode(index);
    
}
