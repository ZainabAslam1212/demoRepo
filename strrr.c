//phonebook
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

struct student
{
    char name[35];
    float cgpa;
    char father_name[35];
    long int roll_number;
    char mail[100];
};

void menu();
void got(char *name);
void start();
void back();
void addrecord();
void listrecord();
void modifyrecord();
void deleterecord();
void searchrecord();

int main()
{
    system("color 1f");
    start();
    return 0;
}

void back()
{
    start();
}

void start()
{
    menu();
}

void menu()
{
    system("cls");
    printf("\t\t********WELCOME TO STUDENT RECORD SYSTEM***********");
    printf("\n\n\t\t\t  MENU\t\t\n\n");
    printf("\t1.Add New   \t2.List   \t3.Exit  \n\t4.Modify \t5.Search\t6.Delete");

    switch (getch())
    {
    case '1':
        addrecord();
        break;
    case '2':
        listrecord();
        break;
    case '3':
        exit(0);
        break;
    case '4':
        modifyrecord();
        break;
    case '5':
        searchrecord();
        break;
    case '6':
        deleterecord();
        break;
    default:
        system("cls");
        printf("\nEnter 1 to 6 only");
        printf("\n Enter any key");
        getch();

        menu();
    }
}

void addrecord()
{
    system("cls");
    FILE *f;
    struct student s;
    f = fopen("student_records", "ab+");
    printf("\n Enter name: ");
    got(s.name);
    printf("\nEnter the CGPA: ");
    scanf("%f", &s.cgpa);
    printf("\nEnter father name: ");
    got(s.father_name);
    printf("\nEnter roll number:");
    scanf("%ld", &s.roll_number);
    printf("\nEnter e-mail:");
    got(s.mail);
    fwrite(&s, sizeof(s), 1, f);

    fflush(stdin);
    printf("\nrecord saved");

    fclose(f);

    printf("\n\nEnter any key");
    getch();
    system("cls");
    menu();
}

void listrecord()
{
    struct student s;
    FILE *f;
    f = fopen("student_records", "r+");
    if (f == NULL)
    {
        printf("\nfile opening error in listing :");
        exit(1);
    }
    while (fread(&s, sizeof(s), 1, f) == 1)
    {
        printf("\n\n\n YOUR RECORD IS\n\n ");
        printf("\nName=%s\nCGPA=%.2f\nFather name=%s\nRoll number=%ld\nE-mail=%s", s.name, s.cgpa, s.father_name, s.roll_number, s.mail);

        getch();
        system("cls");
    }
    fclose(f);
    printf("\n Enter any key");
    getch();
    system("cls");
    menu();
}

void searchrecord()
{
    struct student s;
    FILE *f;
    char name[100];

    f = fopen("student_records", "r+");
    if (f == NULL)
    {
        printf("\n error in opening\a\a\a\a");
        exit(1);
    }
    printf("\nEnter name of student to search\n");
    got(name);
    while (fread(&s, sizeof(s), 1, f) == 1)
    {
        if (strcmp(s.name, name) == 0)
        {
            printf("\n\tDetail Information About %s", name);
            printf("\nName:%s\nCGPA=%.2f\nFather name:%s\nRoll number:%ld\nE-mail:%s", s.name, s.cgpa, s.father_name, s.roll_number, s.mail);
        }
        else
            printf("file not found");
    }
    fclose(f);
    printf("\n Enter any key");

    getch();
    system("cls");
    menu();
}

void deleterecord()
{
    struct student s;
    FILE *f, *ft;
    int flag;
    char name[100];
    f = fopen("student_records", "r+");
    if (f == NULL)
    {

        printf("\nSTUDENT'S DATA NOT ADDED YET.");
    }
    else
    {
        ft = fopen("temp", "wb+");
        if (ft == NULL)
            printf("\nfile opening error");
        else
        {
            printf("\nEnter STUDENT'S NAME:");
            got(name);
            fflush(stdin);
            while (fread(&s, sizeof(s), 1, f) == 1)
            {
                if (strcmp(s.name, name) != 0)
                    fwrite(&s, sizeof(s), 1, ft);
                if (strcmp(s.name, name) == 0)
                    flag = 1;
            }
            fclose(f);
            fclose(ft);
            if (flag != 1)
            {
                printf("\nNO STUDENT'S RECORD TO DELETE.");
                remove("temp.txt");
            }
            else
            {
                remove("student_records");
                rename("temp.txt", "student_records");
                printf("\nRECORD DELETED SUCCESSFULLY.");
            }
        }
    }
    printf("\n Enter any key");

    getch();
    system("cls");
    menu();
}

void modifyrecord()
{
    int c;
    FILE *f;
    int flag = 0;
    struct student s, t;
    char name[50];
    f = fopen("student_records", "r++");
    if (f == NULL)
    {

        printf("STUDENT'S DATA NOT ADDED YET.");
        exit(1);
    }
    else
    {
        system("cls");
        printf("\nEnter STUDENT'S NAME TO MODIFY:\n");
        got(name);
        while (fread(&s, sizeof(s), 1, f) == 1)
        {
            if (strcmp(name, s.name) == 0)
            {
                printf("\n Enter name:");
                got(t.name);
                printf("\nEnter the CGPA:");
                scanf("%f", &t.cgpa);
                printf("\nEnter father name:");
                got(t.father_name);
                printf("\nEnter roll number:");
                scanf("%ld", &t.roll_number);
                printf("\nEnter e-mail:");
                got(t.mail);
                fseek(f, -sizeof(s), SEEK_CUR);
                fwrite(&t, sizeof(s), 1, f);
                flag = 1;
                break;
            }
            fflush(stdin);
        }
        if (flag == 1)
        {
            printf("\n your data is modified");
        }
        else
        {
            printf(" \n data is not found");
        }
        fclose(f);
    }
    printf("\n Enter any key");
    getch();
    system("cls");
    menu();
}

void got(char *name)
{
    int i = 0, j;
    char c, ch;
    do
    {
        c = getch();
        if (c != 8 && c != 13)
        {
            *(name + i) = c;
            putch(c);
            i++;
        }
        if (c == 8)
        {
            if (i > 0)
            {
                i--;
            }

            system("cls");
            for (j = 0; j < i; j++)
            {
                ch = *(name + j);
                putch(ch);
            }
        }
    } while (c != 13);
    *(name + i) = '\0';
}
