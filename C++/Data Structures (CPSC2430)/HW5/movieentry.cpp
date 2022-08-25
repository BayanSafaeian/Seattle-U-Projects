#include "movieentry.h"
#include <string>

MovieEntry::MovieEntry(){
}

MovieEntry::~MovieEntry(){
}

void MovieEntry::setTitle(string t){
    title = t;
}

void MovieEntry::setGenre(string g){
    genre = g;
}

void MovieEntry::setContentRating(string rate){
    contentRating = rate;
}

void MovieEntry::setTagline(string tline){
    tagline = tline;
}

void MovieEntry::setDirector(string dir){
    director = dir;
}

void MovieEntry::setId(long id){
    this->id = id;
}

void MovieEntry::setYear(int year){
    release_year = year;
}

string MovieEntry::getTitle() const{
    return title;
}

string MovieEntry::getGenre() const{
    return genre;
}

string MovieEntry::getContentRating() const{
    return contentRating;
}

string MovieEntry::getTagline() const{
    return tagline;
}

string MovieEntry::getDirector() const{
    return director;
}

long MovieEntry::getId() const{
    return id;
}

int MovieEntry::getYear() const{
    return release_year;
}