/*
 * jogo.cpp
 */

#include "jogo.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

//alinea c
unsigned int Jogo::numPalavras(string frase)
{
  if ( frase.length() == 0 ) return 0;

  unsigned n=1;
  size_t pos = frase.find(' ');
  while (pos != string::npos) {
    frase = frase.substr(pos+1);
    pos = frase.find(' ');
    n++;
  }
  return n;
}


Jogo::Jogo(){}


Jogo::Jogo(list<Crianca>& lc2)
{
    this->criancas=lc2;
}
//alinea a
void Jogo::insereCrianca(const Crianca &c1)
{
   criancas.push_back(c1);
}
//alinea a
list<Crianca> Jogo::getCriancasJogo() const
{
    return this->criancas;
}

//alinea b
string Jogo::escreve() const
{
    stringstream res;
    list<Crianca>::const_iterator it;
    for(it = criancas.begin(); it!= criancas.end();it++){
        res<<(*it).escreve()<<endl;
    }
    return res.str();
}
//alinea c
Crianca& Jogo::perdeJogo(string frase)
{
    list<Crianca> aux=criancas;

    int n=numPalavras(frase)-1;//nao contar a criança inicial
    list<Crianca>::iterator it_i=criancas.begin();
    list<Crianca>::iterator it_f=criancas.end();
    while(criancas.size()>1){
        int n_children=criancas.size();
        int p=n%n_children;
        for(int i=1; i<=p;i++) {
            it_i++;
            if (it_i == it_f) it_i = criancas.begin();
        }
        cout << "sai: "<< it_i->escreve()<<endl;
        it_i=criancas.erase(it_i);
        if(it_i==it_f) it_i=criancas.begin();
    }

    return *it_i;
}
//alinea d
list<Crianca>& Jogo::inverte()
{
    criancas.reverse();
    return criancas;
}
//alinea e
list<Crianca> Jogo::divide(unsigned id)
{
    list<Crianca> res;
    list<Crianca>::iterator it;
    for(it = criancas.begin(); it!= criancas.end();it++){
        if((*it).getIdade()>id){
            res.push_back(*it);
            it=criancas.erase(it);
        }
    }
    return res;
}
//alinea a
void Jogo::setCriancasJogo(const list<Crianca>& l1)
{
    criancas.insert(criancas.end(), l1.begin(), l1.end());
}

// alinea f
bool Jogo::operator==(Jogo& j2)
{
    if(criancas.size() != j2.getCriancasJogo().size()) return false;
    list<Crianca> list_j2=j2.getCriancasJogo();
    list<Crianca>::iterator it_1=criancas.begin();
    list<Crianca>::iterator it_2= list_j2.begin();
    int c_1,c_2;//counters
    //percorre as duas listas e se encontrar uma criança diferente na mesma posiçao retorna falso
    while(it_1!=criancas.end()){
        if (((*it_1).getNome() == (*it_2).getNome()) && ((*it_1).getIdade() == (*it_2).getIdade())){
            advance(it_1, 1);
            advance(it_2, 1);
        }

        else
            return false;
    }
    return true;
}

// alinea g
list<Crianca> Jogo::baralha() const
{
    list<Crianca> res;
    int pos;
    list<Crianca>::const_iterator it = criancas.begin(), it2;
    srand(time(NULL));

    for (int i = 1; i < criancas.size() + 1; i++) {
        pos = rand() % i;
        it2 = res.begin();
        advance(it2, pos);
        res.insert(it2,(*it));
        it++;
    }

    return res;
}

