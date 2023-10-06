#include <iostream>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
using namespace std;

FILE *fb, *ft, *fa;
char choice, another;
int eid;

class employee_opps
{
public:
    int empid, age, salary, year;
    char name[10], post[10];

    int getdata();
    int display();
    int update();
    int del();
};

employee_opps e;

int employee_opps::getdata()
{
    cout << "\nenter the id of emp : ";
    cin >> empid;

    cout << "enter the name of emp :";
    cin >> name;

    cout << "enter the age of emp :";
    cin >> age;

    cout << "enter the post of emp :";
    cin >> post;

    cout << "enter the salary of emp :";
    cin >> salary;

    cout << "enter the years of joining of emp :";
    cin >> year;
}

int employee_opps::display()
{
    cout << "\nid\tname\t\tage\tpost\tsalary\tyear\n"<< endl;
    rewind(fb);
    while (fread(&e, sizeof(e), 1, fb) == 1)
    {
        cout << empid << "\t" << name << "\t\t" << age << "\t" << post << "\t" << salary << "\t" << year << endl;
    }
    getch();
}

int employee_opps::update()
{
    another = 'y';
    while (another == 'y')
    {

        cout << "\nEnter the employee id to modify: ";
        cin >> eid;
        rewind(fb);
        while (fread(&e, sizeof(e), 1, fb) == 1)
        {
            if (e.empid == eid)
            {
                e.getdata();
                fseek(fb, -sizeof(e), SEEK_CUR);
                fwrite(&e, sizeof(e), 1, fb);
                break;
            }
        }
        cout << ("\nModify another record(y/n)");
        fflush(stdin);
        another = getche();
    }
}

int employee_opps::del()
{
    another = 'y';
    while (another == 'y')
    {
        printf("\nEnter name of id to delete: ");
        cin >> eid;
        ft = fopen("Temp.dat", "wb");
        rewind(fb);
        while (fread(&e, sizeof(e), 1, fb) == 1)
        {
            if (e.empid != eid)
            {
                fwrite(&e, sizeof(e), 1, ft);
            }
        }
        fclose(ft);
        fclose(fb);
        remove("EMP.DAT");             // remove the orginal file
        rename("Temp.dat", "EMP.DAT"); // rename the temp file to original file name
        fb = fopen("EMP.DAT", "rb+");
        printf("Delete another record(y/n)");
        fflush(stdin);
        another = getche();
    }
}

int main()
{

    fb = fopen("EMP.DAT", "rb+");
    if (fb == NULL)
    {
        fb = fopen("EMP.DAT", "wb+");
        if (fb == NULL)
        {
            cout << "Connot open file";
        }
    }

    while (1)
    {
        cout << "\n1. Add Record\n";
        cout << "2. List Records\n";
        cout << "3. Modify Records\n";
        cout << "4. Delete Records\n";
        cout << "5. Exit\n";
        cout << "Your Choice: ";
        fflush(stdin);
        choice = getche();

        switch (choice)
        {
        case '1':
            another = 'y';
            while (another == 'y')
            {
                e.getdata();
                fwrite(&e, sizeof(e), 1, fb);
                cout << "\nAdd another record(y/n) ";
                fflush(stdin);
                another = getche();
            }
            break;
        case '2':
            e.display();
            break;

        case '3':
            e.update();
            break;

        case '4':
            e.del();
            break;

        case '5':
            fclose(fb);
            exit(0);
        }
    }
}
