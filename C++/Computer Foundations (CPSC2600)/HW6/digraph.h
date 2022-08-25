#ifndef _DIAGRAPH_H
#define _DIAGRAPH_H

#include <string>
using namespace std;
class Digraph{
    private:

    int** matrix; // a two-dimensional array for storing the edges 
    int size; // the number of vertices in the graph 
    bool* visited; //an array of bool used for the traversal functions, we always delete it after the traversals are done so we can reset the values easier 

    void dfsHalp(int vertex); // helper for displayDFS, nothing special really

    public:
        
        int accessElm( int a, int b) const; //this is kind of a helper for the copy constructor, since we can't directly access it otherwise
        Digraph(const Digraph & original);// copy constructor 
        Digraph(int n);// creates a matrix with n rows/collumns with 0 filled in all of the data;
        Digraph(string filename); //creates matrix based on the file we enter in
        ~Digraph(); //An inappropriate destructor. lmao gottem
        void addEdge(int a, int b); //adds edge (a,b) to the graph, where a goes into b
        void  display()  const; //displays adjacency matrix of graph
        void displayDFS(int vertex); //displays depth first search result starting at vertex
        Digraph& createBFS(int vertex);// creates new graph from the breath first search algortithm
        int inDegree(int i) const; //returns inDegree of vertex i
};
#endif