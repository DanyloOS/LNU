#ifndef D_LIST_H
#define D_LIST_H
#include <iostream>

template <typename T>
class D_List
{
public:
    D_List();
    ~D_List();

    void add_begin(T data);
    void add_end(T data);
    void del_begin();
    void del_end();
    int search(T data);
    void add_mid(int index);
    void del_mid(int index);

    int getSize() { return Size; }
    T& operator[](const int index);

private:
    template<typename T1>
    class Node
    {
    public:
        Node * pNext;
        Node * pPrevious;
        T data;

        Node(T data = T(), Node *pPrevious = nullptr, Node *pNext = nullptr)
        {
            this->data = data;
            this->pNext = pNext;
            this->pPrevious = pPrevious;
        }
    };

    int Size;
    Node<T> *first;
    Node<T> *last;
};

template<typename T>
D_List<T>::D_List()
{
    Size = 0;
    first = nullptr;
    last = nullptr;
}

template<typename T>
D_List<T>::~D_List()
{
//    clear();
}

template<typename T>
void D_List<T>::add_begin(T data)
{
    if (first == nullptr) {
        first = new Node<T>(data);
    } else {
        Node<T> *current = this->first;

        while (current->pNext != nullptr)
        {
            current = current->pNext;
        }
        current->pPrevious = current;
        current->pNext = new Node<T>(data);
    }
    Size++;
}

template<typename T>
void D_List<T>::add_end(T data)
{
    Node<T> *current;
    if (first == nullptr) {
        first = new Node<T>(data);
    } else {
        current = this->last;

        while (current->pNext != nullptr)
        {
            current = current->pNext;
        }
        current->pPrevious = current;
        current->pNext = new Node<T>(data);
    }
    Size++;
    this->last = current;
}


//template<typename T>
//void D_List<T>::clear()
//{
//    while (Size)
//    {
//        pop_front();
//    }
//}

template <typename T>
T & D_List<T>::operator[](const int index)
{
    int counter;

    Node<T> *current = this->first;

    if (index <= Size/2){
        counter = 0;
        current = this->first;
        while (current != nullptr) {
            if (counter == index){
                return current->data;
            }
            current = current->pNext;
            counter++;
        }
    } else {
        counter = Size-1;
        current = this->last;
        while (current != nullptr) {
            if (counter == index){
                return current->data;
            }
            current = current->pPrevious;
            counter--;
        }
    }
}

//template<typename T>
//void D_List<T>::push_front(T data)
//{
//    head = new Node<T>(data, head);
//    Size++;
//}

//template<typename T>
//void D_List<T>::insert(T data, int index)
//{
//    if (index == 0)
//    {
//        push_front(data);
//    }
//    else
//    {
//        Node<T> *previous = this->head;

//        for (int i = 0; i < index - 1; i++)
//        {
//            previous = previous->pNext;
//        }

//        Node<T> *newNode = new Node<T>(data, previous->pNext);

//        previous->pNext = newNode;

//        Size++;
//    }
//}

//template<typename T>
//void D_List<T>::removeAt(int index)
//{
//    if (index == 0)
//    {
//        pop_front();
//    }
//    else
//    {
//        Node<T> *previous = this->head;
//        for (int i = 0; i < index - 1; i++)
//        {
//            previous = previous->pNext;
//        }

//        Node<T> *toDelete = previous->pNext;

//        previous->pNext = toDelete->pNext;

//        delete toDelete;

//        Size--;
//    }
//}

//template<typename T>
//void D_List<T>::pop_back()
//{
//    removeAt(Size - 1);
//}

#endif // D_LIST_H
