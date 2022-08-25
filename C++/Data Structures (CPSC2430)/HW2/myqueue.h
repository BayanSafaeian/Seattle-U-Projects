//poly.h
#ifndef _MYQUEUE_H
#define _MYQUEUE_H

typedef int ElementType;
class MyQueue
{
    private:
    struct Node //Node has two data members, one to house the actual data in the node and the other is a pointer to the next node.
    {
        ElementType data; 
        Node* next = nullptr; 
    };

    Node* Head = new Node(); // We have a pointers for both the back and the front of the Queue
    Node* Tail = Head;
    int Size = 0; // tracks the size of the Queue which is very important for several of our methods
    public:
        MyQueue(); //constructor
        ~MyQueue(); //destructor
        bool empty() const; //returns True if Queue is empty
        int size() const; //returns Size of Queue
        int front() const; //returns the Head Node's data
        int back() const; //returns the Head Node's data
        void push(int val); //pushes a value at the end of the Queue 
        void pop(); //removes the first Node from the Queue

};
#endif //end of poly.h