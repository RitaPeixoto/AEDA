/*
 * Account.cpp
 */
#include <iostream>
#include "Account.h"
#include<vector>
using namespace std;

Account::Account(string hold, string codeH, string codeA, double bal): holder(hold), codeHolder(codeH), codeIBAN(codeA), balance(bal) {}

Account::~Account(){ }

string Account::getCodH() const {
	return codeHolder;
}

string Account::getCodIBAN() const {
	return codeIBAN;
}

double Account::getBalance() const {
	return balance;
}

SavingsAccount::SavingsAccount (string hold, string codeH, string codeA, double bal, double pct):
		Account(hold, codeH, codeA, bal), rate(pct/100)
{ }


CheckingAccount::CheckingAccount(string hold, string codeH, string codeA, double bal,double lim):
			Account(hold, codeH, codeA, bal) {
	limit = lim;
}


TimeAccount::TimeAccount(string hold, string codeH, string codeA, double bal, double pct):
			SavingsAccount(hold, codeH, codeA, bal, pct) {
	funds_avail = balance*rate;
}
template <class T>
unsigned int numberDifferent (const vector<T> & v1) {
    sort(v1.begin(),v1.end());
    T aux;
    int counter=0;
    for(int i=0; i< v1.size();i++){
        if(i==0){
            counter ++;
            aux= v1[i];
        }

        else  if(aux==v1[i]){
                continue;
            }
        else
            counter ++;
        }

}

double getCharge () const{

}




