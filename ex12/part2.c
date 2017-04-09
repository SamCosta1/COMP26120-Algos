#include "graph.h"


int main(int argc,char *argv[]) {
  Graph myGraph;
  read_graph(&myGraph,argv[1]);

  dijkstra(9619, &myGraph);
  print_graph(&myGraph);
  
  return(0);

}