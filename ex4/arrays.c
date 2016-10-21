#include <stdio.h>
#include <stdlib.h>

#define HOW_MANY 7
char *names[HOW_MANY]= {"Simon", "Suzie", "Alfred", "Chip", "John", "Tim",
		      			"Harriet"};
int ages[HOW_MANY]= {22, 24, 106, 6, 18, 32, 24};

struct person {
	char *name;
	int age;
};

static void insert(struct person **people, char *name, int age) {
  static int nextfreeplace = 0;

  people[nextfreeplace] = (struct person *)malloc(sizeof(struct person));

  people[nextfreeplace]->name = name;
  people[nextfreeplace++]->age = age;
}

int main(int argc, char **argv) {

  struct person *people[HOW_MANY];
  int i;

  for (i = 0; i < HOW_MANY; i++)   {
    insert (people, names[i], ages[i]);
  }

  for (i = 0; i < HOW_MANY; i++)   {
  	printf("%-7s : %d\n", people[i]->name, people[i]->age);
  }

  return 0;
}
