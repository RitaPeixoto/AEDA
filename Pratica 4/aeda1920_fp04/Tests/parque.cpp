#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>

using namespace std;


bool InfoCartao::operator<(const  InfoCartao &ic1)const{
    if(frequencia > ic1.frequencia)
        return true;
    else if(frequencia <ic1.frequencia)
        return false;
    else
        return (nome<ic1.nome);
}
ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot;
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }

unsigned int ParqueEstacionamento::getNumLugares() const { return lotacao; }

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const { return lotacao-vagas; }



int ParqueEstacionamento::posicaoCliente(const string &nome) const
{
    /*InfoCartao inf1;
    inf1.nome=nome;
    int p= sequentialSearch(v:clientes, inf1);
    return p;*/
    for (unsigned int i = 0; i < clientes.size(); i++)
        if (clientes[i].nome == nome)
            return i;
    return -1;
}


int ParqueEstacionamento::getFrequencia(const string &nome) const
{
 int posicao= posicaoCliente(nome);
 if(posicao==-1){
     throw ClienteNaoExistente(nome);
 }

    return clientes[posicao].frequencia;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
 	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
    info.presente = false;
    info.frequencia=0;
	clientes.push_back(info);
	numClientes++;
	return true;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( it->nome == nome ) {
			if ( it->presente == false ) {
				clientes.erase(it);
				numClientes--;
				return true;
			}
			else return false;
		}
	return false;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == true ) return false;
	clientes[pos].presente = true;
	clientes[pos].frequencia++;
	vagas--;
	return true;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == false ) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}

		

void ParqueEstacionamento::ordenaClientesPorFrequencia()
{
    //insertionSort(clientes);
        for (unsigned int p = 1; p < clientes.size(); p++)
        {
            InfoCartao tmp = clientes[p];
            int j;
            for (j = p; j > 0 && tmp < clientes[j-1]; j--)
                clientes[j] = clientes[j-1];
            clientes[j] = tmp;
        }
}
bool compNome(const InfoCartao &c1, const InfoCartao &c2){//funçao de ordenaçao
    return c1.nome < c2.nome;
}

void ParqueEstacionamento::ordenaClientesPorNome()//ordenar por nome
{
    sort(clientes.begin(), clientes.end(), compNome);
}


vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2)
{
    vector<string> nomes;
    insertionSort(clientes);
    for(unsigned int i=0; i<clientes.size();i++){
        if(clientes[i].frequencia >=n1 && clientes[i].frequencia<=n2){
            nomes.push_back(clientes[i].nome);
        }
    }
    return nomes;
}


ostream & operator<<(ostream & os, const ParqueEstacionamento & pe)
{
    os<< "----------------Parque de Estacionamento---------------";
    for(unsigned int i=0; i<pe.numClientes; i++){
        os<< "Nome: "<< pe.clientes[i].nome<< "Presente:";
        if(pe.clientes[i].presente)
            os<< "Sim ";
        else
            os<< "Nao ";
        os<< "Numero de vezes que frequentou o parque: "<< pe.clientes[i].frequencia<<endl;

    }
    return os;
}



InfoCartao ParqueEstacionamento::getClienteAtPos(vector<InfoCartao>::size_type p) const {
    if(p<0 || p> numClientes-1){
        throw PosicaoNaoExistente(p);
    }
    return clientes[p];
}

