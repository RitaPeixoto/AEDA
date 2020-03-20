#include "parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli): numMaximoClientes(nMaxCli=0), lotacao(lot=0){
    vagas=lot;
}
unsigned int ParqueEstacionamento::getNumLugares() const{//alinea a
    return lotacao;
}

unsigned int ParqueEstacionamento::getNumMaximoClientes() const{ //alinea a
    return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string & nome) const{//alinea b
    for(int i=0; i<clientes.size();i++){
        if(clientes[i].nome== nome){
            return i;
        }
    }
    return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string & nome){//alinea b
    if (clientes.size()==numMaximoClientes){
        return false;
    }
    if(posicaoCliente(nome)!= -1) return false;
    InfoCartao client;
    client.nome=nome;
    client.presente=false;
    clientes.push_back(client);
    return true;
}

bool ParqueEstacionamento::entrar(const string & nome){//alinea c
    int pos= posicaoCliente(nome);
    if (vagas ==0){
        return false;
    }
    else if(pos==-1){
        return false;
    }
    else if(clientes[pos].presente == true){
        return false;
    }

    clientes[pos].presente=true;
    vagas --;
    return true;
}

bool ParqueEstacionamento::retiraCliente(const string & nome){//alinea d
    int pos= posicaoCliente(nome);
    if(pos ==-1){
        return false;
    }
    else if(clientes[pos].presente== true){
        return false;
    }
    clientes.erase(clientes.begin() + pos);
    return true;
}

bool ParqueEstacionamento::sair(const string & nome){//alinea e
    int pos= posicaoCliente(nome);
    if(clientes[pos].presente==false || pos==-1){
        return false;
    }
    clientes[pos].presente=false;
    vagas ++;
    return true;
}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const{//alinea f
    return (lotacao-vagas);
}
unsigned int ParqueEstacionamento::getNumClientesAtuais() const{//alinea f
    return clientes.size();
}
