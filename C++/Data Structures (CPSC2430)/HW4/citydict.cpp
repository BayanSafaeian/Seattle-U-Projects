#include "citydict.h"
#include <string>
#include <iostream>

using namespace std;

CityDict::CityDict(){ root = nullptr;}

CityDict::CityDict(const CityDict& original){ //copy constructor
    root = copyhelp(original.root); // we set to root equal to the copy of the original tree
}

const CityDict &CityDict::operator=(const CityDict &right){ //assigment operator
    this->root = copyhelp(right.root);//calls the same helper as the copy constructor
    return * this;
}

CityDict::CityNode *CityDict::copyhelp(const CityDict::CityNode *org){ // helper function for copy constructor and assignemtn op
    CityNode * dupe;
    if(org == nullptr){ // if a node is null we return a nullptr
        dupe = nullptr;
    return dupe;
    }
    
    dupe = new CityNode; // we create a new node and input every data member into the new tree
    dupe->name = org->name;
    dupe->country = org->country;
    dupe->population = org->population;
    
    dupe->left = copyhelp(org->left); // after thats done we fill in the rest of the nodes using a recursive call
    dupe->right = copyhelp(org->right);
    
    return dupe; // finally we return the node
}


CityDict::~CityDict()// destructor
{
    del(root); //calls helper delete function
}

void CityDict:: del( CityNode * pointer) // recursively deletes nodes in r
{   
    if(pointer == nullptr)
    return;
    
    del(pointer ->left);
    del(pointer -> right);
    delete pointer;
    pointer = nullptr;
}

void CityDict::insert(string name, string country, int population)//adds new node to bst using city name as the key
{
    CityNode * t = new CityNode(); // we create a new node so we can input it later
    t->name = name;
    t->population = population;
    t->country = country;

    if(!root){ // if theres no root node we set that equal to the node we created
        root = t;
        return;
    }
    
    CityNode * p = root;
    while (p){
	if( name == p->name) //if a node already has the same key we return
        return;

        if( name < p->name){ //if the key is less than the node name we walk left otherwise go right
            
            if(p->left)
            p = p->left;
            else{
            p->left = t;// if no node exists in the left spot thats where the node should go
            return;
            }
       }
       else{
           if(p->right) // same logic as the left subtree
            p = p->right;
            else{
            p->right = t;
            return;
            }
       }
    }

}

bool CityDict::remove(string name) // removes node using city name as key
{
        if(!root) // if tree is empty we return false
        return false;
        
    if(root->name == name){ // if we're deleting the rootnode we perform this logic, same as the case 1/0 since case 2 is already covered
        CityNode* del= root;
        if((!root->left) | (!root->right)){
            if(!root->left)
                root = root->right;
            else
                root = root->left;
            
            delete del;
            return true;
        }
        
       	if((!root->left) & (!root->right)){
            delete del;
            root = nullptr;
            return true;
        }
    }
    
    CityNode * p = root; // three pointers are made, p is the node were deleting
    CityNode * swap = nullptr; // swap is the successor
    CityNode * parent; //parent is the parent of the successor, it'll perform the adoption
    while (p){
        
       	if((name == p->name) | (!p)){ // if we find the node to delete we return out of while loop
            swap =p;
            p = nullptr;
            continue;
        }
        
       	if( name < p->name){ //if less than name go left and vise versa
            parent= p;
            p = p->left;
            continue;   
        }
        
       	if(name > p->name){
            parent = p;
            p = p->right;
            continue;
        }
    }
    p = swap; //recover value for p since it's null before
    
    if(!p)
    return false; // if p is still null that means we didn't find the node

    if(swap){
	if((swap->right !=nullptr) & (swap->left !=nullptr)){ // case 2
            parent = swap; 
            swap= swap->right; // we move to one of the potential spots for the successor and set parent to prev node
                
            while(swap->left){ // we move to further left node in right subtree
                parent = swap;
                swap= swap->left;
            }
            
            p->name = swap->name; //we swap the values
            p->country = swap->country;
            p->population = swap->population;
        }
        
       	if((swap->right !=nullptr) | (swap->left !=nullptr)){ //case 1
            
            if(parent->left->name == swap->name){ // adoption algorithm for parent left grandchild
                if(parent->left->left)
                    parent->left = swap->left;
                else if(parent->left->right)
                    parent->left = swap->right;
            }
            
            if(parent->right->name == swap->name){  // adoption algorithm for parent right grandchild
                if(parent->right->right)
                    parent->right->right = swap->right;
                else if(parent->right->left)
                    parent->right = swap->left;
            }
            
            delete swap; //deallocate
            return true;
        }
        
       	if((!swap->right) & (!swap->left)){// case 0
            if(parent->left !=nullptr){         // find which child is the node thats being deleted and set that pointer to null
                if(parent->left->name == swap->name)
                parent->left = nullptr;
            }
            
            if(parent->right->name == swap->name)
            parent->right = nullptr;
            
            delete swap; //deallocate
            return true;
        }
    }
    return false;
}

string CityDict::getCountry(string name) //returns the country name after being found using city name
{
    CityNode* p = find(name); // calls recursively defined find function for easy searching
    if(p) //if p is found we return the country
    return p->country;
    
    return "NA"; // if otherwise we return NA
}

int CityDict::getPopulation(string city)// returns population of the city after being found using city name
{
    CityNode * p = find(city); //same logic as getCountry
    if(p)
    return p->population;
    
    return -1; // return -1 if no city is found
}

void CityDict::greater(string name)// prints out the city, country, population of the cities that come after the key entered
{
    Print_greater(root, name); // calls recursive function for greater
}

void CityDict::Print_greater(CityNode * pointer, string name)/// helper for greater
{
    CityNode *p = pointer; 
    
    if(!pointer) //if node doesnt exist, return
    return;
    
    if((p->name < name) & (p->right !=nullptr)){ // if node p's name is less than name, we check the right
        if(p->right->name < name){ // if we are able to go right we check it's name, if it's greater we go to the right
            Print_greater(p->right, name);
        }
	return;
    }
    
    Print_greater(p->left, name); // go left
    if(p->name > name){ // process data under a condition
    cout << "City: "<< p->name << endl;
    cout << "Country: "<< p->country << endl;
    cout << "population: "<< p->population << endl;
    }
    cout<<endl; // spacer
    Print_greater(p->right, name); //go right
}

CityDict::CityNode *CityDict::find(string name)// if we find the Node return the node otherwise return empty pointer
{
     CityNode * p = root;
    while (p){ // same algorithm as the insert function but we return the node when it's found, otherwise return null
        
       	if( name == p->name)
            return p;

        if( name < p->name){
            
            if(p->left)
            p = p->left;
            else
            return nullptr;
        }else{
                
            if(p->right)
            p = p->right;
            else
            return nullptr;
       }
    }
    return nullptr;
}

CityDict::CityNode *CityDict::rotateLeft(CityDict::CityNode *parent){
    CityNode * axis = parent->right;
    parent->right= axis->left;
    axis->left = parent;
    rightH--;
    leftH++;
    return axis;
}

CityDict::CityNode *CityDict::rotateRight(CityDict::CityNode *parent){
    if(!parent)
        return nullptr;
    
    CityNode * axis = parent->left;
    if(parent->left->right)
        parent->left= axis->right;
    else
        parent->left = axis->right;
    
    axis->right = parent;
    rightH++;
    leftH--;
    return axis;
}

CityDict::CityNode *CityDict::balHelp(CityDict::CityNode *bal, bool left){
    
    if(!bal){
        if(left)
            leftH = 0;
        else
            rightH = 0;
            
        return nullptr;
    }
    
    bal->left = balHelp(bal->left, true);
    bal->right = balHelp(bal->right, false);
    
    while((leftH - rightH < -1) | (leftH - rightH > 1)){
    if(leftH - rightH > 1){
        bal = rotateRight(bal);
    }else if (leftH - rightH < -1)
        bal = rotateLeft(bal);
    }
    
    if(left){
        if(leftH >= rightH)
            leftH = leftH + 1;
        else
            rightH = rightH +1;
    }else{
        if(leftH >= rightH)
            leftH = leftH + 1;
        else
            rightH = rightH +1;
    }
    
    return bal;
}

void CityDict::balance(){
    root = balHelp(root, false);
    
    while(((leftH - rightH) < -1) | ((leftH - rightH) > 1)){
    if(leftH - rightH > 1){
        root = rotateRight(root);
        continue;
    }else if (leftH - rightH < -1)
        root = rotateLeft(root);
    }
    
    cout << leftH;
    cout << rightH;
    
    leftH = 0;
    rightH = 0;
    
    cout << root->name;
}