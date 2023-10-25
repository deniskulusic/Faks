#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_NAME_SIZE (128)
#define MAX_LINE (128)
#define FILE_ERROR_OPEN (-1)
#define GET_INFO_SUCCESS (0)
#define MAX_NUM_POINTS (60)
#define SUCCESS (0)

struct _Student;
typedef struct _Student
{
    char name[MAX_NAME_SIZE];
    char surname[MAX_NAME_SIZE];
    int points;

}Student;

int readNoRowsInFile();
int getStudentInfo( int, Student*);
void printStudentInfo(int, Student*);


int main(void)
{
    Student* studenti = NULL;
    int show = -1;
    int numOfStudents = 0;

    //get no of students
    numOfStudents = readNoRowsInFile();

    //allocate memory for students
    if (numOfStudents > 0)
    {
        studenti = (Student*)malloc(numOfStudents * sizeof(Student));

    }

    //if we allocated memory run function
    if (studenti)
    {
        //function returns GET_INFO_SUCCESS (0) if it gets correct data from file
        show = getStudentInfo(numOfStudents, studenti);
    }

    //Printing student info if we didnt get an error from last funtion
    if (show == 0)
    {
        printStudentInfo(numOfStudents, studenti);
    }
    else
    {
        printf("Error when getting student info from the file!\n");
    }

    //free memory allocated
    free(studenti);

    return SUCCESS;
}


int getStudentInfo(int numOfStudents, Student* studenti)
{
    int i = 0;
    int count = 0;
    char buffer[MAX_LINE] = { 0 };

    FILE* fp = NULL;
    fp = fopen("students.txt", "r");

    //check if file has opened successfully 
    if (!fp)
    {
        printf("File is not open!\n");
        return FILE_ERROR_OPEN;
    }

    for (i = 0; i < numOfStudents; i++)
    {
        char nameInp[MAX_NAME_SIZE] = "";
        char surnameInp[MAX_NAME_SIZE] = "";
        int pointsInp = 0;

        //skipping blank rows
        while (1)
        {
            fgets(buffer, MAX_LINE, fp);

            if (strcmp("\n", buffer) != 0)
            {
                break;
            }
        }

        //copying data from the buffer to the variables 
        sscanf(buffer, "%s %s %d", nameInp, surnameInp, &pointsInp);


        //copying data from variables to the structure via pointer
        strcpy((studenti + i)->name, nameInp);
        strcpy((studenti + i)->surname, surnameInp);
        (studenti + i)->points = pointsInp;

    }
    fclose(fp);

    return GET_INFO_SUCCESS;
}



void printStudentInfo(int numOfStudents, Student* studenti)
{
    int i = 0;
    float rel_points = 0.0;
    printf("\nPrinting student info:\n");

    //looping through the known number of students and printing their info
    for (i = 0; i < numOfStudents; i++)
    {
        Student stud = *(studenti + i);
        //calculating their relative score
        rel_points = (((float)stud.points / MAX_NUM_POINTS) * 100);

        //printing everything on the screen
        printf("Student %s %s ima %d apsolutnih odnosno %.2f%% bodova!\n", stud.name, stud.surname, stud.points, rel_points);
    }

}


int readNoRowsInFile() {
    int counter = 0;
    FILE* filePointer = NULL;
    char buffer[MAX_LINE] = { 0 };

    filePointer = fopen("students.txt", "r");

    //check if file has opened successfully 
    if (!filePointer) {
        printf("File is not open!\n");
        return FILE_ERROR_OPEN;
    }

    while (!feof(filePointer)) {
        fgets(buffer, MAX_LINE, filePointer);
        counter++;
    }

    fclose(filePointer);

    return counter;
}