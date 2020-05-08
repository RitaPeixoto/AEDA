/*
 * CinemaFinder.cpp
 */

#include "CinemaFinder.h"
#include "Cinema.h"
#include "Film.h"
#include <algorithm>

CinemaFinder::CinemaFinder() { }

CinemaFinder::~CinemaFinder() { }

void CinemaFinder::addFilm(Film *f1) {
	FilmPtr fp1;
	fp1.film = f1;
	films.insert(fp1);
}

void CinemaFinder::addCinema(const Cinema &c1)
{ cinemas.push(c1); }

tabHFilm CinemaFinder::getFilms() const
{ return films; }

priority_queue<Cinema> CinemaFinder::getCinemas() const
{ return cinemas; }


// TODO


//b1
list<string> CinemaFinder::filmsWithActor(string actorName) const {
    // TODO
	list<string> res;
	tabHFilm aux= films;
	tabHFilm::iterator it= aux.begin();
	while(it!=aux.end()){
	   if((*it).film->actorExists(actorName)){
	       res.push_back((*it).film->getTitle());
	   }
	    it++;
	}
    return res;

}


//b2
void CinemaFinder::addActor(string filmTitle, string actorName) {

	// TODO
    bool found =false;
    tabHFilm aux= films;
    tabHFilm::iterator it= aux.begin();
    while(it!=aux.end()){
        if((*it).film->getTitle()==filmTitle){
            (*it).film->addActor(actorName);
            found =true;
            break;
        }
        it++;
    }
    if(!found){
        list<string> a = {actorName};
        Film* f=new Film(filmTitle);
        FilmPtr fptr;
        fptr.film=f;
        films.insert(fptr);
    }


}


//c1
string CinemaFinder::nearestCinema(string service1) const {
    string cName="";

    priority_queue<Cinema> temp = cinemas;
    list<string> ser;

    while(!temp.empty()){
        ser = temp.top().getServices();
        for(list<string>::const_iterator it = ser.begin();it!=ser.end();it++){
            if(*it==service1)
                return temp.top().getName();
        }
        temp.pop();
    }

    return cName;
}


//c2
void CinemaFinder::addServiceToNearestCinema(string service1, unsigned maxDistance) {

	// TODO
    if(cinemas.empty())
        throw CinemaNotFound();

    priority_queue<Cinema> temp = cinemas;

    while(!temp.empty()){
        Cinema cin = temp.top();

        if(cin.getDistance()<maxDistance){
            cin.addService(service1);
            temp.pop();
            temp.push(cin);
            cinemas=temp;
            return;
        }
        temp.pop();
    }

    throw CinemaNotFound();
}
