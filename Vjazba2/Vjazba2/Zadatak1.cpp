/*2. Definirati strukturu osoba (ime, prezime, godina roðenja) i napisati program koji:
A. dinamièki dodaje novi element na poèetak liste,
B. ispisuje listu,
C. dinamièki dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. briše odreðeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LINE (128)
#define MEMORY_NOT_ALLOCATED_CORRECT (-1)
#define ERROR (-1)
struct _person;
typedef struct _person* position;

typedef struct _person {
	char name[MAX_LINE];
	char lastName[MAX_LINE];
	int birthYear;

	position next;
}person;


int AddFrist(position p, char* name, char* lastName, int birthYear);
int AddLast(position p, char* name, char* lastName, int birthYear);
int PrintList(position p);

int main(void) {

	char name[MAX_LINE] = { 0 };
	char lastName[MAX_LINE] = { 0 };
	int birthYear = 0;
	int choice;

	//allocating head element which is always first in the list
	position head = NULL;
	head = (position)malloc(sizeof(person));

	if (head == NULL) {
		printf("Memory not allocated correctly!");
		return MEMORY_NOT_ALLOCATED_CORRECT;
	}

	//asigning head with values of null
	strcpy(head->name, "");
	strcpy(head->lastName, "");
	head->birthYear = 0;
	head->next = NULL;

	//user decides what he wants and enters values if needed
	while (1) {

		printf("\nChoose what you want to do:\n");
		printf("1 - Insert a person at the beginning of the list\n");
		printf("2 - Insert a person at the end of the list\n");
		printf("3 - Print list\n");
		printf("4 - Exit\n");
		printf("Your choice: ");
		scanf(" %d", &choice);

		switch (choice)
		{
		case 1:
			printf("Type in name of the person you want to insert: ");
			scanf(" %s", name);
			printf("Type in last name of the person you want to insert: ");
			scanf(" %s", lastName);
			printf("Type in birth year of the person you want to insert: ");
			scanf("%d", &birthYear);
			AddFrist(head, name, lastName, birthYear);
			break;

		case 2:
			printf("Type in name of the person you want to insert: ");
			scanf(" %s", name);
			printf("Type in last name of the person you want to insert: ");
			scanf(" %s", lastName);
			printf("Type in birth year of the person you want to insert: ");
			scanf("%d", &birthYear);
			AddLast(head, name, lastName, birthYear);
			break;

		case 3:
			PrintList(head->next);
			break;

		case 4:
			return EXIT_SUCCESS;
			break;
		default:
			
			break;
		}
		
	}


	return EXIT_SUCCESS;
}






int AddFrist(position p, char* name, char* lastName, int birthYear) {
	//set velues to new position q
	position q = (position)malloc(sizeof(person));
	strcpy(q->name, name);
	strcpy(q->lastName, lastName);
	q->birthYear = birthYear;
	q->next = NULL;


	//get new element Next value of the last element 
	q->next = p->next;
	//set last element Next to new element adress
	p->next = q;

	return EXIT_SUCCESS;
}




int AddLast(position p, char* name, char* lastName, int birthYear) {
	//set velues to new position q
	position q = (position)malloc(sizeof(person));
	strcpy(q->name, name);
	strcpy(q->lastName, lastName);
	q->birthYear = birthYear;
	q->next = NULL;

	//go to last current eleemnt of list
	while (p->next != NULL) {
		p = p->next;
	}
	//get new element Next value of the last element 
	q->next = p->next;
	//set last element Next to new element adress
	p->next = q;

	return EXIT_SUCCESS;
}


int PrintList(position p) {
	//if there is no positition head->Next element return error
	if (p == NULL) {
		printf("Nema elemenata, lista je prazna!");
		return ERROR;
	}
	//print values
	else {
		while (p != NULL) {
			printf("%s ", p->name);
			printf("%s ", p->lastName);
			printf("%d\n", p->birthYear);

			p = p->next;
		}
		return EXIT_SUCCESS;
	}
}