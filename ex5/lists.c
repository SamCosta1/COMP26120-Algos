#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HOW_MANY 7
char *names[HOW_MANY]= {"Simon", "Suzie", "Alfred", "Chip", "John", "Tim",
		      			"Harriet"};
int ages[HOW_MANY]= {22, 24, 106, 6, 18, 32, 24};

struct person {
	char *name;
	int age;
	struct person *next;
};

struct person * insert_start(struct person *people, char *name, int age) {
	struct person *current = (struct person *)malloc(sizeof(struct person));
	
	if (current == NULL) {
		printf("Something went wrong with memory");
		exit(-1);
	}
	current->name = name;
  current->age = age;
	current->next = people;
	return current;
}

int compare_people_by_name(struct person *person1, struct person *person2) {
	return strcmp(person1->name, person2->name);
}

int compare_people_by_age(struct person *person1, struct person *person2) {
	return person1->age - person2->age;
}

struct person * insert_sorted(struct person *people, char *name, int age,
                              int (*compare_people)(struct person *,
                                                    struct person *)) {
	struct person *current = (struct person *)malloc(sizeof(struct person));

	if (current == NULL) {
		printf("Something went wrong with memory");
		exit(-1);
	}

	current->name = name;
  current->age = age;

	if (people == NULL || (*compare_people)(people, current) > 0) {
		current->next = people;
		return current;
	} else {
	  
		struct person *nextPerson = people;
		while (nextPerson->next != NULL
		       && (*compare_people)(nextPerson->next,current) < 0) {
		  nextPerson = nextPerson->next;
		}
		
		if (nextPerson->next == NULL) {
		  nextPerson->next = current;
		} else {
		  // The current list is,  nextPerson ---> nextPerson.next
		  // we need               nextPerson ---> current ---> nxtPerson.next
		  // ie current needs to be insterted in the middle
		  struct person *tempPerson = nextPerson->next;
		  nextPerson->next = current;
		  current->next = tempPerson;		
		}
		
		return people;
	}
}

struct person * insert_end(struct person *people, char *name, int age) {
	struct person *current = (struct person *)malloc(sizeof(struct person));

	if (current == NULL) {
		printf("Something went wrong with memory");
		exit(-1);
	}
	
	current->name = name;
    current->age = age;

	if (people == NULL) {
		current->next = people;
		return current;
	} else {
		struct person *nextPerson = people;
		while (nextPerson->next != NULL) {
	        nextPerson = nextPerson->next;
		}

		nextPerson->next = current;
		return people;
	}
}

int main(int argc, char **argv) {
  struct person *people = NULL;
  struct person *nextPerson;
  int i;

  for (i = 0; i < HOW_MANY; i++)  {
    people = insert_sorted(people, names[i], ages[i], &compare_people_by_age);
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
