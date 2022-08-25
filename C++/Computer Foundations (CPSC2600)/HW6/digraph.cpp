#include "digraph.h"
#include <iostream>
#include <deque>
#include <fstream>
#include <sstream>

Digraph::Digraph(int n){ // constructor with n vertrices as input
    matrix = new int* [n]; //creates the main array that holds the other arrays
    size = n; //update size

    for(int i = 0; i < size; i++){
        int * p = new int[size] {0}; // creates array of integers, all of them are zero. 
        matrix[i] = p; // each indivial array of zeroes is put into the main array, thus creating collumns and rows
    }
}

Digraph::Digraph( const Digraph & original){ //copy constructor
    size = original.size; //update size

    matrix = new int* [size]; //creates the main array that holds the other arrays

    for(int i = 0; i < size; i++){
        int * p = new int[size] {0}; // creates array of integers, all of them are zero.
        
        for( int j = 0; j < size; j++){
            p[j] = original.matrix[i][j];
        }
        matrix[i] = p; // each indivial array of zeroes is put into the main array, thus creating collumns and rows
    }
}

Digraph :: Digraph(string filename) {
    ifstream fin (filename);
    string line;
    int max = 0;

    deque<int> mydeque;

    while(getline (fin, line)){ //finds maximum element to create Digraph

        istringstream input (line);
        int row , column;
        string c;
        getline (input, c, ',');

           if(line.find(",") == std::string::npos){
            continue;
        }

        stringstream a (c);
        a >> row;
        input >> column;

           if(max < row)
            max = row;

    if(max < column)
            max = column;

    mydeque.push_back(row); //stores verticies
    mydeque.push_back(column);
    }
    
    matrix = new int* [max+1]; //creates the main array that holds the other arrays
    size = max+1; //update size

    for(int i = 0; i < size; i++){
        int * p = new int[size] {0}; // creates array of integers, all of them are zero. 
        matrix[i] = p; // each indivial array of zeroes is put into the main array, thus creating collumns and rows
    }

    while(!mydeque.empty()){ // adds them to the grpah
        int i, j;
        i = mydeque.front();
        mydeque.pop_front();

        j = mydeque.front();
        mydeque.pop_front();

           addEdge(i,j);
    }
}

Digraph::~Digraph(){
    for(int i = 0; i < size; i++){
        int * p = matrix[i]; // set p to the index of a collumn
        delete p; // deallocate memory
        p = nullptr; // set pointer to null
    }
}

void Digraph::addEdge(int a, int b){

    if( (a < 0) | (a >= size) | (b < 0) | (b >= size)) //testing if a or b is within the parameters;
        return;

    int * p = matrix[a]; // go to position 'a' for the row
    p[b] = 1; // go to collumn 'b' and put in 1 which means we have added the edge at (a,b).
}

void Digraph::display() const{

    int * p;
    for(int i= 0; i < size; i++){
        p = matrix[i];
        for(int j = 0; j < size; j++){
            cout << p[j] <<  " ";
        }
        cout<<endl; //moves onto new line
    } 
    cout<<endl; //adds a space for the future display opperations
}

void Digraph::displayDFS(int vertex){ // this houses the caps of the DFS logic, meanwhile the helper does most of the work

    if( (vertex < 0) | (vertex >= size) )//recuring test to see if we are putting a valid vertex 
        return;//we just need it in the display DFS function because the helper will never access an invalid vertex
    
    cout << "DFS visit order starting at " << vertex << ":" <<endl;

    visited = new bool [size] {false}; // create an array of bools with all verticies set to false.
    dfsHalp(vertex);
    delete visited; //erase visited for another search

    cout<< endl;
    cout<< endl;
}

void Digraph::dfsHalp(int vertex){
    if(visited[vertex]) // if we visited that node we return, simple
        return;

    cout << vertex << " "; // everytime we visit an unvisited node we print it out
    visited[vertex] = true; // if we haven't vistited the node we carry on with our algorithmn
    int *p = matrix[vertex]; // we then check that row for any 1's, this means we check if that vertex is going INTO another vertex;

    for(int i= 0; i < size; i++){
        if(p[i] == 1) // if we find a 1 that means we can go into another vertex
            dfsHalp(i);
    }
}

Digraph &Digraph::createBFS(int vertex){
    Digraph * bfs = new Digraph(this->size);

    if( (vertex < 0) | (vertex >= size) )//recuring test to see if we are putting a valid vertex
        return *bfs;

    cout << "BFS visit order starting at " << vertex << ":" <<endl;

    visited = new bool [size] {false}; // create an array of bools with all verticies set to false.
    std::deque<int> mydeque;

    mydeque.push_back(vertex);// put in starting element
    visited[vertex] = true; // set node we visted equal to zero

    cout << vertex << " ";

    while (!(mydeque.empty())){
        int * p = matrix[mydeque.front()];
        for(int i = 0; i < size; i++){
            
            if( (p[i] == 1) & (visited[i] == false)){
                bfs->addEdge(mydeque.front() , i);
                cout << i << " ";
                mydeque.push_back(i);
                visited[i] = true;
            }
        }

        //cout << mydeque.front() << " ";
        mydeque.pop_front();
    }

    cout<< endl;
    cout<< endl;

    return *bfs;
}

int Digraph::inDegree(int i) const{
    if( (i < 0) | (i >= size) ) //recuring test to see if we are putting a valid vertex
        return -1;

    int count = 0;
    int * p = nullptr;

    for(int j = 0; j < size; j++){
        p = matrix[j]; // go through each row  
        count = count + p[i]; // add the value at pos[i] on that array
    }
    return count;
}