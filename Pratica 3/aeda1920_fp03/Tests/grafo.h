#include <iostream>
#include <vector>

using namespace std;

/**
 * Versao da classe generica Grafo usando a classe vector
 */

template <class N, class A> class Aresta;

template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N,A> > arestas;
	No(N inf) {
		info = inf;
	}
};

template <class N, class A>
class Aresta {
public:
	A valor;
	No<N,A> *destino;
	Aresta(No<N,A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};

template <class N, class A> 
class Grafo { 
	vector< No<N,A> *> nos;
  public: 
    Grafo();
    ~Grafo(); 
    Grafo & inserirNo(const N &dados);
    Grafo & inserirAresta(const N &inicio, const N &fim, const A &val);
    Grafo & eliminarAresta(const N &inicio, const N &fim);
    A & valorAresta(const N &inicio, const N &fim);
    int numArestas(void) const;
    int numNos(void) const;
    void imprimir(std::ostream &os) const; 
};

template <class N, class A> 
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g);


// excecao NoRepetido
template <class N>
class NoRepetido
{
public:
   N info;
   NoRepetido(N inf) { info=inf; }
};
template <class N> 
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no)
{ out << "No repetido: " << no.info; return out; }


// excecao NoInexistente
template <class N>
class NoInexistente {
public:
	N info;
	NoInexistente(N inf) {
		info = inf;
	}
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni)
{ out << "No inexistente: " << ni.info; return out; }

//ALINEA C
//exceçao ArestaRepetida
template <class N>
class ArestaRepetida{
public:
    N info_1,info_2;
    ArestaRepetida(N inf_1, N inf_2) {
        info_1 = inf_1;
        info_2=inf_2;
    }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaRepetida<N> &ar)
{ out << "Aresta repetida: " << ar.info_1<< " , "<<ar.info_2; return out; }

//ALINEA D
//exceçao ArestaInexistente
template<class N>
class ArestaInexistente{
public:
    N info_1,info_2;
    ArestaInexistente(N inf_1,N inf_2){
        info_1=inf_1;
        info_2=inf_2;
    }
};
template<class N>
std::ostream & operator<<(std::ostream &out, const ArestaInexistente<N> &ai)
{ out << "Aresta inexistente: " << ai.info_1<< " , "<<ai.info_2; return out; }




//alinea a
template <class N, class A>
Grafo<N,A>::Grafo(){

}

template <class N, class A>
Grafo<N,A>::~Grafo(){
    for(int i=0; i<nos.size();i++){
        delete nos[i];
    }
}
template <class N, class A>
int Grafo<N,A>::numNos(void) const{
    return nos.size();
}
template <class N, class A>
int Grafo<N,A>::numArestas(void) const{
    int n_arestas=0;
    for(int i=0; i<numNos();i++){
        n_arestas+=nos[i]->arestas.size();
    }
    return n_arestas;
}

//ALINEA B
template <class N, class A>
Grafo<N,A> & Grafo<N,A> :: inserirNo(const N &dados){
        for(int i=0; i<nos.size();i++){
            if(nos[i]->info == dados){
                throw(NoRepetido<N>(dados));
            }
        }
        No<N,A> *no1= new No<N,A> (dados);
        nos.push_back(no1);
        return *this;
}




//ALINEA C
template <class N, class A>
Grafo<N,A> & Grafo<N,A>::inserirAresta(const N &inicio, const N &fim, const A &val){
    //Percorrer o vetor de nos ate encontrar a No em que info=inicio
    typename vector< No<N,A>*>::const_iterator it;
    typename vector< Aresta<N,A>>:: iterator it_a;
    bool found_begin=false, found_end= false;

    No<N,A> *begin_pointer=NULL, *end_pointer=NULL;

    for(it=nos.begin(); it!=nos.end();it++) {
        //procura no vetor de nos a no em que info==inicio
        if ((*it)->info == inicio) {
            found_begin = true;
            begin_pointer = *it;
            //verifica se vetor de arestas ja tem uma aresta com aquele destino
            for (it_a = (*it)->arestas.begin(); it_a != (*it)->arestas.end(); it_a++) {
                //se for repetida e lançada a exceçao
                if (it_a->destino->info == fim) {
                    throw (ArestaRepetida<N>(inicio,fim));
                }
            }
            if (found_end) { break; }
        } else if ((*it)->info == fim) {
            found_end = true;
            end_pointer = *it;
            if (found_begin) { break; }
        }
    }
        //se nao encontrar um dos nos, lança a exceçao do tipo NoInexistente
        if(!found_begin) throw NoInexistente<N>(inicio);
        if(!found_end) throw NoInexistente<N>(fim);

        //criar uma nova aresta
        Aresta<N,A> aresta1(end_pointer,val);
        //insere o objeto no vetor de arestas do no
        begin_pointer->arestas.push_back(aresta1);
    return *this;

}


//ALINEA D
template <class N, class A>
A & Grafo<N,A>::valorAresta(const N &inicio, const N &fim){
    typename vector<No<N,A>*>::const_iterator it ;
    typename vector<Aresta<N,A>>::iterator it_a;

    for(it=nos.begin(); it!=nos.end();it++){
        if ((*it)->info == inicio) {
            for (it_a = (*it)->arestas.begin(); it_a != (*it)->arestas.end(); it_a++) {
                if (it_a->destino->info == fim) {
                    return it_a->valor;

                }
            }
            throw ArestaInexistente<N>(inicio, fim);
        }

    }
    throw NoInexistente<N>(inicio);
}



//ALINEA E
template <class N, class A>
Grafo<N,A> & Grafo<N,A>:: eliminarAresta(const N &inicio, const N &fim){
    typename vector<No<N,A>*>::const_iterator it ;
    typename vector<Aresta<N,A>>::iterator it_a;

    for(it=nos.begin(); it!=nos.end();it++){
        if ((*it)->info == inicio) {
            for (it_a = (*it)->arestas.begin(); it_a != (*it)->arestas.end(); it_a++) {
                if (it_a->destino->info == fim) {
                    (*it)->arestas.erase(it_a);
                    return *this;
                }
            }
            throw ArestaInexistente<N>(inicio, fim);
        }

    }
    throw NoInexistente<N>(inicio);
}


//ALINEA F
template <class N, class A>
void Grafo<N,A>::imprimir(std::ostream &os) const{
    No<N,A> *begin=NULL;
    No<N,A> *end=NULL;
    typename vector<No<N,A>*>::const_iterator it;
    typename vector<Aresta<N,A>>::iterator it_a;


    for (it=nos.begin(); it!=nos.end(); it++){
        os<<"( " <<(*it)->info;
        it_a=(*it)->arestas.begin();
        if((*it)->arestas.size()>0){
            for(it_a=(*it)->arestas.begin(); it_a!= (*it)->arestas.end();it_a++){
                os<< "[ "<<(*it_a).destino->info<<" "<<(*it_a).valor<<"] ";
            }
        }
        os<<") ";
    }

}

//ALINEA G

template<class N, class A>
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g){
    g.imprimir(out);
    return out;
}