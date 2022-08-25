#ifndef _MOVIEENTRY_H
#define _MOVIEENTRY_H

#include <string>
using namespace std;

class MovieEntry { 
private: 
   string title;  
   string genre;  
   string contentRating; 
   string tagline; 
   string director;  
   long id;  
   int release_year; 
public:

   MovieEntry();
   ~MovieEntry();
   void setTitle(string t); 
   void setGenre(string g); 
   void setContentRating(string rate); 
   void setTagline(string tline); 
   void setDirector(string dir); 
   void setId(long id); 
   void setYear(int year); 
   string getTitle() const; 
   string getGenre() const; 
   string getContentRating() const; 
   string getTagline() const; 
   string getDirector() const; 
   long getId() const; 
   int getYear() const; 
}; 

#endif
