
// Dynamic programming for 0/1 knapsack
// (C) Joshua Knowles
// The variable names here follow standard usage in formulating
// dynamic programming via recursive definitions

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

FILE *fp;  // file pointer for reading the input files
int Capacity;     // capacity of the knapsack (total weight that can be stored)
int Nitems;    // number of items available
int *item_weights;  // vector of item weights
int *item_values;  // vector of item profits or values
int *temp_indexes;  // list of temporary item indexes for sorting items by value/weight
int QUIET=0; // this can be set to 1 to suppress output


// function prototypes
extern void read_knapsack_instance(char *filename);
int DP(int *v,int *wv, int n, int W, int *solution);
extern int check_evaluate_and_print_sol(int *sol,  int *total_value, int *total_weight);
void memoryCheck(void *ptr);
int** get2DIntArray(int size1, int size2);
int max(int a, int b);

int main(int argc, char *argv[1])
{
  int *solution;    // binary vector indicating items to pack
  int total_value, total_weight;  // total value and total weight of items packed

  read_knapsack_instance(argv[1]);

  if((solution = (int *)malloc((Nitems+1)*sizeof(int)))==NULL)
    {
      fprintf(stderr,"Problem allocating table for DP\n");
      exit(1);
    }

  DP(item_values,item_weights,Nitems,Capacity,solution);
  check_evaluate_and_print_sol(solution,&total_weight,&total_value);
  return(0);
}



int DP(int *v,int *wv, int n, int W, int *solution) {
   // the dynamic programming function for the knapsack problem
   // the code was adapted from p17 of http://www.es.ele.tue.nl/education/5MC10/solutions/knapsack.pdf

   // v array holds the values / profits / benefits of the items
   // wv array holds the sizes / weights of the items
   // n is the total number of items
   // W is the constraint (the weight capacity of the knapsack)
   // solution: a 1 in position n means pack item number n+1. A zero means do not pack it.

   // 2d arrays for use in the dynamic programming solution
   // keep[][] and V[][] are both of size (n+1)*(W+1)
   int **V = get2DIntArray(n + 1, W + 1);
   int **keep = get2DIntArray(n + 1, W + 1);

   int i, w, K;



   //  set the values of the zeroth row of the partial solutions table to zero
   for (w = 0; w <= W; w++) V[0][w] = 0;


   // main dynamic programming loops , adding one item at a time and looping through weights from 0 to W
   for (i = 1; i <= n; i++)
      for(w = 0; w <= W; w++) {

         int withThisVal = v[i] + V[i - 1][  w > wv[i] ? 0 : w - wv[i]  ];

         if (wv[i] <= w && withThisVal > V [i-1][w]) {
            V[i][w] = withThisVal;
            keep[i][w] = 1;
         } else {
            V[i][w] = V[i-1][ w];
            keep[i][w] = 0;
         }
      }

   // now discover which items were in the optimal solution
   K = W;
   for (i = n; i >=1; i--) {
      solution[i] = keep[i][K];
      if (keep[i][K] == 1)
         K -= wv[i];
   }

   return V[n][W];

}

void memoryCheck(void *ptr) {
    if (ptr == NULL) {
        printf("Memory issue");
        exit(0);
    }
}

int** get2DIntArray(int size1, int size2) {
   int i;
   int **arr = (int**)malloc(size1 * sizeof(int*));
   memoryCheck(arr);

   for (i = 0; i < size1; i++) {
      arr[i] = (int*)malloc(size2 * sizeof(int));
      memoryCheck(arr[i]);
   }

   return arr;
}

int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}
