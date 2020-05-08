/*
 * Postman.cpp
 */
#include "Postman.h"

unsigned int id_aux=1;
Postman::Postman(): id(0) {}

void Postman::setName(string nm){
	name = nm;
}

string Postman::getName() const{
	return name;
}

vector<Mail *> Postman::getMail() const {
	return myMail;
}

void Postman::addMail(Mail *m) {
	myMail.push_back(m);
}

void Postman::addMail(vector<Mail *> mails) {
	myMail.insert(myMail.end(),mails.begin(),mails.end());
}

unsigned int Postman::getID() const{
	return id;
}
//alinea e
Postman::Postman(string name){
    id=id_aux;
    id_aux ++;
    this->name=name;
}

bool Postman:: operator< (const Postman &p){
    vector<string> p1;
    vector<string> p2;
    vector<Mail *> :: iterator it =myMail.begin();
    for(; it!= myMail.end();it++){
        p1.push_back((*it)->getZipCode());
    }
    typename vector<Mail *> :: const_iterator it2 =p.myMail.begin();

    for(; it2!= p.myMail.end();it2++){
        p2.push_back((*it2)->getZipCode());
    }

    if(numberDifferent(p1)<numberDifferent(p2))
        return true;
    else
        return false;
}