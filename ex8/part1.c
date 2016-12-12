
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

FILE *fp;

typedef struct book
{
  double rating;
  double price;
  double relevance;
  int ID;
} Book;

Book * merge(Book *list, int start, int length1, int length2, int(*compar)(const void *, const void *));
void print_results(Book*L, int N);



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
Book * merge(Book *L, int low, int mid, int high, int(*compar)(const void *, const void *)) {
   int l1, l2, i;

   for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
      if (compar(&L[l1],&L[l2]) <= 0)
         newArray[i] = L[l1++];
      else
         newArray[i] = L[l2++];
   }
   while(l1 <= mid)
      newArray[i++] = L[l1++];

   while(l2 <= high)
      newArray[i++] = L[l2++];

   for(i = low; i <= high; i++)
      L[i] = newArray[i];

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
int comp_on_rating(const void *list, const void *newArray)
{
  if ((*(Book *)list).rating < (*(Book *)newArray).rating)
  {
     return -1;
  }
    else
  {
    if ((*(Book *)list).rating > (*(Book *)newArray).rating)
    {
      return 1;
    }
      else
    {
      return 0;
    }
  }
}
int comp_on_relev(const void *list, const void *newArray)
{

  if ((*(Book *)list).relevance < (*(Book *)newArray).relevance)
  {
     return -1;
  }
     else
  {
     if ((*(Book *)list).relevance > (*(Book *)newArray).relevance)
     {
       return 1;
     }
       else
     {
       return 0;
     }
  }
}
int comp_on_price(const void *list, const void *newArray)
{

  if ((*(Book *)list).price < (*(Book *)newArray).price)
  {
     return 1;
  }
     else
  {
     if ((*(Book *)list).price > (*(Book *)newArray).price)
     {
       return -1;
     }
       else
     {
       return 0;
     }
  }
}

void user_interface(int N)
{

  // For Part 1 this function calls the sort function to sort on Price only
  newArray = malloc(N *sizeof(Book));
  newArray = mergeSort(list, 0, N, comp_on_price);
  print_results(newArray, N);

  // For Part 2 this function
  // (1) asks the user if they would like to sort their search results
  // (2) asks for the most important field (or key), the next most etc
  // (3) calls your sort function


}


void print_results(Book*L, int N)
{
    int i;
    if((fp=fopen("top20.txt","w")))
    {
      for(i=N-1;i>=N-20;i--)
      {
	  printf("%-3g %g %g %d\n", L[i].rating, L[i].price, L[i].relevance, L[i].ID);
	  fprintf(fp, "%-3g %g %g %d\n", L[i].rating, L[i].price, L[i].relevance, L[i].ID);

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
