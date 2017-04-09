#include "graph.h"

void insertToLinkedList(List* list, int index);

int initialize_graph (Graph *myGraph, int maxSize) {
   myGraph->maxSize = maxSize;
   myGraph -> table = malloc(sizeof(Node) * maxSize);

   memoryCheck(myGraph);
   memoryCheck(myGraph -> table);
   return 0;

}

int insert_graph_node (Graph *myGraph, int n, char *name) {
   myGraph->table[n].name = strdup(name);
   myGraph->table[n].index = n;
   myGraph->table[n].outdegree = 0;
   myGraph->table[n].indegree = 0;
   myGraph->table[n].distanceKey = -1;

   return 0;
}


int insert_graph_link (Graph *myGraph, int source, int target) {

   if (myGraph->table[source].outlist == NULL) {
      myGraph->table[source].outlist = malloc(sizeof(List));
      memoryCheck(myGraph->table[source].outlist);
      myGraph->table[source].outlist -> index = target;
   }
   else
      insertToLinkedList(myGraph->table[source].outlist, target);

   myGraph->table[target].indegree++;
   myGraph->table[source].outdegree++;

   return 0;
}


void insertToLinkedList(List* list, int index) {

   // Case not at end of list
   if (list->next != NULL) {
      insertToLinkedList(list->next, index);
      return;
   }

   // Case we're at the end of list
   list->next = malloc(sizeof(List));  memoryCheck(list->next);
   list->next->index = index;
}

//-----------------------------------------------------------------

// use to check result of strdup, malloc etc.
void check (void *memory, char *message) {
  if (memory == NULL)   {
    fprintf (stderr, "Can't allocate memory for %s\n", message);
    exit (3);
  }
}

void memoryCheck(void *memory) {
   check(memory, "you messed up memory");
}


int read_graph (Graph *mygraph, char *filename) {
/*
 * Reads in graph from FILE *filename which is of .gx format.
 * Stores it as Graph in *mygraph.
 * Returns an error if file does not start with MAX command,
 * or if any subsequent line is not a NODE or EDGE command.
 * Does not check that node numbers do not exceed the maximum number
 * Defined by the MAX command.
 * 8/2/2010 - JLS
 */
  FILE *fp;
  char command[80], name[80];
  int i, s, t;
  fp= fopen (filename, "r");
  if (fp==NULL)
  {
    fprintf(stderr,"cannot open file %s\n", filename);
    return -1;
  }
  printf ("Reading graph from %s\n", filename);
  fscanf (fp,"%s", command);
  if (strcmp (command, "MAX")!=0)
  {
    fprintf (stderr, "Error in graphics file format\n");
    return -1;
  }
  else
  {
    fscanf (fp, "%d", &i);

    initialize_graph (mygraph, i+1); // +1 so nodes can be numbered 1..MAX
    while (fscanf (fp, "%s", command)!=EOF)
    {
      if (strcmp (command, "NODE")==0)
      {
        fscanf (fp, "%d %s", &i, name);
        insert_graph_node (mygraph, i, name);
      }
      else
      {
        if (strcmp (command, "EDGE")==0)
        {
          fscanf (fp, "%d %d", &s, &t);
          insert_graph_link (mygraph, s, t);
        }
        else
        {
          return -1;
        }
      }
    }
  }
  return 0;
}
void print_graph (Graph *mygraph)
/*
 * Prints out Graph *mygraph to the stdout in .gx format - JLS
 */
{
  int i;
  List *current;
  printf ("MAX %d\n", mygraph->maxSize - 1);
  for (i=0; i<mygraph->maxSize; i++)
    if (mygraph->table[i].name!=NULL)
    {
      printf ("NODE %d %s\n", i, mygraph->table[i].name);
      current= mygraph->table[i].outlist;
      while (current!=NULL)
      {
        printf ("EDGE %d %d\n", i, current->index);
        current= current->next;
     }
  }
}
