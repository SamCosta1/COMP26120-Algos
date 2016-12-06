
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

void merge(Book *list1, Book *list2, int(*compar)(const void *, const void *));
void print_results(Book*L, int N);

void mergeSort(Book * L, int listLength,
                         int(*compar)(const void *, const void *)) {
    if (listLength < 1)

    print_results(L, listLength);
    printf("------\n");
    int halfFloored = listLength / 2;
    merge(mergeSort(L, halfFloored, compar),
                 mergeSort(L+halfFloored, listLength - halfFloored, compar), compar);
}


void merge(Book *list1, Book *list2, int(*compar)(const void *, const void *)) {
   if (list1 == NULL || list2 == NULL)
      return;

   if (compar(&(list1[0]), &(list2[0])) <= 0) {
      merge(++list1, list2, compar);

   } else {
      merge(++list1, list2+1, compar);

   }
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
int comp_on_rating(const void *a, const void *b)
{
  if ((*(Book *)a).rating < (*(Book *)b).rating)
  {
     return -1;
  }
    else
  {
    if ((*(Book *)a).rating > (*(Book *)b).rating)
    {
      return 1;
    }
      else
    {
      return 0;
    }
  }
}
int comp_on_relev(const void *a, const void *b)
{

  if ((*(Book *)a).relevance < (*(Book *)b).relevance)
  {
     return -1;
  }
     else
  {
     if ((*(Book *)a).relevance > (*(Book *)b).relevance)
     {
       return 1;
     }
       else
     {
       return 0;
     }
  }
}
int comp_on_price(const void *a, const void *b)
{

  if ((*(Book *)a).price < (*(Book *)b).price)
  {
     return 1;
  }
     else
  {
     if ((*(Book *)a).price > (*(Book *)b).price)
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
  mergeSort(list, N, comp_on_price);


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
	  printf("%g %g %g %d\n", L[i].rating, L[i].price, L[i].relevance, L[i].ID);
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

  print_results(list, N);

  return(0);
}
