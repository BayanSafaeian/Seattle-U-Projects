// NAME: Bayan Safaeian
// FILE: hw3.cpp
// DESCRIPTION: Tests IntSet class

#include <iostream>
using namespace std;
#include "intSet.cpp"

int main()
{
  
  //Tests written after main homework
  //1. Create the following sets with the universal domain: 

        //a. A = { x | x is an even number } 
        IntSet A;
        for(int i = 1; i <= 10; i++){
        
       	if(i % 2 == 0)// if i/2 has a zero remainder then its even
            A.addElement(i);
        }

	//b. B = { x | x is a number divisible by 3} 
        IntSet B;
        for(int i = 1; i <= 10; i++){
        
       	if(i % 3 == 0)// if i/3 has a zero remainder then it's divisible by 3
            B.addElement(i);
        }

	//c. C = {1, 2, 4, 6, 9}

        int c[] = {1, 2, 4, 6, 9};
        IntSet C;
        for(int i = 0; i < 5; i++)
            C.addElement(c[i]);
        

        
 
    //2. Compute the following sets: 

        //a. D = 𝐴 
        IntSet D = A;

        //b. E = A ∪ B 
        IntSet E = A.unions(B);

        //c. F = B ∩ C 
        IntSet F = B.intersect(C);

        //d. G = A – B 
        IntSet G = A.difference(B);

        //e. H = B ∪ (A ∩ C)
        IntSet H = B.unions(A.intersect(B));

        //f. I = (A ∪ B) - C 
        IntSet I = E.difference(C);
 
    //3. Print to the screen the sets A through C using printBit (print the name of the sets as well) 
        cout << "Bitstring of set A is: ";
        A.printBit();

        cout << "Bitstring of set B is: ";
        B.printBit();

        cout << "Bitstring of set C is: ";
        C.printBit();

    //4. Print to the screen the sets D through I using printSet. 
        cout << "Set D is: ";
        D.printSet();

        cout << "Set E is: ";
        E.printSet();

        cout << "Set F is: ";
        F.printSet();

        cout << "Set G is: ";
        G.printSet();

        cout << "Set H is: ";
        H.printSet();

        cout << "Set I is: ";
        I.printSet();
 
    //5. Print to the screen either True or False: 
        //a. 6 Î H?
        cout << "6 exists in set H is : ";
        if(H.contains(6))
            cout<<"True"<<endl;
        else
	        cout<<"False"<<endl;

        //b. 2 Î D?
        cout << "2 exists in set D is : "; 
        if(D.contains(2))
            cout<<"True"<<endl;
        else
	        cout<<"False"<<endl;

  //Tests written here
  cout<<endl;
  cout<<endl;
  cout<<endl;

  cout<<"Tests start here:"<<endl;
  
  IntSet a;
  IntSet b;

  a.addElement(1);
  a.addElement(2);
  a.addElement(5);
  a.addElement(3);

  b = a;

  cout << "set 'a' equals b is (should be true): ";
  if(a.isEqual(b))
  cout<<"True"<<endl;
  else
  cout<<"False"<<endl;


  cout<<"adding elements test:" <<endl;
  a.printSet();
  a.printBit();
  cout << endl;

  cout<<"remove elements test:" <<endl;
  a.removeElement(3);
  a.printSet();
  a.printBit();
  cout << endl;

  cout<<"copy set 'a' test:" <<endl;
  b.printSet();
  b.printBit();
  cout << endl;

  cout<<"unions of set 'a' and 'b' test:" <<endl;
  IntSet d;
  d= a.unions(b);
  d.printSet();
  d.printBit();
  cout << endl;

  cout<<"intersect of set 'a' and 'b' test:" <<endl;
  d= a.intersect(b);
  d.printSet();
  d.printBit();
  cout << endl;

  cout<<"difference of set 'a' and 'b' test:" <<endl;
  d= a.difference(b);
  d.printSet();
  d.printBit();
  cout << endl;

  cout<<"complement of 'a' test:" <<endl;
  d= a.complement();
  d.printSet();
  d.printBit();
  cout << endl;

  cout << "set 'a' equals b is (should be false): ";
  if(a.isEqual(b))
  cout<<"True"<<endl;
  else
  cout<<"False"<<endl;

  cout<<"Testing invalid inputs into set a, addElement:" <<endl;
  a.addElement(11);
  a.addElement(-5);
  cout << endl;

  cout<<"Testing invalid inputs into set a, removeElement:" <<endl;
  a.removeElement(11);
  a.removeElement(-5);
  cout << endl;

  cout<<"Testing invalid inputs into set a, contains:" <<endl;
  a.removeElement(11);
  a.removeElement(-5);
  cout << endl;

  cout << "Set a is of size: " << a.size() << endl;
  return 0;
}
