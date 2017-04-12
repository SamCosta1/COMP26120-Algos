#include "graph.h"

void print_path(List *path) {
   while (path != NULL) {
     printf("%d ", path->index);

     if (path->index == -1)
        printf("\nNo Path was found :( ");
     
     path = path->next;

     if (path !=NULL)
       printf("-> ");
   }
   printf("\n");
}

int isAdjacentTo(int source, int target, Graph* graph) {  
    List *current = graph->table[source].outlist;
    while (current!=NULL) {
        if (current->index == target)
          return TRUE;
        current = current->next;
    }

    return FALSE;
}

void addToPath(List* path, int node) {
   List* current = path;
   while (current->next != NULL) 
      current = current->next;
   
   current->next = malloc(sizeof(struct linkedlist));
   current->next->index = node;
}

int max(List* outlist, Graph* graph) {
   List* current = outlist;
   int max = -1;
   int maxIndex = -1;
   while (current->next != NULL) {
      if (isInExploredList(current->index)) {
        current = current->next;
        continue;
      }

      if (max < graph->table[current->index].outdegree)
         maxIndex = current->index;
      
      current = current->next;
   }

   return maxIndex;
}

List* pathFind(int source, int target, Graph* graph) {
    initExploredList(graph->maxSize);

    List* path = malloc(sizeof(struct linkedlist));
    path->index = source;
  
    int current = source;

    while (!isAdjacentTo(current, target, graph) 
              && graph->table[current].outdegree > 0) {
       int next = max(graph->table[current].outlist, graph);

       if (next < 0) // Can't find path
          break;

       addToExploredList(next);
       addToPath(path, next);
       current = next;
    }

    if (isAdjacentTo(current, target, graph))
       addToPath(path, target);
    else 
       addToPath(path, -1);

    return path;
}

int main(int argc,char *argv[]) {
  Graph myGraph;
  read_graph(&myGraph,argv[1]);
  
  List* path = pathFind(712, 9, &myGraph);

  print_path(path);
  
  return(0);
}
