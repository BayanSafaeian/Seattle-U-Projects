// NAME: Bayan Safaeian
// FILE: intSet.cpp
// DESCRIPTION: Implementation of the IntSet class.

#include <iostream>
using namespace std;
#include "intSet.h"
#include <vector>

IntSet::IntSet() // creates empty set
{
    vector= 0; //0 is the same as 0000 0000 00 in binary which is the null set
}// each bit position coresponds to {1,2,3,4,5,6,7,8,9,10}


void IntSet::addElement(int val)
{
    if(!((val >=1) & (val<=10))){ //if value is not within the domain exit out of the function
    cout<< "INVALID VALUE: "<< val << " Enter an int from 1 to 10" << endl;
    return;
    }

    int add = 1; // 0000 0000 01 in binary
    add = add << (10-val);// shift bit left until it's in the correct spot
    vector = vector | add; // the or opperation only changes 0's to 1's when the coresponding bit is 1, which is ideal for adding.
}


void IntSet::removeElement(int val) // 1111 1111 11 
{
    if(!((val >=1) & (val<=10))){ //if value is not within the domain exit out of the function
    cout<< "INVALID VALUE: "<< val << " Enter an int from 1 to 10" << endl;
    return;
    }

    int remove=1;
    remove = remove << (10-val); 
    vector = vector ^ (vector & remove); // perform a bitwise xor after aligning the bits
}


bool IntSet::contains(int val) const
{
    if(!((val >=1) & (val<=10))){ //if value is not within the domain exit out of the function
    cout<< "INVALID VALUE: "<< val << " Enter an int from 1 to 10" << endl;
    return false;
    }

    int has=1;
    has = has << (10-val);

    int cont = vector & has; // the bitwise and operation turns all bits except for the desired bit to 0
    if(cont == has) //cont == has if the bit is found, otherwise it's zero and returns false
    return true;

    return false;
}


void IntSet::printSet() const
{
    int print = 512; // initialize bit to 1000 0000 00
    int i; //since i is used as both an indexer and a varible it has to be initialized
    int temp = vector;

    cout<< "{ ";
    for(i=1; i <= 10; i++){ //output elements in the set if they exist

        if((print & vector) !=0)// if bit is detected output that element as an int
        cout << i;

        if((temp & print) != 0) //if elment is detected remove it from temp bitstring
        temp = print ^ temp;
        
       	if((temp != 0) & ((print & vector) !=0)) // if temp bit is zero early that means we reached the end of the set, therefore we don't print commas
        cout<< ", ";

        print = print >> 1;
    }
    cout << " }" << endl;
}


void IntSet::printBit() const
{
    int print = 512; // initialize bit to 1000 0000 00
    int i; //since i is used as both an indexer and a varible it has to be initialized

    for(i=1; i <= 10; i++){ //output bitstring of the set
        
       	if((print & vector) !=0) //everytime bit is detected output 1, else output 0
        cout << 1;
        else
	cout << 0;

        if(i % 4 == 0) //prints a space every 4 elements
        cout << " ";
        
       	print = print >> 1;
    }
    cout << endl;
}


int IntSet::size() const
{
    int s = 512;
    int counter = 0; // create two varibles, one to increment everytime a value is found and the other to compare with the vector

    while (s !=0)
    {
     	if((s & vector) != 0)// if we detect the bit we increment counter
        counter++;

        s = s >> 1;
    }
    
    return counter;
}


IntSet IntSet::unions(const IntSet& operand) const // union of a set is everything in both sets, it's kind of like adding both sets
{
    IntSet u; // union of the two sets being opperated on
    u.vector = vector | operand.vector; // bitwise or both sets since that adds both without counting anything twice
    return u;
}


IntSet IntSet::intersect(const IntSet& operand) const // intersection only outputs elements in both sets
{
    IntSet n;
    n.vector = vector & operand.vector; // bitwise and both sets since that is only true when both set a and b have that bit
    return n;
}


IntSet IntSet::difference(const IntSet& operand) const// set A has elements that are also in set B subtracted out
{
    IntSet s_;
    s_.vector = vector ^ (vector & operand.vector); // bitwise subtract the bits that are in both elements
    return s_;
}


IntSet IntSet::complement() const
{
    IntSet sc;
    sc.vector = vector ^ universal; // the definition of compliment is the set - the universal set
    return sc;
}


bool IntSet::isEqual(const IntSet& operand) const
{
    if((vector ^ operand.vector) == 0) //if both sets are equivilent then the bitwise xor operation of them should always be zero
    return true;

    return false;
}
