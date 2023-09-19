// LinkedList.h (Header file)
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

using namespace std;

template <class T>
struct Node
{
    Node<T> *next;
    T data;
};

template <class T>
class LinkedList
{
private:
    Node<T> *head;
    Node<T> *last;

public:
    LinkedList()
    {
        head = NULL;
        last = NULL;
    };
    ~LinkedList()
    {
        while (head)
        {
            Node<T> *temp;
            temp = head;
            head = head->next;
            delete temp;
        }
    };
    void insert(T data)
    {
        if (!head)
        {
            // when there is no element in the list
            head = new Node<T>;
            head->data = data;
            head->next = NULL;
            last = head;
        }
        else
        {
            // when the list is not empty
            if (last == head)
            {
                // when the list has one element
                last = new Node<T>;
                last->data = data;
                last->next = NULL;
                head->next = last;
            }
            else
            {
                // when the list has more than one element
                Node<T> *insdata = new Node<T>;
                insdata->data = data;
                insdata->next = NULL;
                last->next = insdata;
                last = insdata;
            }
        }
    };
    T operator[](int index)
    {
        return get(index);
    };
    T get(int index)
    {
        if (!head)
        {
            throw out_of_range("LinkedList is empty.");
        }
        if (index == 0)
        {
            // returning the head element
            return this->head->data;
        }
        else
        {
            // Get the index'th element
            Node<T> *curr = this->head;
            for (int i = 0; i < index; ++i)
            {
                curr = curr->next;
            }
            return curr->data;
        }
        throw out_of_range("Index out of bounds");
    };
    void set(int index, T data)
    {
        if (!head)
        {
            throw out_of_range("LinkedList is empty.");
        }
        Node<T> *current = head;
        int currentIndex = 0;
        while (current)
        {
            if (currentIndex == index)
            {
                current->data = data;
                return;
            }
            current = current->next;
            currentIndex++;
        }
        throw out_of_range("Index out of range.");
    }
    T pop()
    {
        if (head == NULL)
        {
            throw runtime_error("Cannot pop from an empty list.");
        }
        Node<T> *curr = head;
        while (curr->next->next != NULL)
        {
            curr = curr->next;
        }
        Node<T> *temp = curr->next;
        curr->next = NULL;
        return temp->data;
    };
    int size()
    {
        if (!head)
        {
            return 0;
        }
        else
        {
            Node<T> *curr = this->head;
            int size = 1;
            while (curr->next != NULL)
            {
                size++;
                curr = curr->next;
            }
            return size;
        }
    };
    void print()
    {
        Node<T> *curr = this->head;
        cout << "[";
        while (curr->next != NULL)
        {
            cout << curr->data << ",";
            curr = curr->next;
        }
        cout << curr->data << "]" << endl;
    };
};

#endif // LINKEDLIST_H
