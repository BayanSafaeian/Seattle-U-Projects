#include <iostream>
#include <fstream>
#include "citydict.h"
#include <sstream>
#include <string>

using namespace std;

int main()
{
    CityDict dict;
    ifstream fin("cities.csv");

        string line;
        
        getline(fin, line);
        while(getline(fin, line))
        {
            istringstream input(line);
            
            string name, country;
            int pop;
            
            getline(input,name,',');
            getline(input,country,',');
            
            if(input >> pop)
            dict.insert(name, country, pop);
        }

    fin.close(); //once every line has been read, close the file
    //cities.print();
    //cout<< endl;

    CityDict dict2(dict);
    //dict.remove("Manila"); //Delhi
    //cities.print();
    //dict.greater("Karachi");
    //dict2.greater("Los Angeles");
    
    bool ex = true;
    
    while(ex){
        string input;
        cin >> input;
        if(input == "cp"){
            cin >> input;
            cout << input << ": " <<endl;
            cout << "country: " <<dict.getCountry(input) <<endl;
            cout << dict.getPopulation(input) <<endl;
            cout <<endl;
        }
        
        if(input == "grt"){
            cin >> input;
            dict.greater(input);
        }
        
        if(input == "rm"){
            cin >> input;
            dict.remove(input);
        }
        
        if(input == "rcp"){
            dict.remove(input);
            cin >> input;
            cout << input << ": " <<endl;
            cout << "country: " <<dict.getCountry(input) <<endl;
            cout << dict.getPopulation(input) <<endl;
            cout <<endl;
        }
        
        //if()
    }
    return 0;
}