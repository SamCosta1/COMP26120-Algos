#include "graph.h"
#include "datastructure.h"


void processNode(Node n, int index) {
    printf("Node: %d %s\n", index, n.name);
}

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

void addChildren(int index, Graph *graph) {
    List *current = graph->table[index].outlist;
    while (current!=NULL) {
        if (!isInExploredList(current->index)) {
            addToExploredList(current->index);
            push(current->index);
        }
        current = current->next;
    }
}

void searchFromNode(int index, Graph *graph) {
    initStructure(graph->maxSize);
    initExploredList(graph->maxSize);


    push(index);
    addToExploredList(index);
    
    while (sizeOfStructure() > 0) {
        int top = pop();       
        processNode(graph->table[top], top);

        addChildren(top, graph); // Add the children of the node to the datastructure
     }   
}