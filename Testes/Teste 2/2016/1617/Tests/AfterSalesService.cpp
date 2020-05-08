/*
 * AfterSalesService.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include <algorithm>
#include "AfterSalesService.h"

using namespace std;

int AfterSalesService::tableOrdinal = 0;

AfterSalesService::AfterSalesService(int toWrapQS) : toWrapQueueSize(toWrapQS) {
}

vector<Article*> AfterSalesService::getPresentsTable() const {
	return presentsTable;
}

queue<Article*> AfterSalesService::getToWrap() const {
	return toWrap;
}

queue<Article*> AfterSalesService::getToDeliver() const {
	return toDeliver;
}

/**
 *  Place presents on the presents table, assigning them a relative present number and a sequential number.
 *  Assumes all given presents are from the same client.
 */
void AfterSalesService::dropPresentsOnTable(vector<Article*> presents) {
	for(vector<Article*>::size_type i = 0; i<presents.size(); i++) {
		presents[i]->setPresentNumber(i+1);
		presents[i]->setArrivalNumber(++tableOrdinal);
		presentsTable.push_back(presents[i]);
	}
}

/**
 * Remove from the table all articles of a given client.
 */
vector<Article*> AfterSalesService::pickPresentsFromTable(long client) {
	vector<Article*> clientPresents;
	vector<Article*>:: iterator it=presentsTable.begin();
	for(it; it!=presentsTable.end(); it++){
	    if((*it)->getClient() ==client){
	        clientPresents.push_back(*it);
	        presentsTable.erase(it);
	        it--;
	    }
	}
	return clientPresents;
}

/**
 * Sort the first 10 articles in the presents table:
 *   (i) give priority to articles that are NOT to be delivered at home (client is waiting);
 *  (ii) if two articles have (relative) present numbers differing more than 2,
 *       the one with lower present number should have priority (clients should not wait too much);
 * (iii) else, maintain article order in the table.
 */
bool compareArticle(Article* a1, Article* a2){
    if(abs(a1->getPresentNumber()-a2->getPresentNumber())>2){
        return a1->getPresentNumber()<a2->getPresentNumber();
    }
    return false;
}


void AfterSalesService::sortArticles() {
    vector<Article*> aux={presentsTable.begin(),presentsTable.begin()+10};
    vector<Article*> deliver_home;
    for(vector<Article*>::iterator it=aux.begin(); it!=aux.end(); it++){
        if((*it)->getDeliverHome()){
            deliver_home.push_back((*it));
            aux.erase(it);
            it--;
        }
    }
    sort(aux.begin(), aux.end(),compareArticle);
    aux.insert(aux.end(),deliver_home.begin(),deliver_home.end());
    for(int i=0; i<10; i++){
        presentsTable[i]=aux[i];
    }
}

/**
 * Move the first presents in the table to the queue of presents to wrap, taking into account the size of the queue.
 */
void AfterSalesService::enqueueArticles() {

	// TODO
	int counter=0;
	if(presentsTable.size()<toWrapQueueSize-toWrap.size()){
	    int i=0;
	    while(i!=presentsTable.size()){
	        toWrap.push(presentsTable[i]);
	        i++;
	    }
	    presentsTable.erase(presentsTable.begin(),presentsTable.end());

	}
	else {
        while (toWrap.size() < toWrapQueueSize) {
            toWrap.push(presentsTable[counter]);
            counter++;
        }
        presentsTable.erase(presentsTable.begin(), presentsTable.begin() + counter);
    }

}

/**
 * Process the first present to wrap. If it is an article to deliver home, the article is placed in the toDeliver queue.
 */
Article* AfterSalesService::wrapNext() {

	// TODO
	if(toWrap.size()==0)
	    return NULL;
	if(toWrap.front()->getDeliverHome()){
	    toDeliver.push(toWrap.front());
	    toWrap.pop();
	    return NULL;
	}
	else{
	    Article* res;
	    res=toWrap.front();
	    toWrap.pop();
	    return res;
	}
}

