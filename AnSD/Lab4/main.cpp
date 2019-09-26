#include <iostream>
#include "s_list.h"
#include "d_list.h"

#define TypeName double

using namespace std;

template <typename T>
inline void printList(D_List<T> &lst);

int main()
{
    D_List <TypeName> lst;
    //TypeName data;

    lst.add_begin(2.4);
    lst.add_begin(2.66);
    //lst.add_end(2.02);
    printList(lst);
    cout << lst[2];

    /*int index;
    int choice;

    while(true){
        cout << "What you want to do?:\n"
                "1) Push back\n"
                "2) Push front\n"
                "3) Push middle\n"
                "4) Pop back\n"
                "5) Pop front\n"
                "6) Pop middle\n"
                "7) Show size\n"
                "8) Clear\n"
                "9) Exit\n\n";
        cin >> choice;
        system("cls");

        switch (choice)
        {
        case 1:
            {
            cout << "Input data: ";
            cin >> data;
            lst.push_back(data);
            break;
            }
        case 2:
            {
            cout << "Input data: ";
            cin >> data;
            lst.push_front(data);
            break;
            }
        case 3:
            {
            cout << "Input data and index: ";
            cin >> data >> index;
            if (index <= lst.GetSize() + 1) {
                lst.insert(data, index);
            } else {
              cout << "You have input wrong index! Try again\n";
            }
            break;
            }
        case 4:
            {
            if (lst.GetSize() == 0) {
                cout << "There is nothing to delete!\n";
                break;
            }
            lst.pop_back();
            break;
            }
        case 5:
            {
            if (lst.GetSize() == 0) {
                cout << "There is nothing to delete!\n";
                break;
            }
            lst.pop_front();
            break;
            }
        case 6:
            {
            if (lst.GetSize() == 0) {
                cout << "There is nothing to delete!\n";
                break;
            }
            cout << "Input index: ";
            cin >> index;
            if (index <= lst.GetSize()) {
                lst.removeAt(index);
            } else {
              cout << "You have input wrong index! Try again\n";if (lst.GetSize() == 0) {
                  cout << "There is nothing to delete!\n";
                  break;
              }
            }
            break;
            }
        case 7:
            {
            cout << "The current size of List is: " << lst.GetSize() << endl;
            break;
            }
        case 8:
            {
            lst.clear();
            cout << "The List has been cleared\n";
            break;
            }
        case 9:
            {
            lst.clear();
            return 0;
            }
        }
        cout << endl;
        printList(lst);
        cout << endl;
    }*/
}

template<typename T>
inline void printList(D_List<T> &lst)
{
    for (int i = 0; i < lst.GetSize(); i++)
        cout << lst[i] << endl;
}
