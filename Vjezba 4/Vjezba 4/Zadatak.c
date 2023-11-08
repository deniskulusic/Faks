/*4. Napisati program za zbrajanje i množenje polinoma. Koeficijenti i eksponenti se
èitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nužno sortirani.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FILE_DIDNT_OPEN_ERROR (-1)
#define MAX_LINE (1024)
#define MAX_FILE_NAME (256)
#define MEMORY_NOT_ALLOCATED_CORRECT (-1)



struct _polinom;
typedef struct _polinom* position;

typedef struct _polinom {
    int koef;
    int eksp;
    position next;
}polinom;


int readFromFile(position p, char* fileName);
position createNewPoli(int koef, int eksp);
int insertSort(position p, int koef, int eksp);
int insertAfter(position p, position q);
int printPoliList(position p);
int deleteAfter(position p);
int Delete(position p);

int main(void) {

    polinom Poly = { .koef = 0, .eksp = {0}, .next = NULL };
    char fileName[MAX_FILE_NAME] = { 0 };

    printf("Type in file name: ");
    scanf(" %s", fileName);
    readFromFile(&Poly, fileName);
    printf("Polinom 1: ");
    printPoliList(Poly.next);
    printf("==================================\n");
    if (Delete(Poly.next) == 0) {
        printf("Successful memory cleaning p1!");
        printf("\n");
    }



    return EXIT_SUCCESS;
}



int readFromFile(position p, char* fileName) {

    FILE* fp = NULL;
    fp = fopen(fileName, "r");

    if (fp == NULL) {
        printf("Dear customer, the file %s didn't open! \r\n", fileName);
        return FILE_DIDNT_OPEN_ERROR;
    }


    char buffer[MAX_LINE] = { 0 };
    char* ptr = buffer;
    int koef = 0;
    int eksp = 0;
    int n = 0;

    while (!feof(fp)) {

        fgets(ptr, MAX_LINE, fp);

        while (strlen(ptr) > 0)
        {
            sscanf(ptr, "%d %d %n", &koef, &eksp, &n);

            if (koef != 0)
                insertSort(p, koef, eksp);

            ptr += n;

        }
    }
    fclose(fp);

    return EXIT_SUCCESS;
}

position createNewPoli(int koef, int eksp)
{
    position new = NULL;
    new = (position)malloc(sizeof(polinom));

    if (new == NULL) {
        printf("Memory not allocated correctly!");
        return MEMORY_NOT_ALLOCATED_CORRECT;
    }

    new->koef = koef;
    new->eksp = eksp;
    new->next = NULL;

    return new;
}


int insertSort(position p, int koef, int eksp) {

    position new = NULL;
    new = createNewPoli(koef, eksp);

    if (new == NULL) {
        printf("Memory not allocated correctly!");
        return MEMORY_NOT_ALLOCATED_CORRECT;
    }

    //Add if its the first element being added or if its exponent is the smallest
    if (p == NULL || eksp < p->eksp) {
        new->next = p;
        p = new;
    }
    //else go until you find the right spot for it
    else {

        position temp = p;
        //loop until we get to the last element of an element 
        while (temp->next != NULL && temp->next->eksp < eksp) {
            if (temp->next->koef == 0) {
                deleteAfter(temp);
            }
            temp = temp->next;
        }
        if (temp->next != NULL && temp->next->eksp == eksp) {
            if (temp->next->koef == -koef)
                deleteAfter(temp);
            else
                temp->next->koef += koef;
        }

        else {
            insertAfter(temp, new);
        }

    }

    return EXIT_SUCCESS;
}

int insertAfter(position p, position q)
{
    q->next = p->next;
    p->next = q;

    return EXIT_SUCCESS;
}

int printPoliList(position p) {

    if (p == NULL) {
        printf("No polynomials!");
        return FILE_DIDNT_OPEN_ERROR;
    }

    while (p != NULL) {

        printf(" %dx^%d ", p->koef, p->eksp);
        if (p->next != NULL) {
            if (p->next->koef >= 0)
                printf("+");
            else
                printf("");
        }

        p = p->next;
    }
    printf("\n");


    return EXIT_SUCCESS;
}

int deleteAfter(position p) {
    position toDel = NULL;

    toDel = p->next;
    p->next = p->next->next;
    free(toDel);

    return EXIT_SUCCESS;
}


int Delete(position p) {
    position head = p;
    position temp;

    while (head != NULL) {
        temp = head->next;
        free(head);
        head = temp;
    }

    return EXIT_SUCCESS;
}