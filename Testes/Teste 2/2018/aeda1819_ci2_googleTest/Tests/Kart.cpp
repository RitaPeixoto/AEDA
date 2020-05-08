#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
#include <sstream>
#include <vector>
#include <time.h>
#include <string>
#include "Kart.h"

using namespace std;

//To help build better array
string itos(int i){
    stringstream s;
    s << i;
    return s.str();
}

void CGrupo::criaGrupo()
{
    float cilindradas[4]  = {134,250,450,600};
    bool avariados[3]  = {true,false,false};

    srand (1);   //Criar Pistas e Karts de Teste
    for(int i=1;i<=50;i++){
        vector<CKart> frota;
        for(int j=1;j<=50;j++){
            frota.push_back(CKart(avariados[rand()% 3],
                                  ("KART - "+itos(i))+itos(j),(i-1)*50+j,cilindradas[(rand() % 4)]));
        }
        adicionaPista(CPista("Pista - "+itos(i),frota));
    }
}


vector <CKart> CPista::getKartsAvariados()
{
    vector<CKart> aux;
    for (vector<CKart>::iterator it = frotaKartsPista.begin() ; it != frotaKartsPista.end(); ++it) {
        if ((it)->getAvariado()) aux.push_back((*it));
    }
    return aux;
}

bool compareKarts( CKart c1,  CKart c2){
    return c1.getNumero()<c2.getNumero();
}

//Exercicio 1 a)     
vector<CKart> CGrupo::ordenaKarts()
{
	vector<CKart> vord;
	vector<CKart>::const_iterator it_k;
	vector<CPista>::iterator it_p=pistasG.begin();
	for(it_p; it_p!=pistasG.end();it_p++){
	    for(it_k=(*it_p).getFrotaActual().begin(); it_k!=(*it_p).getFrotaActual().end();it_k++){
            vord.push_back(*it_k);
	    }
	}
	sort(vord.begin(), vord.end(),compareKarts);
	return vord;
    
}

//Exercicio 1 b)  
int CGrupo::numAvariados(int cilind)
{
    vector<CKart>::iterator it_k;
    vector<CPista>::iterator it_p=pistasG.begin();
    int counter=0;
    for(it_p; it_p!=pistasG.end();it_p++){
        for(it_k=(*it_p).getFrotaActual().begin(); it_k!=(*it_p).getFrotaActual().end();it_k++){
            if((*it_k).getCilindrada() == cilind && (*it_k).getAvariado()){
                counter ++;
            }
        }
    }
    return counter;
}

//Exercicio 1 c)   
bool CPista::prepararCorrida(int numeroKarts, int cilind)
{
    int counter=0;
    vector<CKart> aux;
    vector<CKart>::iterator it;
    if(frotaKartsPista.size()-getKartsAvariados().size()<numeroKarts){
        return false;
    }
    it=frotaKartsPista.begin();
    while(it!=frotaKartsPista.end()){
        if((!(*it).getAvariado()) && ((*it).getCilindrada()==cilind)){
            aux.push_back(*it);
        }
        it++;
    }
    it=aux.begin();
    if(aux.size()<numeroKarts){
        for(it;it!=aux.end();it++){
            kartsLinhaPartida.push(*it);
        }
        return false;
    }
    else{
        for(it;it!=aux.end();it++){
            while(counter!=numeroKarts){
                kartsLinhaPartida.push(*it);
                counter++;
            }

        }
        return true;
    }
}

//Exercicio 1 d) 
int CPista::inicioCorrida()
{
    int s= kartsLinhaPartida.size();
    for(int i=0; kartsLinhaPartida.size();i++){
        CKart c= kartsLinhaPartida.front();
        kartsEmProva.push_back(c);
        kartsLinhaPartida.pop();
    }
    return kartsEmProva.size();
}

