
#include "animal.h"
#include <sstream>
using namespace std;

/*
 * Classe Animal
 */

int Animal:: maisJovem=999;
Animal::Animal(string nome, int idade){
    this->nome=nome;
    this->idade=idade;
    this->vet=NULL;
    if(Animal::maisJovem>idade){
        Animal::maisJovem=idade;
    }
}

string Animal::getNome() const {
	return nome;
}
int Animal::getIdade() const {
    return this-> idade;
}
int Animal::getMaisJovem(){
    return maisJovem;
}
void Animal::setVeterinario(Veterinario *v) {
    this->vet = v;
}
Veterinario * Animal::getVet() {
    return this->vet;
}
bool Animal::eJovem()const{
    return false;
}


Cao::Cao(string nome, int idade, string raca):Animal(nome,idade) {
    this->raca=raca;
}

string Cao::getRaca() const{
    return this->raca;
}

bool Cao::eJovem()const{
    if(idade<5){
        return true;
    }
   return Animal::eJovem();
}

string Cao::getInformacao() const{
    string info;
    if(vet==NULL) {
        info = this->nome + ", " +to_string(this->idade) + ", "+ this-> raca;
    }
    else {
        info = this->nome + ", " +to_string(this->idade) + ", "+ this-> raca; + ", "+ this->vet->getNome()+ ", "+ to_string(this->vet->getCod());
    }

    return info;

}

Voador::Voador(int vmax, int amax){
    this->velocidade_max = vmax;
    this->altura_max = amax;
}
int Voador:: getVelocidade()const{
    return this->velocidade_max;
}
int Voador::getAltura () const{
    return this->altura_max;
}
Morcego::Morcego(string nome, int idade, int vmax, int amax): Animal(nome, idade), Voador(vmax,amax){
}

bool Morcego:: eJovem()const{
    if(this->idade<4){
        return true;
    }
    return false;
}


string Morcego::getInformacao() const{
    string info;
    if(vet==NULL)
        info=this->nome+", "+to_string(this->idade)+", "+to_string(this->getVelocidade())+", "+to_string(this->getAltura());
    else
        info=this->nome+", "+to_string(this->idade)+", "+this->vet->getNome()+", "+to_string(this->vet->getCod())+", "+to_string(this->getVelocidade())+", "+to_string(this->getAltura());
    return info;
}
