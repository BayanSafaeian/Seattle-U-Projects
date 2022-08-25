//myqueue.cpp 
#include "myqueue.h"

MyQueue::MyQueue(){} //constructor

MyQueue::~MyQueue(){ //destructor
    while(Head)
    {
        Node* t = Head; 
        Head = Head->next;
        delete t;
    }
}

bool MyQueue::empty() const{ //returns True if Queue is empty
    if (Size == 0) //Queue is empty when size is zero. Since it's returning a bool we can use this in our if statements.
    return true;

    return false;
}

int MyQueue::size() const{ //returns Size of Queue
    return Size;
}

int MyQueue::front() const{ //returns the Head Node's data
    return Head->data;
}

int MyQueue::back() const{ //returns the Head Node's data
    return Tail->data;
}

void MyQueue::push(int val){ //pushes a value at the end of the Queue 
    int Data = Head->data; //we need to have a temp int to pass through the if statement in order to only run it when Head is empty

    if(empty()){ // if Queue is empty we need to set Head to a new node that we're about to fill
    Head= new Node();
    Head->data = val;

    Size++; //Once head is filled, the size of the Queue is one since the queue is no longer empty.
    Tail = Head; // since this is the first element Tail and Head point to the same place
    return;
    }

    Tail->next = new Node(); // Tail's next pointer is set to the new node we're about to fill
    Tail = Tail->next;

    Tail->data = val; // Once Tail is set to the new node we fill in the data and increment the Size of the Queue by 1.
    Size++;
}

void MyQueue::pop(){ //removes the first Node from the Queue
    if(empty()) // if Queue is empty we return out of the function
    return;

    if(Size == 1){ // if size is 1 only Head has data so we just erase that
    Head->data = 0;
    Size--;
    return;
    }

    Node* Next = Head->next; //We need to keep the next pointer for Head before we delete it
    delete Head; // Deallocate memory 
    Head = Next;

    Size --; // since the pop function shrinks the array we need to decrement size by 1 everytime we call "pop"
}//end of myqueue.cpp 