#ifndef _MOVIEDB_H
#define _MOVIEDB_H

#include <string>
#include "movieentry.h"
using namespace std;
class MovieDB {
private:

    class PrimeCalc {
        private:
            int CAP = 1024; //maxmium element we can reach with current primes
            int Size = 11;
            int pwr = 10 ; // 2^pwr = CAP
            int max_elm = 11;
            
            int prime(int n); // calculates bitstrings of primes so we can perform bit ops
            void inputprimes(int bitstr , int start);
            void resize();

            int sqrt2(int pwr); // calculates the squareroot of max size of array
            int size (int pwr); // calculates size of the primes array

            int find_primes(int search);  // generates primes and inserts them into prime array

        public:

        int * primes = new int[11]{2,3,5,7,11,13,17,19,23,29,31}; //these are our seed primes, they can be used to find more primes as needed, new primes will be added to this array too
        int * bitstr = new int[11]{0};

        PrimeCalc(); //constructor
        ~PrimeCalc(); //destructor

        int* primes_31(int a[], int * p); // returns an array of bitstrings of primes from 2 to 31
        int loc_nearestPrime(int p); //locates nearest prime to the number we sqaured

};

    struct Node{
        MovieEntry * movie_record = nullptr;
        Node * next = nullptr;
    };
 
PrimeCalc * pr = nullptr;
int curpwr = 4 ; // current power
int maxsize = 17; //maximum size
int cursize = 0; //current size
Node ** hashish = nullptr;
double loadfact = cursize/maxsize; // needs to be updated everytime we do a put or remove operation

int Hash(string s); //hash function given in pdf

void rehash(); //resizing algorithm for hashmap
public:

MovieDB(); // constructor
~MovieDB(); // destructor

bool put(const MovieEntry &m);
//The put() inserts a movie into a hash table if it does not exist. It returns true if insertion is successful and false otherwise. 
MovieEntry * get(const string &title); 
//The get() retrieves a movie (MovieEntry) with the specified title. It returns NULL if no such a movie exists.
void remove(const string &title); 
//The remove() removes the movie with the specified title. Do not forget to deallocate dynamic memory used by the MovieEntry object. 
};
#endif