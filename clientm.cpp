#include <iostream>
#include "myqueue.cpp"
using namespace std;

string sarr[180] = {""};

int main()
{
    cin>> sarr[0];
    string command;
    int s = 0;
    MyQueue q;

    while(sarr[s] != "exit")
    {   
        s++;
        cin>> sarr[s];
    }

    s=0;

    while (command != "exit")
    {
        command = sarr[s];

        if(command == "push")
        {
            s++;
            q.push(stoi(sarr[s]));
            s++;
            cout << "The first element is: " << q.front() << "    ";
		    cout << "The last element is: " << q.back() << endl;
        }

        if(command == "pop")
        {
            //cout<< q.front()<<endl;
            q.pop();
            s++;
        }

    }
    return 0;
}