#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

FILE *fp;

typedef enum key
{
   PRICE,
   RELEVANCE,
   RATING,
   NONE
} Key;

typedef struct book
{
  double rating;
  double price;
  double relevance;
  int ID;
} Book;

#define BUFFER_SIZE 100

Book * merge(Book *list, int start, int length1, int length2, int(*compar)(const void *, const void *));
void print_results(Book*L, int N);

void memoryCheck(void *ptr) {
    if (ptr == NULL) {
        printf("Memeory issue");
        exit(0);
    }
}


Book * mergeSort(Book * L, int start, int end,
                         int(*compar)(const void *, const void *)) {
   if (start >= end)
      return NULL;

   int middle = (start + end) / 2;
   mergeSort(L, start, middle, compar);
   mergeSort(L, middle+1, end, compar);
   return merge(L, start, middle, end, compar);
}

Book *newArray;
/*
   Adapted from code seen on tutorial point
   https://www.tutorialspoint.com/data_structures_algorithms/merge_sort_program_in_c.htm
*/
Book * merge(Book *L, int start1, int start2, int end2, int(*compar)(const void *, const void *)) {
   int startIndex = start1;
   int middleIndex = start2 + 1;
   int newArrayIndex = start1;

   while (startIndex <= start2 &&
          middleIndex <= end2) {
      if (compar(&L[startIndex], &L[middleIndex]) < 0)
         newArray[newArrayIndex] = L[startIndex++];
      else
         newArray[newArrayIndex] = L[middleIndex++];
      newArrayIndex++;
   }

   while (startIndex <= start2)
      newArray[newArrayIndex++] = L[startIndex++];
   while (middleIndex <= end2)
      newArray[newArrayIndex++] = L[middleIndex++];

   // Update the original array to use sorted values
   for (int i = start1; i <= end2; i++) {
      L[i] = newArray[i];
   }


   return newArray;
}

Book *list;
int read_file(char *infile, int N)
{
  int c;
  if((fp=fopen(infile, "rb")))
    {
      fscanf(fp, "%*s\t%*s\t%*s\t%*s\n");
      c=0;
      while((!feof(fp))&&(c<N))
	{
	  fscanf(fp, "%lf\t%lf\t%lf\t%d\n", &list[c].rating,  &list[c].price, &list[c].relevance, &list[c].ID);
	  c++;
	}
      fclose(fp);
    }
      else
    {
      fprintf(stderr,"%s did not open. Exiting.\n",infile);
      exit(-1);
    }
  return(c);
}
int comp_on_rating(const void *list, const void *list2)
{
  if ((*(Book *)list).rating < (*(Book *)list2).rating)
  {
     return -1;
  }
    else
  {
    if ((*(Book *)list).rating > (*(Book *)list2).rating)
    {
      return 1;
    }
      else
    {
      return 0;
    }
  }
}
int comp_on_relev(const void *list, const void *list2)
{

  if ((*(Book *)list).relevance < (*(Book *)list2).relevance)
  {
     return -1;
  }
     else
  {
     if ((*(Book *)list).relevance > (*(Book *)list2).relevance)
     {
       return 1;
     }
       else
     {
       return 0;
     }
  }
}
int comp_on_price(const void *list, const void *list2)
{

  if ((*(Book *)list).price < (*(Book *)list2).price)
  {
     return 1;
  }
     else
  {
     if ((*(Book *)list).price > (*(Book *)list2).price)
     {
       return -1;
     }
       else
     {
       return 0;
     }
  }
}

char *newInput;
char *getRawInput() {
    char *data = malloc(BUFFER_SIZE);
    memoryCheck(data);
    fgets(data, BUFFER_SIZE, stdin);

    newInput = malloc(strlen(data) + 1);
    memoryCheck(newInput);
    sscanf(data, "%[^\n]", newInput); // Extract text before newline character
    free(data);
    return newInput;
}


// Takes a list and an array of keys in increasing order of importance and number
// of elements
void sort(Book *L, Key *keys, int N) {
   for (int i = 0; i < 3; i++){
      switch (keys[i]) {

         case PRICE:
            qsort(L, N, sizeof(Book), comp_on_price);
         break;

         case RELEVANCE:
            qsort(L, N, sizeof(Book), comp_on_relev);
         break;

         case RATING:
            qsort(L, N, sizeof(Book), comp_on_rating);
         break;

         case NONE: break;
      }
   }

}

void toLowerCase ( char *p ) {
    for (int i = 0; i < strlen(p); i++) {
        p[i] = tolower(p[i]);
    }
}


Key getKeyFromInput(char * input) {
   toLowerCase(input);
   if (strcmp(input, "price") == 0)
      return PRICE;
   if (strcmp(input, "rating") == 0)
      return RATING;
   if (strcmp(input, "relevance") == 0)
      return RELEVANCE;
   return NONE;
}

void user_interface(int N)
{
  Key keys[3];
  printf("What is the most important field?\nPrice\nRelevance\nRating\n\n>");
  keys[2] = getKeyFromInput(getRawInput());

  // Must choose most important key
  if (keys[2] == NONE) user_interface(N);

  printf("What's the second most important? (Leave blank if no preference)\n>");
  keys[1] = getKeyFromInput(getRawInput());
  printf("And the third? (Leave blank if no preference)\n>");
  keys[0] = getKeyFromInput(getRawInput());
  sort(list, keys, N);
  print_results(list, N);

}


void print_results(Book*L, int N)
{
    int i;
    if((fp=fopen("top20.txt","w")))
    {
      printf("Stars	Price	Relv  ID\n");
       for(i=N-1;i>=N-20;i--)
      {
	  printf("%-7g %-7g %-5g %d\n", L[i].rating, L[i].price, L[i].relevance, L[i].ID);
	  fprintf(fp, "%g %g %g %d\n", L[i].rating, L[i].price, L[i].relevance, L[i].ID);

      }
      fclose(fp);
    }
      else
    {
      fprintf(stderr,"Trouble opening output file top20.txt\n");
      exit(-1);
   }

}

int main(int argc, char *argv[])
{
  int N;

  if(argc!=3)
    {
      fprintf(stderr, "./exec <input_size> <filename>\n");
      exit(-1);
    }

  N=atoi(argv[1]);

  list = (Book *)malloc(N*sizeof(Book));

  N=read_file(argv[2], N);

  user_interface(N);


  return(0);
}
