#ifndef _CITYDICT_H_
#define _CITYDICT_H_
using namespace std; 
#include <string>


class CityDict
{
    private:

    struct CityNode { 
     string name; 
     string country; 
     int population; 
     CityNode* left = nullptr; 
     CityNode* right = nullptr;
    };
    CityNode * root;

    void Print_greater(CityNode * pointer, string name); // helper for greater
    CityNode* find(string name); //used to return the Node at the desired city name
    void del( CityNode * pointer); // helper for destructor
    CityNode* copyhelp(const CityNode * org); // helper for copy constructor
    
    
    int leftH = 0;
    int rightH= 0;
    CityNode * rotateLeft(CityNode * parent); //left rotation algorithm
    CityNode * rotateRight(CityNode * parent);// right rotation algorithm
    CityNode * balHelp(CityNode * bal , bool left); // balance helper function, defined recursively .. 
    // ..bool left is true when inputing left child, false when it's a right child
    
    public:

    CityDict(); //constructor
    CityDict(const CityDict& original); //copy constructor
    const CityDict& operator= (const CityDict& right); //Assignment operator
    ~CityDict(); //destructor
    void insert(string name, string country, int population); //adds new node to bst using city name as the key
    bool remove(string name); // removes node using city name as key
    string getCountry(string name); //returns the country name after being found using city name
    int getPopulation(string city); // returns population of the city after being found using city name
    void greater(string name); // prints out the city, country, population of the cities that come after the key entered
    void balance(); // public function to call balance in main
};

#endif
