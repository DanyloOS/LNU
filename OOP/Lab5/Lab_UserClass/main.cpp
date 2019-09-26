#include <iostream>
#include <vector>
#include "student.h"

unsigned int Student::amountOfStudents = 0;

using namespace std;

int main()
{
    vector<Student> students;
    int choice = 0;
    unsigned i = 0;
    while(true){
        cout << "1)Add new student\n2)Find student by ID\n3)Show all students\n4)Exit\n\n";
        cin >> choice;
        switch (choice) {
        case 1: {
            students.push_back(Student());
            i++;

            string tempStudName;
            cout << "\nName: ";
            cin >> tempStudName;//cin >> tempStudName;
            students[i-1].setStudentName(tempStudName);

            int tempStudGroup;
            cout << "Group: ";
            cin >> tempStudGroup;
            students[i-1].setStudentGroup(static_cast<Group>(tempStudGroup));

            int tempStudYear;
            cout << "Year: ";
            cin >> tempStudYear;
            students[i-1].setCourseYear(static_cast<Year>(tempStudYear));

            system("cls");
            break;
        }
        case 2: {
            system("cls");
            cout << "ID: ";
            unsigned int tempID;
            cin >> tempID;

            system("cls");
            if (tempID > 0 && tempID <= students.size()){
                students[tempID-1].displayStatistics();
                cout << endl;
            } else {
                cout << "No user with that ID!" << endl;
            }
            break;
        }
        case 3: {
            system("cls");
            for (unsigned int i = 0; i < students.size(); i++) {
                students[i].displayStatistics();
                cout << "\n";
            }
            break;
        }
        case 4:  return 0;
        }
    }
}
