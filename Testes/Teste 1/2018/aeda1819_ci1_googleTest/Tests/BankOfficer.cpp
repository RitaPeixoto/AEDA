/*
 * BankOfficer.cpp
 */
#include "BankOfficer.h"

unsigned int BankOfficer::aux = 1;
BankOfficer::BankOfficer(): id(0) {}

void BankOfficer::setName(string nm){
	name = nm;
}

string BankOfficer::getName() const{
	return name;
}

vector<Account *> BankOfficer::getAccounts() const {
	return myAccounts;
}

void BankOfficer::addAccount(Account *a) {
	myAccounts.push_back(a);
}

unsigned int BankOfficer::getID() const{
	return id;
}


// ----------------------------------------------------------------------------------------------

BankOfficer::BankOfficer(string name) {
    this->name=name;
    id=aux;
    aux++;
}

bool BankOfficer::operator>(const BankOfficer &b2){
    if(myAccounts.size()>b2.getAccounts().size()){
        return true;
    }

    else if(myAccounts.size()==b2.getAccounts().size()){
        if(name >b2.getName())
            return true;
    }
    return false;
}



