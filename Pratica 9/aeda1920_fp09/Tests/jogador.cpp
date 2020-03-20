#include "jogador.h"


void Jogador::adicionaAposta(const Aposta & ap)
{
    apostas.insert(ap);
}

unsigned Jogador::apostasNoNumero(unsigned num) const
{
    unsigned res=0;
    tabHAposta:: const_iterator it = apostas.begin();
    for (it ; it!= apostas.end(); it++){
        if((*it).contem(num)){
            res ++;
        }
    }
    return res;
}


tabHAposta Jogador::apostasPremiadas(const tabHInt & sorteio) const
{

    tabHAposta result;
    tabHAposta:: const_iterator it = apostas.begin();
    for(it; it!= apostas.end();it++){
        if((*it).calculaCertos(sorteio)>=3){
            result.insert(*it);
        }
    }
    return result;

}
