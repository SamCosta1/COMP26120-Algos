#include "graph.h"

int main(int argc,char *argv[])
{
  Graph mygraph;
  read_graph(&mygraph,argv[1]);
  print_graph(&mygraph);
  /* you take it from here */

  return(0);
}
