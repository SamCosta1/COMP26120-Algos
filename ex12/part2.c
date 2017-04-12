#include "graph.h"

void print_path(List *path) {
   while (path != NULL) {
     printf("%d ", path->index);
     
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

int max(List* outlist) {
   List* current = outlist;
   int max = -1;
   while (current->next != NULL) {
      if (max < current->index)
         max = current->index;
      
      current = current->next;
   }

   return max;
}

List* pathFind(int source, int target, Graph* graph) {
    initExploredList(graph->maxSize);

    List* path = malloc(sizeof(struct linkedlist));
    path->index = source;
  
    int current = source;

    while (!isAdjacentTo(current, target, graph) 
              && graph->table[current].outdegree > 0
              && !isInExploredList(current)) {
       int next = max(graph->table[current].outlist);

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
  
  List* path = pathFind(1, 700, &myGraph);

  print_path(path);
  
  return(0);

}
