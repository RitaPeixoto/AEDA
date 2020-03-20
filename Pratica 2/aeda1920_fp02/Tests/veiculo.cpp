#include "veiculo.h"
#include <iostream>

using namespace std;
//alinea a
Veiculo::Veiculo(string mc, int m, int a){
    this->marca=mc;
    this->mes  =m;
    this->ano  =a;
}
int  Veiculo::getAno() const{
    return ano;
}
Motorizado::Motorizado(string mc, int m, int a,string c,int cil):Veiculo (mc,m,a){
    this-> combustivel= c;
    this-> cilindrada= cil;
}

Automovel::Automovel(string mc, int m, int a,string c, int cil): Motorizado(mc,m,a,c,cil){}

Camiao::Camiao(string mc, int m, int a,string c, int cil,int cm): Motorizado(mc,m,a,c,cil){
    this->carga_maxima=cm;
}
Bicicleta::Bicicleta(string mc, int m, int a,string t):Veiculo (mc,m,a){
    this->tipo=t;
}

string Motorizado::getCombustivel() const{
    return combustivel;
}
string Veiculo::getMarca() const{
    return marca;
}

//alinea c

int Veiculo::getMes() const{
    return mes;
}
int Veiculo::info() const{
    cout << "Marca: " << marca<<endl;
    cout<< "Data: "<<mes << " / "<<ano<<endl;
    return 3;
}
int Motorizado::getCilindrada() const {
    return cilindrada;
}
int Motorizado::info() const{
    int aux= Veiculo::info();
    cout << "Combustivel: "<< combustivel<<endl;
    cout << "Cilindrada: "<< cilindrada<<endl;
    return 2+ aux;
}

int Automovel::info() const {
    Motorizado::info();
}
int Camiao::getCargaMaxima()const{
    return carga_maxima;
}
int Camiao::info() const{
    int aux= Motorizado::info();
    cout << "Carga máxima: "<< carga_maxima<<endl;
    return 1+aux;
}
string Bicicleta::getTipo() const{
    return tipo;
}
int Bicicleta::info() const{
    int aux= Veiculo::info();
    cout << "Tipo: "<< tipo<<endl;
    return 1+ aux;
};
//alinea e
bool Veiculo::operator < (const Veiculo & v) const{
    return (ano<v.ano || ano==v.ano && mes<v.mes);
}

//alinea g
float Veiculo::calcImposto() const {
    return 0;
}
float Motorizado::calcImposto() const{
    if((combustivel == "gasolina" && cilindrada<=1000) || (combustivel != "gasolina" && cilindrada <=1500)) {
        if (ano > 1995)
            return 14.56;
        else
            return 8.10;
    }
    else if ((combustivel == "gasolina" && cilindrada>1000 && cilindrada<=1300) || (combustivel != "gasolina" && cilindrada > 1500 && cilindrada<=2000)) {
        if (ano > 1995)
            return 29.06;
        else
            return 14.56;
    }
    else if ((combustivel == "gasolina" && cilindrada>1300 && cilindrada<=1750) || (combustivel != "gasolina" && cilindrada > 2000 && cilindrada<=3000)) {
        if (ano > 1995)
            return 45.15;
        else
            return 22.65;
    }
    else if ((combustivel == "gasolina" && cilindrada>1750 && cilindrada<=2600) || (combustivel != "gasolina" && cilindrada > 3000)) {
        if (ano > 1995)
            return 113.98;
        else
            return 54.89;
    }
    else if (combustivel == "gasolina" && cilindrada>2600 && cilindrada<=3500) {
        if (ano > 1995)
            return 181.17;
        else
            return 87.13;
    }
    else if (combustivel == "gasolina" && cilindrada>3500) {
        if (ano > 1995)
            return 320.89;
        else
            return 148.37;
    }
    return Veiculo::calcImposto();
}
float Automovel::calcImposto() const {
    return Motorizado::calcImposto();
}
float Camiao::calcImposto() const {
    return Motorizado::calcImposto();
}
float Bicicleta::calcImposto() const {
    return Veiculo::calcImposto();
}