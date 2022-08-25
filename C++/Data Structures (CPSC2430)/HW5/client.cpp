#include <iostream>
#include <fstream>
#include "moviedb.h"
#include "movieentry.h"
#include <sstream>
#include <string>

using namespace std;
int
main ()
{
  ifstream fin ("movies.csv"); //change to csv when done

  string line;
  getline (fin, line);
  MovieDB db;

  while(getline (fin, line)){
      MovieEntry entry;

      istringstream input (line);

      string id, title, genre, release_year, content_rating, tagline, director;
      int year;
      long ID;

      getline (input, id, ',');
      getline (input, title, ',');
      getline (input, genre, ',');
      getline (input, release_year, ',');
      getline (input, content_rating, ',');
      getline (input, tagline, ',');
      getline (input, director);

      stringstream d (id);
      stringstream y (release_year);

      d >> ID;
      y >> year;

      entry.setId (ID);
      entry.setTitle (title);
      entry.setGenre(genre);
      entry.setYear (year);
      entry.setContentRating (content_rating);
      entry.setTagline (tagline);
      entry.setDirector (director);

      db.put (entry);
    }

  bool ex = true;
  while(ex){ 

  cout <<"Enter Function for db (get , rmv , ex), make sure to use a ',' to seperate inputs of titles"<< endl;
  string input;
  cin >> input;
  
  if (input == "ex")
    {                           //exits out of while loop
      ex = false;
    }

  if (input == "get")
    {                           // calls get function

      cin >> input;
      string i;
      while (input != ","){     // we keep accepting inputs until the user puts in a comma

          i.append (input);     // all inputs before a comma are put into one string to be processed
          cin >> input;

          if (input != ",")     // only output spaces when the next word isn't a comma
            i.append (" ");
        }
      MovieEntry *get = db.get (i);

      if(get != nullptr){
      cout << "ID: " << get->getId() << endl;
      cout << "Title: " << get->getTitle() << endl;
      cout << "Genre: " << get->getGenre() << endl;
      cout << "Content Rating: " << get->getContentRating() << endl;
      cout << "Tagline: " << get->getTagline() << endl;
      cout << "Director: " << get->getDirector() << endl;
      cout << "Release Year: " << get->getYear() << endl;
      }
    }

  if (input == "rmv"){// calls remove function

      cin >> input;
      string i;
      while (input != ","){     // we keep accepting inputs until the user puts in a comma

          i.append (input);     // all inputs before a comma are put into one string to be processed
          cin >> input;

          if (input != ",")     // only output spaces when the next word isn't a comma
            i.append (" ");
        }
      db.remove (i);
    }
  }

  return 0;
}