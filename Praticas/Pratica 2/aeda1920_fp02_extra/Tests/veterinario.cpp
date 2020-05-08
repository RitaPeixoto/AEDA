
#include "veterinario.h"
#include <sstream>
using namespace std;

Veterinario::Veterinario(string nome, int cod){
    this->nome=nome;
    this->codOrdem=cod;
}
long Veterinario:: getCod() const{
    return codOrdem;
}
string Veterinario::getNome() const {
    return nome;
}

