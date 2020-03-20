#include "frota.h"
#include <string>

using namespace std;


//alinea b
void Frota::adicionaVeiculo(Veiculo *v1){
    veiculos.push_back(v1);
}
int Frota::numVeiculos() const{
    return veiculos.size();
}
int Frota::menorAno() const{
    int anoV;
    if(numVeiculos()==0)
        return 0;
    int menor=veiculos[0]->getAno();
    for (int i=0; i< numVeiculos();i++){
        anoV=veiculos[i]->getAno();
        if(anoV<menor) {
            menor = anoV;
        }
    }
    return menor;
}
//alinea d
ostream & operator<<(ostream & o, const Frota & f)
{
    vector<Veiculo *>::const_iterator it=f.veiculos.begin();
    while(it!=f.veiculos.end()) {
        (*it)->info();
        it++;
    }
    return o;
}
//alinea f
vector<Veiculo *> Frota::operator () (int anoM) const{
    vector<Veiculo*>:: const_iterator it=veiculos.begin();
    vector<Veiculo*> final;
    if(veiculos.size()==0){

    }
    while(it!= veiculos.end()){
        if((*it)->getAno()==anoM){
            final.push_back(*it);
        }
        it++;
    }
    return final;
}

//alinea h
float Frota::totalImposto() const{
    float aux=0;
    for(int i=0; i< veiculos.size();i++){
        aux += veiculos[i]->calcImposto();
    }
    return aux;
}

/*Qual é a diferença de p.e veiculos[i]->getAno() e veiculos[i].getAno()
 *O porquê de float calcImposto() const = 0{} não funcionar??
 */