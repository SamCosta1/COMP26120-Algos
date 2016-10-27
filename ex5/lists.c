#include <stdio.h>
#include <stdlib.h>

#define HOW_MANY 7
char *names[HOW_MANY]= {"Simon", "Suzie", "Alfred", "Chip", "John", "Tim",
		      			"Harriet"};
int ages[HOW_MANY]= {22, 24, 106, 6, 18, 32, 24};

struct person {
	char *name;
	int age;
	struct person *next;
};

struct person * insert(struct person *people, char *name, int age) {
	struct person *current = (struct person *)malloc(sizeof(struct person));
	current->name = name;
    current->age = age;
	current->next = people;
	return current;
}

int main(int argc, char **argv) {

  struct person *people = NULL;
  struct person *nextPerson;
  int i;

  for (i = 0; i < HOW_MANY; i++)  {
    people = insert (people, names[i], ages[i]);
  }

  nextPerson = people;
  for (i = 0; i < HOW_MANY; i++)  {
  	printf("%-7s : %d\n", nextPerson->name, nextPerson->age);
	struct person *tempNextPerson = nextPerson->next;
	free(nextPerson);
	nextPerson = tempNextPerson;
  }

  return 0;
}
