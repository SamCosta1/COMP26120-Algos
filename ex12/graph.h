#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include <string.h>
#define FALSE 0
#define TRUE 1

typedef struct linkedlist { // linked list of ints (for use in Node)
  int index ;
  struct linkedlist *next;
} List;

typedef struct { // a Node of a Graph
  char *name;
  List *outlist; // adjacency list
  int outdegree; // length of outlist
  int indegree; // Number of nodes pointing to this one
  int index;
  int distanceKey; // -1 used to denote infinity
  //double pagerank_score; //not needed for this exercise
} Node;

typedef struct {
   int maxSize;
   Node *table;
} Graph;

// use to check result of strdup, malloc etc.
extern void memoryCheck (void *memory);

extern int initialize_graph (Graph *mygraph, int MaxSize);
extern int insert_graph_node (Graph *mygraph, int n, char *name);
extern int insert_graph_link (Graph *mygraph, int source, int target);
extern int read_graph (Graph *mygraph, char *filename);
extern void dijkstra(int index, Graph *mygraph);
extern void print_graph (Graph *mygraph);

extern void addToExploredList(int index);
extern int isInExploredList(int index);
extern void initExploredList(int maxSize);
