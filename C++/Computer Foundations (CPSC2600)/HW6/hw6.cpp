#include "digraph.h"
#include <iostream>

int main(){

    Digraph p(8);

    p.addEdge(0,6);
    p.addEdge(0,5);
    p.addEdge(0,1);

    p.addEdge(1,2);
    p.addEdge(1,3);

    p.addEdge(2,5);
    p.addEdge(3,4);
    p.addEdge(4,5);
    p.addEdge(5,7);
    p.addEdge(5,7);
    p.addEdge(6,3);

    cout << "Matrix 1 :\n";
    p.display();
    p.displayDFS(0);

    int i = p.inDegree(3);
    p.inDegree(7);
    Digraph bfs (p.createBFS(0));

    cout << "Matrix 1 BFS :\n";
    bfs.display();
    
    Digraph test("test.in");
    
    cout << "Test Matrix :\n";
    test.display();
    
    Digraph test2("test2.in");
    
    cout << "Test2 Matrix :\n";
    test2.display();
    
    cout << i <<endl;
    return 0;
}