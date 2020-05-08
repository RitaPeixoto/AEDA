#include "caixa.h"
#include <sstream>


Objeto::Objeto(unsigned idObj, unsigned pesoObj): id(idObj), peso(pesoObj)
{}

unsigned Objeto::getID() const {
	return id;
}

unsigned Objeto::getPeso() const {
	return peso;
}

Caixa::Caixa(unsigned cap): id(ultimoId++), capacidade(cap), cargaLivre(cap)
{}

unsigned Caixa::getID() const {
	return id;
}

unsigned Caixa::getCargaLivre() const {
	return cargaLivre;
}

void Caixa::addObjeto(Objeto& obj) {
	cargaLivre -= obj.getPeso();
	objetos.push(obj);
}

void Caixa::resetID(){
	ultimoId = 1;
}
void Caixa:: dimininuishID(){ultimoId --;}


unsigned Caixa::getSize() const {
	return objetos.size();
}


ostream& operator<<(ostream& os, Objeto obj) {
	os << "O" << obj.id << ": " << obj.peso;
	return os;
}

unsigned Caixa::ultimoId = 1;


bool Objeto::operator<(const Objeto& o1) const {
    return peso<o1.getPeso();
}


bool Caixa::operator<(const Caixa& c1) const {
	return cargaLivre>c1.getCargaLivre();
}

string Caixa::imprimeConteudo() const {
    stringstream s;
    STACK_OBJS obj=objetos;

    if(objetos.empty())
    {
        s<< "Caixa ";
        s<<id;
        s<< " vazia!\n";

        return s.str();
    }
    s<<"C"<<id<<"[ ";
  while(!obj.empty()){
        s<<obj.top()<<" ";
        obj.pop();
    }
  s<<"]";
	return s.str();
}



