#include "aposta.h"
#include <iostream>
#include <sstream>

using namespace std;


bool Aposta::contem(unsigned num) const
{
    // Find if "num" is contained in "numeros"
    unordered_set<unsigned>::const_iterator it = numeros.find(num);

    // Return true if it's contained , false otherwise
    return (it != numeros.end());
}

void Aposta::geraAposta(const vector<unsigned> & valores, unsigned n)
{
    // Clear numeros
    numeros.clear();
    vector<unsigned>::const_iterator it = valores.begin();
    for(it; it!= valores.end();it++){
        if(numeros.size() ==n)    // Check if we already got to the bet requested size
            break;
        else{
            if(!contem(*it))// Add the number to the bet, if it is not there yet
                numeros.insert(*it);
            }
        }
}


unsigned Aposta::calculaCertos(const tabHInt & sorteio) const
{
    unsigned res=0;
    // Search if they are all contained
    tabHInt::const_iterator it=sorteio.begin();
    for(it; it!= sorteio.end(); it++){
        if(contem(*it)){
            res++;
        }
    }
    return res;
}


bool Aposta::operator==(const Aposta &a1)const{
    if(a1.getNumeros()==numeros)
        return true;
    return false;
}





