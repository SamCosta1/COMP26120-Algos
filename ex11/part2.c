#include "graph.h"


int main(int argc,char *argv[]) {
  Graph myGraph;
  read_graph(&myGraph,argv[1]);

  searchFromNode(7, &myGraph);
  return(0);

}