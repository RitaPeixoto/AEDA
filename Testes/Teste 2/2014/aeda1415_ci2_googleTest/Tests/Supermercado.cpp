/*
 * Supermercado.cpp
 *
 * Created on: Dec 3, 2014
 *
 */

#include "Supermercado.h"

int Cliente::numeroItens() const{
    if(cestos.size()==0) return 0;

    int counter=0;
    list<Cesto>::const_iterator it=cestos.begin();
    for(it; it!=cestos.end();it++){
        counter+= (*it).getItens().size();
    }
    return counter;
}

int Cliente::valorItens()const{
    int counter=0;
    list<Cesto> :: const_iterator it=cestos.begin();
    for(it; it!=cestos.end();it++){
        stack<Item> aux= (*it).getItens();
        int size = aux.size();
        for(int i=0; i<size;i++){
            counter+= aux.top().preco;
            aux.pop();
        }
    }
    return counter;
}

int Cliente::trocarItem(Item& novoItem){
    int counter=0;
    list<Cesto> :: iterator it=cestos.begin();
    for(it; it!=cestos.end();it++){
        vector<Item> aux;
        int size =it->getItens().size();
        while(size>0){
            if((*it).getItens().top().preco >novoItem.preco   || (*it).getItens().top().produto == novoItem.produto){
                aux.push_back(novoItem);
                counter++;
                (*it).popItem();
            }
            else{
                aux.push_back((*it).getItens().top());
                (*it).popItem();
            }
            size--;
        }
        for(int i=0; i<aux.size();i++){
            it->pushItem(aux.at(aux.size()-1-i));
        }
    }
    return counter;
}

bool sortProdutos(Item i1, Item i2){
    return i1.peso<i2.peso;
}

void Cliente::organizarCestos(){
    list<Cesto>::iterator it=cestos.begin();
    for(it; it!=cestos.end(); it++){
        vector<Item> aux;
        while(!(*it).getItens().empty()){
            aux.push_back((*it).getItens().top());
            (*it).getItens().pop();
            (*it).popItem();
        }
        sort(aux.begin(), aux.end(), sortProdutos);
        int s= aux.size();
        for(int i=0; i<s;i++){
            (*it).pushItem(aux.at(aux.size()-1-i));
        }
    }
}

vector<string> Cliente::contarItensPorTipo(){
    vector <string> aux={};
    vector<string> result={};
    list<Cesto> :: iterator it =cestos.begin();

    for(Cesto ces: cestos){
        stack<Item> itens= ces.getItens();
        int size=itens.size();
        while(size!=0){
            aux.push_back(itens.top().tipo);
            itens.pop();
        }
    }
    sort(aux.begin(),aux.end());
    for(auto it=aux.begin();it!=aux.end();it++){
        string add="";
        string compare=*it;
        int count=1;
        for(auto it1=aux.begin()+1; it1!=aux.end();it1++){
            if(compare == *it1) {
                count++;
                it1= --aux.erase(it1);
            }
            else
                break;
        }
        add = *it + " " + to_string(count);
        result.push_back(add);
        it = --aux.erase(it);
    }
    return result;
}

int Cesto::novoItem (const Item& umItem){
    stack<Item> aux=itens;
    int w=0, v=0;
    while(!aux.empty()){
        w+= aux.top().peso;
        v+= aux.top().volume;
        aux.pop();
    }

    if(umItem.peso +w<=max_peso){
        if(umItem.volume +v<= max_volume){
            pushItem(umItem);
            return itens.size();
        }
    }
    return 0;

}


int Cliente::novoItem(const Item &umItem) {
    bool done =false;
    list<Cesto> :: iterator it=cestos.begin();
    for(it; it!= cestos.end(); it++){
        if((*it).novoItem(umItem)!=0){
            done=true;
            return cestos.size();
        }
    }
    if(!done){
        Cesto c;
        c.pushItem(umItem);
        cestos.push_back(c);
        return cestos.size();
    }
    return 0;
}

int Supermercado::novoCliente(Cliente &umCliente){
    if(umCliente.getIdade()<65){
        filaNormal.push(umCliente);
    }
    else{
        if(filaNormal.size()< filaPrioritaria.size()){
            filaNormal.push(umCliente);
        }
        else{
            filaPrioritaria.push(umCliente);
        }
    }
    return filaNormal.size() + filaPrioritaria.size();
}

Cliente Supermercado:: sairDaFila(string umNomeDeCliente) {
    vector<Cliente> aux;
    Cliente result;
    bool found = false;
    while (!filaNormal.empty()){
        if (umNomeDeCliente == filaNormal.front().getNome()){
            result = filaNormal.front();
            filaNormal.pop();
            found = true;
        }
        else {
            aux.push_back(filaNormal.front());
            filaNormal.pop();
        }
    }
    if (!aux.empty()){
        for (Cliente cli: aux){
            filaNormal.push(cli);
        }
    }
    if (found)
        return result;
    aux = {};
    while (!filaPrioritaria.empty()){
        if (umNomeDeCliente == filaPrioritaria.front().getNome()){
            result = filaPrioritaria.front();
            filaPrioritaria.pop();
            found = true;
        }
        else {
            aux.push_back(filaPrioritaria.front());
            filaPrioritaria.pop();
        }
    }
    if (!aux.empty()){
        for (Cliente cli: aux){
            filaPrioritaria.push(cli);
        }
    }
    if (found)
        return result;
    throw ClienteInexistente(umNomeDeCliente);
}