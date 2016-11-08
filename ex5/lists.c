#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HOW_MANY 7

typedef enum staff_or_student {
	staff,
	student,
	neither
} PersonType;


char *names[HOW_MANY]= {"Simon", "Suzie", "Alfred", "Chip", "John", "Tim",
		      			"Harriet"};
int ages[HOW_MANY]= {22, 24, 106, 6, 18, 32, 24};
PersonType types[HOW_MANY]= {student, staff, student, student, staff, staff,
							 neither};
char *info[HOW_MANY]= {"History", "Kilburn 1.1", "Maths", "Physics",
 					   "Kilburn2.4", "Turning2.12", "N/A"};

typedef struct person {
	char *name;
	int age;
	PersonType personType;

	union {
		char * courseTitle;
		char * roomNumber;
	} info;

	struct person *next;
} Person;

void makeStaffOrStudent(Person *thisPerson, PersonType type, char * info) {
	switch (type) {
		case student:
			thisPerson->info.courseTitle = info;
			break;
		case staff:
			thisPerson->info.roomNumber = info;
			break;
		case neither:
			thisPerson->info.roomNumber = NULL;
			thisPerson->info.courseTitle = NULL;
			break;
	}
	thisPerson->personType = type;
}

void printPerson(Person *p2person) {
	Person thisPerson = *p2person;
	switch (thisPerson.personType) {
		case student:
			printf("Student name: %-7s | Age: %3d | Course: %s\n",
	               thisPerson.name, thisPerson.age,
				   thisPerson.info.courseTitle);
			break;
		case staff:
			printf("Staff name:   %-7s | Age: %3d | Room: %s\n",
	               thisPerson.name, thisPerson.age,
				   thisPerson.info.roomNumber);
			break;
		case neither:
			printf("Person name:  %-7s | Age: %3d |\n",
	               thisPerson.name, thisPerson.age);
			break;
	}
}

Person * insert_start(Person *people, char *name, int age, PersonType type,
													       char * info) {
	Person *current = (Person *)malloc(sizeof(Person));

	if (current == NULL) {
		printf("Something went wrong with memory");
		exit(-1);
	}
	current->name = name;
  	current->age = age;
	current->next = people;

	makeStaffOrStudent(current, type, info);

	return current;
}



int compare_people_by_name(Person *person1, Person *person2) {
	return strcmp(person1->name, person2->name);
}

int compare_people_by_age(Person *person1, Person *person2) {
	return person1->age - person2->age;
}

Person * insert_sorted(Person *people, char *name, int age, PersonType type,
			           char * info, int (*compare_people)(Person *,
                                                          Person *)) {
	Person *current = (Person *)malloc(sizeof(Person));

	if (current == NULL) {
		printf("Something went wrong with memory");
		exit(-1);
	}

	current->name = name;
  	current->age = age;
	current->next = NULL;

	makeStaffOrStudent(current, type, info);

	if (people == NULL || (*compare_people)(people, current) > 0) {
		current->next = people;
		return current;
	} else {

		Person *nextPerson = people;
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
		  Person *tempPerson = nextPerson->next;
		  nextPerson->next = current;
		  current->next = tempPerson;
		}

		return people;
	}
}

Person * insert_end(Person *people, char *name, int age, PersonType type,
													     char * info) {
	Person *current = (Person *)malloc(sizeof(Person));

	if (current == NULL) {
		printf("Something went wrong with memory");
		exit(-1);
	}

	current->name = name;
    current->age = age;

	makeStaffOrStudent(current, type, info);

	if (people == NULL) {
		current->next = people;
		return current;
	} else {
		Person *nextPerson = people;
		while (nextPerson->next != NULL) {
	        nextPerson = nextPerson->next;
		}

		nextPerson->next = current;
		return people;
	}
}

int main(int argc, char **argv) {
  Person *people = NULL;
  Person *nextPerson;
  int i;

  for (i = 0; i < HOW_MANY; i++)  {
    people = insert_sorted(people, names[i], ages[i], types[i], info[i],
		 				   &compare_people_by_age);
  }

  nextPerson = people;
  for (i = 0; i < HOW_MANY; i++)  {
      printPerson(nextPerson);
	  // Temporarily store next person to be able to free it
	  Person *tempNextPerson = nextPerson->next;
	  free(nextPerson);
	  nextPerson = tempNextPerson;
  }

  return 0;
}
