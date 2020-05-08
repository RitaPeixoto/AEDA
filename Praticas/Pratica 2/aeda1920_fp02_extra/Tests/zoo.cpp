#include "zoo.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
using namespace std;

/*
 * Classe Zoo
 */

int Zoo::numAnimais() const {
	return animais.size();
}

int Zoo::numVeterinarios() const {
	return veterinarios.size();
}

void Zoo::adicionaAnimal(Animal *a1) {
    animais.push_back(a1);
}

bool Zoo::animalJovem(string nomeA) {
    for(unsigned int i=0; i<animais.size();i++){
        if(animais[i]->getNome()==nomeA){
            if(animais[i]->eJovem()){
                return true;
            }
        }
    }
    return false;
}

string Zoo::getInformacao() const{
    typename vector<Animal*> :: const_iterator it=animais.begin();
    string info;
    while(it!=animais.end()){
        info+= (*it)->getInformacao() + "\n";
        it++;
    }
    return info;
}
void Zoo::alocaVeterinarios(istream &isV) {
    string nome,cod;

    while(!isV.eof()){
        getline(isV,nome);
        getline(isV,cod);
        Veterinario *v= new Veterinario(nome,stoi(cod));
        veterinarios.push_back(v);
    }

    int vet=0;
    for(unsigned int x=0;x<animais.size();x++){
        animais[x]->setVeterinario(veterinarios[vet]);
        vet++;
        vet=vet%veterinarios.size();
    }

}

bool Zoo::removeVeterinario(string nomeV){
    bool found_vet=false;
    int pos;

    for (size_t i = 0; i < veterinarios.size(); i++) {
        if (veterinarios[i]->getNome() == nomeV) {
            veterinarios.erase(veterinarios.begin() + i);
            pos = i;
            found_vet=true;
            break;
        }
    }

    if(found_vet==true){
        if(pos==veterinarios.size())
            pos=0;

        for (size_t i = 0; i < animais.size(); i++) {
            if (animais[i]->getVet()->getNome() == nomeV)
                animais[i]->setVeterinario(veterinarios[pos]);
        }
    }
    else
        return false;

    return true;
}

bool Zoo::operator<(Zoo &zoo2) const {
    int sum_z1, sum_z2;
    typename vector<Animal*>::const_iterator it= animais.begin();
    typename vector<Animal*>::const_iterator it_2= zoo2.animais.begin();

    while(it!=animais.end()){
        sum_z1+=(*it)->getIdade();
        it++;
    }
    while(it_2!=zoo2.animais.end()){
        sum_z2+=(*it_2)->getIdade();
        it_2++;
    }

    if(sum_z1<sum_z2)
        return true;
    else
        return false;

}
