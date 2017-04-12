#include "graph.h"

void printLargestOutDegree(Graph* graph) {
   int i = 0;
   int largestOut = 0;
   int largestOutIndex = 0;
   for (i = 0; i < graph->maxSize; i++)
      if (graph->table[i].outdegree > largestOut) {
         largestOut = graph->table[i].outdegree;
         largestOutIndex = i;
      }

      printf("Node %d has largest out degree: %d\n", largestOutIndex, largestOut);
}

void printInDegreeStats(Graph* graph) {
   int i = 0;
   int largestIn = 0;
   int largestInIndex = 0;

   int lowestInIndex = 0;
   int lowestIn = 0;

   for (i = 0; i < graph->maxSize; i++) {
      if (graph->table[i].indegree > largestIn) {
         largestIn = graph->table[i].indegree;
         largestInIndex = i;
      }

      if (graph->table[i].indegree == 0)
         continue;

      if (lowestIn == 0) {
         lowestIn = graph->table[i].indegree;
         continue;
      }

      if (graph->table[i].indegree < lowestIn){
         lowestIn = graph->table[i].indegree;
         lowestInIndex = i;
      }

   }

   printf("Node %d has largest in degree:     %d\n", largestInIndex, largestIn);
   printf("Node %d has lowset (!0) in degree: %d\n", lowestInIndex, lowestIn);
}

void printStats(Graph* graph) {
   printLargestOutDegree(graph);
   printInDegreeStats(graph);
}

int main(int argc,char *argv[])
{
  Graph mygraph;
  read_graph(&mygraph,argv[1]);
  printStats(&mygraph);

  return(0);

}
