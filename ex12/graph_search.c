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

void initGraphDistances(Graph* graph) {
    for (int i = 0; i < graph->maxSize; i++)
        graph->table[i].distanceKey = -1;
}

int lessThan(int node, int adjNode) {
    // -1 denotes infinity 
    if (adjNode == -1)
        return TRUE;

    return node - adjNode < 0 ? TRUE : FALSE;
}

void addChildren(int index, Graph *graph) {
    if (index < 0)
        return;
    List *current = graph->table[index].outlist;
    while (current!=NULL) {
        if (!isInExploredList(current->index) && lessThan(graph->table[index].distanceKey + 1, graph->table[current->index].distanceKey)) {
            addToExploredList(current->index);
            graph->table[current->index].distanceKey = graph->table[index].distanceKey + 1;
            push(current->index);
        }
        current = current->next;
    }
}

void dijkstra(int index, Graph *graph) {
  
    initExploredList(graph->maxSize);
    initHeap(graph);
    initGraphDistances(graph);
    graph->table[index].distanceKey = 0;
    push(index);
    addToExploredList(index);
    
    while (sizeOfStructure() > 0) {
        int top = pop();              

        addChildren(top, graph); // Add the children of the node to the datastructure
     }   
}