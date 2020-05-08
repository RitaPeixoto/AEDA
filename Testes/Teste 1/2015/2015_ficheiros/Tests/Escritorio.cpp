#include "Escritorio.h"
#include <iostream>


//Documento
Documento::Documento(int nPag, float pP, float pA):
			numPaginas(nPag), pPreto(pP), pAmarelo(pA)
{ }
Documento::~Documento() {}

int Documento::getNumPaginas() const { return numPaginas; }

float Documento::getPercentagemPreto() const { return pPreto; }

float Documento::getPercentagemAmarelo() const { return pAmarelo; }



//Impressora
Impressora::Impressora(string cod, int a): codigo(cod), ano(a)
{}
Impressora::~Impressora() {}

string Impressora::getCodigo() const
{ return codigo; }

int Impressora::getAno() const
{ return ano; }

vector<Documento> Impressora::getDocumentosImpressos() const
{ return docsImpressos; }



//ImpressoraPB
ImpressoraPB::ImpressoraPB(string cod, int a, int toner): Impressora(cod, a), numPagImprimir(toner)
{}

int ImpressoraPB::getNumPaginasImprimir() const
{ return numPagImprimir; }



//ImpressoraCores
ImpressoraCores::ImpressoraCores(string cod, int a, int toner): Impressora(cod, a),
		numPagImprimirPreto(toner), numPagImprimirAmarelo(toner)
{}

int ImpressoraCores::getNumPaginasImprimir() const {
	if (numPagImprimirPreto < numPagImprimirAmarelo) return (int)numPagImprimirPreto;
	return (int)numPagImprimirAmarelo;
}



//Funcionario
Funcionario::Funcionario(string cod): codigo(cod)
{}
Funcionario::~Funcionario() {}

void Funcionario::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

vector<Impressora *> Funcionario::getImpressoras() const
{ return impressoras; }

string Funcionario::getCodigo() const
{ return codigo; }



//Escritorio
Escritorio::Escritorio() {}
Escritorio::~Escritorio() {}

void Escritorio::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

void Escritorio::adicionaFuncionario(Funcionario f1)
{ funcionarios.push_back(f1); }

vector<Impressora *> Escritorio::getImpressoras() const
{ return impressoras; }


//alinea a
int Escritorio::numImpressorasSemResponsavel() const{
    int n_impressoras= impressoras.size();
    int n_impressoras_com_responsavel=0;
    vector<Funcionario>::const_iterator it;
    for(it=funcionarios.begin(); it!=funcionarios.end();it++){
        n_impressoras_com_responsavel+= (*it).getImpressoras().size();
    }
    return n_impressoras-n_impressoras_com_responsavel;
}
//alinea b
vector<Impressora *> Escritorio::retiraImpressoras(int ano1) {
    vector<Impressora*>::iterator it;
    vector<Impressora*> res;
    for(it=impressoras.begin(); it!=impressoras.end();it++){
        if((*it)->getAno()<ano1){
            res.push_back(*it);
            impressoras.erase(it);
            it--;
        }
    }
    return res;
}
//alinea c
bool Impressora::imprime(Documento doc1) {
}
bool ImpressoraPB::imprime(Documento doc1) {
    if(doc1.getNumPaginas()>numPagImprimir){
        return false;
    }
    else{
        numPagImprimir-=doc1.getNumPaginas();
        docsImpressos.push_back(doc1);
        return true;
    }
}
bool ImpressoraCores::imprime(Documento doc1) {
    float pagP=doc1.getNumPaginas()*doc1.getPercentagemPreto(),pagA=doc1.getNumPaginas()*doc1.getPercentagemAmarelo();
    if((pagA>numPagImprimirAmarelo) || (pagP>numPagImprimirPreto)){
        return false;
    }
    else{
        numPagImprimirAmarelo-=pagA;
        numPagImprimirPreto-=pagP;
        docsImpressos.push_back(doc1);
        return true;
    }
}
//alinea d
Impressora * Escritorio::imprimeDoc(Documento doc1) const {
    vector<Impressora *>::const_iterator it=impressoras.begin();
    Impressora* not_able=new ImpressoraPB("inexistente", 0, 0);
    for(;it!=impressoras.end();it++){
        if((*it)->imprime(doc1)){
            return *it;
        }
    }

    return not_able;
}

//alinea e
vector<Impressora *> Escritorio::tonerBaixo() const{
    vector<Impressora *> res;
    vector<Impressora *>::const_iterator it=impressoras.begin();
    for(;it!=impressoras.end();it++){
        ImpressoraPB* pb = dynamic_cast<ImpressoraPB *>(*it);
        ImpressoraCores* cores = dynamic_cast<ImpressoraCores *>(*it);

        if (pb != nullptr) {
            if (pb->getNumPaginasImprimir() < 30) {
                res.push_back(*it);
            }
        }
        else if (cores != nullptr) {
            if (cores->getNumPaginasImprimir() < 20) {
                res.push_back(*it);
            }
        }
    }
    return res;
}

//alinea f
Documento Documento::operator+(const Documento& rhs) const {
    int nPag = numPaginas + rhs.numPaginas;
    float pP = (pPreto * numPaginas + rhs.pPreto * rhs.numPaginas) / nPag;
    float pA = (pAmarelo * numPaginas + rhs.pAmarelo * rhs.numPaginas) / nPag;

    return Documento(nPag, pP, pA);
}

//alinea g
string Escritorio::operator()(string cod) const {
    for (vector<Funcionario>::const_iterator itFunc = funcionarios.begin(); itFunc != funcionarios.end(); itFunc++) {
        vector<Impressora *> impressorasFunc = itFunc->getImpressoras();
        for (vector<Impressora *>::const_iterator itImp = impressorasFunc.begin(); itImp != impressorasFunc.end(); itImp++) {
            if ((*itImp)->getCodigo() == cod) {
                return itFunc->getCodigo();
            }
        }
    }
    return "nulo";
}