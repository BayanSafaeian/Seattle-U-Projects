// NAME: Bayan Safaeian
// FILE: intSet.h
// DESCRIPTION: Definition of the IntSet class.

#ifndef INTSET_H
#define INTSET_H


#include <iostream>
using namespace std;

class IntSet {

  private:
    //Complete the private section of the class
    int vector; //this is what will be used to represent the bitstring of the set
    int universal = (1<<10)-1;// universal set is 1111 1111 11 or 1023 in integer form

  public: 
    
    // Default constructor: the domain of the set is {1, 2, 3, ..., 10}.
    // The set is initially a null set.
    IntSet();

    // Adds the value to the set if not already an element.
    void addElement(int val);

    // Removes the value if it is in the set.  
    // Nothing happens if the value is not in the set.
    void removeElement(int val);

    // Returns true if the set contains the value. 
    // Returns false otherwise.
    bool contains(int val) const;

    // Displays the set to the screen in the format: {1, 3, 4}
    void printSet() const;

    // Displays the set to the screen using the bit string format.
    void printBit() const;

    // Returns the number of elements in the set.
    int size() const;


    IntSet unions(const IntSet& operand) const; //returns union of the sets, which is the bitwise or opperation between the two.

    IntSet intersect(const IntSet& operand) const; //returns intersect of the sets, which is the bitwise and opperation between the two.

    IntSet difference(const IntSet& operand) const; //returns intersect of the sets, which is the bitwise xor, shown as a^(a & b) where b is the opperand/subtracted set.

    IntSet complement() const; // returns complement of a which is the xor of set a and the universal set.

    bool isEqual(const IntSet& operand) const; // returns true if the sets operated on are equal, if not return false.

};

#endif
