/*
 * Purchase.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include "Purchase.h"

using namespace std;

Purchase::Purchase(long cli) : client (cli) {
}

long Purchase::getClient() const {
	return client;
}

list< stack<Article*> > Purchase::getBags() const {
	return bags;
}

/**
 * Create an Article associated with the client of this purchase.
 */
Article* Purchase::createArticle(long barCode, bool present, bool deliverHome) {

	Article* a=new Article(client,barCode);
	a->setDeliverHome(deliverHome);
	a->setPresent(present);
	return a;

}

/**
 * Add an Article to the bags of this purchase. A new bag is added when the last bag is full.
 */
void Purchase::putInBag(Article* article) {

	if(bags.back().size() >= BAG_SIZE){
	    stack <Article*> s;
	    s.push(article);
	    bags.push_back(s);
	}
	else{
	    bags.back().push(article);
	}

}

/**
 * Pop from the bags all articles that are presents.
 * All other articles are pushed back into the bags where they were, maintaining order.
 */
vector<Article*> Purchase::popPresents() {
	vector<Article*> presents;
	stack<Article*> aux;
    list <stack<Article*>> :: iterator l_it=bags.begin();
    for(l_it; l_it!=bags.end(); l_it++){
        while(!(*l_it).empty()){
            if((*l_it).top()->getPresent()){
                presents.push_back((*l_it).top());
                (*l_it).pop();
            }
            else{
                aux.push((*l_it).top());
                (*l_it).pop();
            }
        }
        while(!aux.empty()){
            (*l_it).push(aux.top());
            aux.pop();
        }
    }

	return presents;

}
