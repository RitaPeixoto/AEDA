/*
 * Hospital.cpp
 */

#include "Hospital.h"
#include <algorithm>
using namespace std;

Hospital::Hospital(unsigned trayC):trayCapacity(trayC)
{ }

void Hospital::addDoctor(const Doctor &d1) {
	doctors.push_back(d1);
}

list<Doctor> Hospital::getDoctors() const {
	return doctors;
}

void Hospital::addTrays(stack<Patient> tray1) {
	letterTray.push_back(tray1);
}

list<stack<Patient> > Hospital::getTrays() const {
	return letterTray;
}



unsigned Hospital::numPatients(string medicalSpecialty) const
{
    unsigned counter=0;
    list<Doctor> :: const_iterator it= doctors.begin();
    for(it; it!=doctors.end();it++){
        if((*it).getMedicalSpecialty() == medicalSpecialty){
            counter += (*it).getPatients().size();
        }
    }

	return counter;

}
bool compareDoctors ( Doctor d1, Doctor d2){
    if(d1.getPatients().size() == d2.getPatients().size()){
        if(d1.getMedicalSpecialty()==d2.getMedicalSpecialty()){
            return d1.getCode()<d2.getCode();
        }
        return (d1.getMedicalSpecialty() < d2.getMedicalSpecialty());
    }
    return d1.getPatients().size() < d2.getPatients().size();
}
void Hospital::sortDoctors() {
	doctors.sort(compareDoctors);
}



bool Hospital::addDoctor(unsigned codM1, string medicalSpecialty1) {
	list<Doctor>::iterator it=doctors.begin();
	Doctor d(codM1,medicalSpecialty1);
	int counter=0;
	for(it; it!=doctors.end(); it++){
	    if((*it).getMedicalSpecialty() == medicalSpecialty1){
	        counter ++;
	    }
	}
    if(counter >= 3){
        return false ;
    }
    doctors.push_back(d);
	return true;

}



queue<Patient> Hospital::removeDoctor(unsigned codM1) {
	queue<Patient> p1;
	list<Doctor>::const_iterator it=doctors.begin();
	for(it; it!=doctors.end();it++) {
        if ((*it).getCode() == codM1) {
            p1 = (*it).getPatients();
            doctors.erase(it);
            return p1;
        }
    }
	throw(Hospital::DoctorInexistent());

}


bool Hospital::putInLessBusyDoctor(unsigned cod1, string medicalSpecialty1) {
    list<Doctor>:: iterator it=doctors.begin();
    list<Doctor>:: iterator it_aux=doctors.begin();
    Patient p1(cod1, medicalSpecialty1);
	int aux=0, previous_aux;
	for(it; it!=doctors.end(); it++) {
        if ((*it).getMedicalSpecialty() == medicalSpecialty1 &&
            (*it).getPatients().size() < (*it_aux).getPatients().size()) {
            it_aux = it;
        }
    }
    (*it_aux).addPatient(p1);
    if(it_aux ==doctors.begin() && (*it_aux).getMedicalSpecialty() !=medicalSpecialty1)
        return false;
    return true;
}



void Hospital::processPatient(unsigned codM1) {
	list<Doctor>::iterator it=doctors.begin();
    list<Doctor>::iterator aux;
    bool exists=false;
	for(it; it!=doctors.end(); it++){
	    if((it)->getCode() ==codM1){
	        aux=it;
	        exists=true;
	        break;
	    }
	}
	if(!exists) return;//nada acontece
	if((aux)->getPatients().size()==0) return; //nada acontece

    Patient p=(aux)->removeNextPatient();
   for(auto it=letterTray.begin(); it!=letterTray.end();it++){
       if((it)->size() < trayCapacity){
           (it)->push(p);
           return;
       }
   }
   stack<Patient> s;
   s.push(p);
   letterTray.push_back(s);
}


unsigned Hospital::removePatients(unsigned codP1) {
    int toRet = 0;
    for (auto iter = letterTray.begin(); iter != letterTray.end(); iter++) {
        if (iter->top().getCode() == codP1) {
            toRet++;
            iter->pop();
        }
    }
    while (letterTray.front().size() == 0) {
        letterTray.erase(letterTray.begin());
    }

    list<stack<Patient>>::iterator iter = letterTray.begin();
    if (letterTray.size() > 0) {
        while (iter != letterTray.end()) {
            if (iter->size() == 0) {
                iter=letterTray.erase(iter);
            }
            else
                iter++;
        }
    }
    return toRet;
    /*unsigned counter=0;
	list<stack<Patient>> ::iterator it=letterTray.begin();
	for(it; it!= letterTray.end();it++){
	    if((*it).top().getCode() ==codP1){
            (*it).pop();
            counter++;
            if((*it).empty()){
                letterTray.erase((it));
            }
	    }
	}
	return counter;*/

}



