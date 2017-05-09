#include "graph.h"

int isSmallWorldNetwork(Graph *graph) {
    int maxDistance = 0; //  Maximum non infinate distance
    for (int i = 1; i < graph->maxSize; i++) {
       // printf("Running: %d\n", i); fflush(stdout);
        dijkstra(i, graph);
        for (int j = 1; j < graph->maxSize; j++) {
            if (graph->table[j].distanceKey > maxDistance)
                maxDistance = graph->table[j].distanceKey;
            
            if (maxDistance > 6)
                return FALSE;
        }
    }

    return TRUE;
}
int main(int argc,char *argv[]) {
  Graph myGraph;
  read_graph(&myGraph,argv[1]);

  if (isSmallWorldNetwork(&myGraph) == TRUE)
     printf("It is a small world network\n");
  else
     printf("It ain't a small world network\n");
 
  //print_graph(&myGraph);
  
  return(0);

}