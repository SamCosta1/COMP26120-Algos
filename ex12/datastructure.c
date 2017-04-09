#include "graph.h"

typedef struct heap {
    int* arr;  
    Graph *graph;  
    int size;
} heap;

heap h;


int parent(int index) {
    return (index - 1) / 2;
}

int leftChild(int index) {
    return 2 * index + 1;
}

int rightChild(int index) {
    return 2 * index + 2;
}

int compareTo(int nodeIndex1, int nodeIndex2) {
    int distance1 = h.graph->table[nodeIndex1].distanceKey;
    int distance2 = h.graph->table[nodeIndex2].distanceKey;

    return distance1 - distance2;
}

int min(int a, int b) {
    return compareTo(h.arr[a], h.arr[b]) <= 0 ? a : b;
}


void upheap_bubble(int index) {
    int currentNode = h.arr[index];
    while (index > 0 && compareTo(h.arr[index], h.arr[parent(index)]) < 0) {
        h.arr[index] = h.arr[parent(index)];
        index = parent(index);
    }

    h.arr[index] = currentNode;

}

void downheap_bubble() {
   int index = 0;
   while (compareTo(h.arr[index], h.arr[leftChild(index)]) > 0
            || compareTo(h.arr[index], h.arr[rightChild(index)]) > 0 ) {
        
        int minChild = min(leftChild(index), rightChild(index));
        int tmp = h.arr[index];
        h.arr[index] = h.arr[minChild];
        h.arr[minChild] = tmp;

        index = minChild;

        // if this has no children
        if (leftChild(index) >= h.size || rightChild(index) >= h.size)
            break;
   }

}


void initHeap(Graph *graph) {
    h.size = 0;
    h.arr = malloc(sizeof(int) * graph->maxSize);
    h.graph = graph;
    for (int i = 0; i < graph->maxSize; i++) {
        h.arr[i] = -1;
    }
}

int sizeOfStructure() {
    return h.size;  
}


int pop() {
    int min = h.arr[0];
    h.arr[0] = h.arr[h.size - 1];
    h.size--;
    downheap_bubble();
    return min;
}

void push(int index) {
    h.arr[h.size] = index;
    upheap_bubble(h.size);
    h.size++;
}

void printHeap() {
    for (int i = 0; i < h.size; i++)
        printf("[%4d] ", h.arr[i]);
}