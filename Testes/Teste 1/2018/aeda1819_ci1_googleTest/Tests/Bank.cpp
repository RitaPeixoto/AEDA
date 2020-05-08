/*
 * Bank.cpp
 */

#include "Bank.h"
#include <algorithm>
#include <string>

Bank::Bank() {}

void Bank::addAccount(Account *a) {
	accounts.push_back(a);
}

void Bank::addBankOfficer(BankOfficer b){
	bankOfficers.push_back(b);
}

vector<BankOfficer> Bank::getBankOfficers() const {
	return bankOfficers;
}

vector<Account *> Bank::getAccounts() const {
	return accounts;
}


// ----------------------------------------------------------------------------------------------

double Bank::getWithdraw(string cod1) const{
    double total=0;
    for(unsigned int i=0; i<accounts.size();i++){
        if(accounts[i]->getCodH()==cod1){
            total+= accounts[i]->getWithdraw();
        }
    }
	return total;
}



vector<Account *> Bank::removeBankOfficer(string name){
	vector<Account *> res;
	for(unsigned int i=0; i<bankOfficers.size();i++){
        if(bankOfficers[i].getName()==name){
            res= bankOfficers[i].getAccounts();
            bankOfficers.erase(bankOfficers.begin()+i);
            break;
        }
	}
	return res;
}

const BankOfficer & Bank::addAccountToBankOfficer(Account *ac, string name) {
    vector<BankOfficer> :: iterator it=bankOfficers.begin();
    for(it; it!=bankOfficers.end();it++){
        if((*it).getName()==name) {
            (*it).addAccount(ac);
            return (*it);
        }
    }
    throw NoBankOfficerException(name);
}

bool CompareAccounts(Account *a1, Account *a2){
    if((*a1).getBalance()==(*a2).getBalance()){
        if((*a1).getCodIBAN()<(*a2).getCodIBAN())
            return true;
    }
    else if((*a1).getBalance()<(*a2).getBalance())
        return true;
    return false;
}

void Bank::sortAccounts() {
    sort(accounts.begin(), accounts.end(), CompareAccounts);
}


