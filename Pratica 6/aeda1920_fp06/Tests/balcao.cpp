#include <queue>
#include <cstdlib>
#include "balcao.h"
#include "exceptions.h"

using namespace std;


Cliente::Cliente() {
    numPresentes= (rand() % 5) + 1;
}

int Cliente::getNumPresentes() const {
    return numPresentes;
}


Balcao::Balcao(int te): tempo_embrulho(te) {
    tempo_atual = 0;
    prox_chegada = rand() % 20 + 1;
    prox_saida = 0;
    clientes_atendidos = 0;
}

void Balcao:: proximoEvento()
{
    if(!clientes.empty()){
        if(prox_chegada<prox_saida){
            tempo_atual=prox_saida;
            chegada();
        }
        else{
            tempo_atual=prox_saida;
            saida();
        }
    }
    else{
        tempo_atual=prox_chegada;
        chegada();
    }
}


void Balcao::chegada()
{
    Cliente cl;
    cout <<"Tempo atual: "<<tempo_atual<<endl;

    if(clientes.empty()){
        prox_saida= tempo_atual + cl.getNumPresentes()*tempo_embrulho;
    }
    clientes.push(cl);
    cout<<"Chegou novo cliente com"<<cl.getNumPresentes()<<" presentes" << endl;
    prox_chegada= (rand() % 20)+1;
}

void Balcao::saida()
{
    Cliente cl;
    cout <<"Tempo atual: "<<tempo_atual<<endl;
    try{
        cl= getProxCliente();
    }
    catch(FilaVazia &e){
        cout<<e.getMsg()<<endl;
        return;
    }
    clientes.pop();
    cout << "Cliente atendido! "<< cl.getNumPresentes()<< " presentes "<<endl;
    clientes_atendidos++;
    if(clientes.empty() !=false){
        prox_saida= tempo_atual + clientes.front().getNumPresentes()*tempo_embrulho;
    }
}


int Balcao::getTempoAtual() const { return tempo_atual; }

int Balcao::getProxChegada() const { return prox_chegada; }


ostream & operator << (ostream & out, const Balcao & b1)
{
    out << "Numero de clientes atendidos: "<<b1.getClientesAtendidos()<< " Numero de clientes em espera: "<< b1.clientes.size();
    return out;
}

int Balcao::getTempoEmbrulho() const {
	return tempo_embrulho;
}

int Balcao::getProxSaida() const {
	return prox_saida;
}

int Balcao::getClientesAtendidos() const {
	return clientes_atendidos;
}

Cliente & Balcao::getProxCliente() {
    if (!clientes.empty()){
        return clientes.front();
    }
    throw (FilaVazia());
}

      
