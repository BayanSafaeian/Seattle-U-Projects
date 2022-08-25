#include "moviedb.h"
#include "movieentry.h"
#include <iostream>
#include <string>
using namespace std;

MovieDB::MovieDB(){ // constructor
    pr = new PrimeCalc;
    pr->primes_31(pr->primes, pr->bitstr);
    
    hashish = new Node *[maxsize] {};
}
MovieDB::~MovieDB(){ // destructor

    for(int i = 0; i < maxsize; i++){ // check all elements in previous array
        Node *trav = hashish[i];
        Node * prev = trav;
        while(trav){ //traverse through entire linked list and delete it
            prev = trav;
            trav = trav->next;
            delete prev;
    }
    }
}

void MovieDB::rehash(){
    if(loadfact <= .25){ // if loadfact is less than or equal to .25 that means we decrement the power
        curpwr--;
    }else
        curpwr++; //otherwise we increase the power 
    
    int oldsize = maxsize;
    
    if(curpwr <= 5){
        int temp[6] = {1,2,3,7,17,31}; // hash maps less than 2^5 are stored here for easy access;
        maxsize = temp[curpwr];
    }
    else{
        maxsize = pr->loc_nearestPrime(1 << (curpwr));
    }
    
    cout << " Hashmap changed from " << oldsize << " : to -> " << maxsize <<endl;
    
    Node ** old = hashish;
    
    hashish = new Node *[maxsize] {} ;
    cursize = 0; //reset current size
    
    for(int i = 0; i < oldsize; i++){ // check all elements in previous array
        Node *trav = old[i];
        while(trav){ //traverse through entire linked list
            int h = Hash(trav->movie_record->getTitle()); // find new hash value
            
            MovieEntry record; //create new movie entry to input values
    
            record.setContentRating( trav->movie_record->getContentRating());
            record.setDirector(trav->movie_record->getDirector());
            record.setGenre(trav->movie_record->getGenre());
            record.setId(trav->movie_record->getId());
            record.setTagline(trav->movie_record->getTagline());
            record.setTitle(trav->movie_record->getTitle());
            record.setYear(trav->movie_record->getYear());

            put(record);

            Node* prev = trav; // set prev node
            trav = trav->next;
            delete prev; // delete prev after we moved
    }
    }
    
    loadfact = cursize/maxsize; //recalculate loadfact
    delete old;
}


bool MovieDB::put(const MovieEntry &m){ // function to add new elms into Hash map
    
    if(loadfact >= .75) //if we go outside of the parameters we need to resize hashtable
        rehash();

    int i = Hash(m.getTitle()); //calculate hash

    Node* trav = hashish[i]; //set node to index position of the hash

    Node * p = new Node; // set values for p
    
    p->movie_record = new MovieEntry; //create new movie entry to input values
    
    p->movie_record->setContentRating( m.getContentRating());
    p->movie_record->setDirector(m.getDirector());
    p->movie_record->setGenre(m.getGenre());
    p->movie_record->setId(m.getId());
    p->movie_record->setTagline(m.getTagline());
    p->movie_record->setTitle(m.getTitle());
    p->movie_record->setYear(m.getYear());
    

    if(!trav){ //insert at first spot if index pos is empty
        hashish[i] = p;
        cursize++; //always increment size when adding elements
        loadfact = (cursize * 1.0)/maxsize; // needs to be multiplied by 1.0 to convert it into a double
        return true;
    }
    
    Node * prev = trav; //keep track of previous node so we can insert at it's next pointer
    while (trav){ // keep going until there's no more elements or if title is found
        if(trav->movie_record->getTitle() == m.getTitle()) //if we find dupelicate return false b/c we cant insert
            return false;
            
        prev = trav;
        trav = trav->next;
    }
    prev->next = p; //insert at last spot
    cursize++; 
    loadfact = (cursize * 1.0)/maxsize; // needs to be multiplied by 1.0 to convert it into a double
    
    return true;
}
//The put() inserts a movie into a hash table if it does not exist. It returns true if insertion is successful and false otherwise. 
MovieEntry *MovieDB::get(const string &title){
    int i = Hash(title);
    Node* db = hashish[i];
    
    while(db){
        if(db->movie_record->getTitle() == title)
            return db->movie_record;
        
        db = db->next;
    }
        
    if(db == nullptr){
        cout << "NOT FOUND" <<endl;
        return nullptr;
    }

    return db->movie_record;
}
//The get() retrieves a movie (MovieEntry) with the specified title. It returns NULL if no such a movie exists. 

int MovieDB::Hash(string s) { //hash function
    unsigned int sum = 0;
        for(char c : s ){
            sum=(sum*31+c)%maxsize; 
        }
return sum; 
}

void MovieDB::remove(const string &title){
    int i = Hash(title); //calculate hash
    Node* trav = hashish[i]; //set node to index position of the hash
    
    if(!trav)
        return;
    
    Node * prev = trav; //keep track of previous node so we can insert at it's next pointer
    while (trav){ // keep going until there's no more elements or if title is found
        if(trav->movie_record->getTitle() == title){ //if we find dupelicate we can delete
            
            prev->next = trav->next;
            delete trav;
            hashish[i] = nullptr;
            cursize--;
            loadfact = (cursize * 1.0)/maxsize; // needs to be multiplied by 1.0 to convert it into a double
            
            if(loadfact <= .25) //if we go outside of the parameters we need to resize hashtable
                rehash();
            
            return;
        }
        prev = trav;
        trav = trav->next;
    }
    
    cout << "NOT FOUND" << endl;   
}

// Code for Prime Calc Class is below

MovieDB::PrimeCalc::PrimeCalc(){ //constructor
    primes_31(primes , bitstr);
}

MovieDB::PrimeCalc::~PrimeCalc(){ //destructor
    delete primes;
    delete bitstr;
}

int MovieDB::PrimeCalc::prime(int n){ // calculates bitstrings of primes so we can perform bit ops
    int a = 32%n;
    int b;
    if(a == 0)
	return 4294967295/((1 << n) -1); //returns bitstring for multiples of 2
    
    b = (4294967295/((1 << n) -1)) << (n-1); // we use modified geometric series formula to calulate the string
    b = b | (1 << (a-1)); // ex. 010101 would be 2^1 +2^4 +2^6, which can be quickly calculated using geo series formula

    b = b | (1 << (a-1)); // ex. 010101 would be 2^1 +2^4 +2^6, which can be quickly calculated using geo series formula
    
    return b ;
}

int*  MovieDB::PrimeCalc::primes_31(int a[], int * p){ // returns an array of bitstrings of primes from 2 to 31
   
   for(int i = 0; i < 11; i++)
       p[i] = prime(a[i]);
   
   return p;
}

void  MovieDB::PrimeCalc::inputprimes(int bitstr , int start){ // generates primes and inserts them into prime array
    int j = 1 << 31;

    int k = max_elm;

    if(bitstr & (j != 0)){ // we need compare out of the for loop because shifting bits with negative numbers causes some errors
        primes[k] = start;
        k++;
        bitstr = bitstr ^ j;
    }
    
    j= 1 << 29; //we need to shift the first bit left like this otherwise the bitstring will get messed up
    
    for(int i = 2; i < 32; i = i+2){

        if( (bitstr & j) != 0){
            primes[k] = start + i;// process the data
            k++;
            if(k >= Size) // shuts down the incrementation when Size is exceded
                return;
            bitstr = bitstr ^ j; // we remove the bit we just counted
        }
        
        j = j >>2; // any bit after the first bit will shift like normal
    }
    max_elm = k;
}

void MovieDB::PrimeCalc::resize(){ 
    int prevSize =Size;
    Size = size(pwr);
    int * p = new int[Size] {0};
    
    for(int i= 0; i < prevSize; i++)
        p[i] = primes[i];
    
    delete primes;
    primes = p;

    int start = 32;

    while (start < primes[max_elm]){
        start = start + 32;
    }
    
    int end = sqrt2(pwr);

    for(int i = start; i < end; i = i +32)
        inputprimes(find_primes(i + 32), i +1);

}

int MovieDB::PrimeCalc::sqrt2(int pwr){ // calculates the squareroot of max size of array
    if(pwr%2 !=0){
        int temp = 1 << (pwr/2); //shifts over to closest even power
        return (1415 * temp)/1000; // result is multiplied by an estimate of the ratio of sqrt of 2
    }else
        return (1 << (pwr/2));// even power's rt are shifted by half
}

int MovieDB::PrimeCalc::size (int pwr){ // calculates size of the primes array
    return (sqrt2(pwr) * 200)/(pwr * 69 - 200); // the eq is a rearanged form of sqrt(n)/(pwr/2 * ln(2) -1), where ln(2) is about 69/100
}// the equation is ultimately derived from n/(ln(n) -1), which almost accurately calculates the number of primes up to that number

int MovieDB::PrimeCalc::find_primes(int search){
    if(search > CAP){
        CAP = 1 << pwr; //reset CAP size
        resize();
    }
    
    int bitst = bitstr[0];
    
    bool firstbit = false;
    for(int i = 1; i< 11; i++){
        
        int mod = (search -31)%primes[i];
        
        if(mod ==0){ // we skip the rest of the loop  when we already have the correct bitstr
            bitst = bitst | bitstr[i];
            firstbit = true;
            continue;
        }
        
        int tempstr = bitstr[i] ^ (1 << 31); // we need to xor out the first bit otherwise our bitstring is ruined
        bitst = bitst | tempstr >> (primes[i] - mod); // now we can safely shift left now that the number is postive
        bitst = bitst | (1 << (31 -primes[i] + mod)); // re-add extracted bit
    }

    if(search > 1024){
        for(int i = 11; i < max_elm; i++){
            bitst =  bitst | (1 << (search %primes[i])); 
        }
    }
    
    bitst = bitst ^ -1; // we find the compliment of the string which will have 1's in positions of binary integers

    return bitst;
}

int MovieDB::PrimeCalc::loc_nearestPrime(int p){ //locates nearest prime to the number we sqaured

    int pw = 0;
    int org = p;
    for(int j = pw; j <= 32; j++){ //finds the power of 2 so we can use it in our caclulations
        p = p >>1;

        if( p == 0){
            pw = j;
            break;
        }
    }

    if(pw > pwr) // resize power if its greater than the current power
        if(pw%2 ==1){
            pwr = pw + 1;
        }else
            pwr = pw;

    int found = find_primes(org); // return bitstring of primes we found in that range

    int i =  1 <<1;
    int count = 0;

    if (org < 32) // if we put in a value less than 32 we just start from that value and count background
        i = 1 << (31 - org);
    
    while( count < 32 &&((found & i) == 0)){ // count everytime we shift back
        i = i <<1;
        count++;
    }

    if(count == 32 ) // if we dont find it we look at the previous 32 numbers
        return loc_nearestPrime(org -32);

    return org-count -1; // we return the cloest prime
}