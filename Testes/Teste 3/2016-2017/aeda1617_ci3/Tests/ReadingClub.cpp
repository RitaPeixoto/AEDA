/*
 * ReadingClub.cpp
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#include "ReadingClub.h"

ReadingClub::ReadingClub(): catalogItems(BookCatalogItem("", "", 0)) {
	//do nothing!
}

ReadingClub::ReadingClub(vector<Book*> books): catalogItems(BookCatalogItem("", "", 0)) {
	this->books = books;
}

void ReadingClub::addBook(Book* book) {
	this->books.push_back(book);
}

void ReadingClub::addBooks(vector<Book*> books) {
	this->books = books;
}

vector<Book*> ReadingClub::getBooks() const{
	return this->books;
}

BookCatalogItem ReadingClub::getCatalogItem(string title, string author) const{
	BookCatalogItem itemNotFound("", "", 0);
	BSTItrIn<BookCatalogItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getTitle() == title && it.retrieve().getAuthor() == author) {
			BookCatalogItem bci(it.retrieve().getTitle(), it.retrieve().getAuthor(), 0);
			bci.setItems(it.retrieve().getItems());
			return bci;
		}
		it.advance();
	}
	return itemNotFound;
}

void ReadingClub::addCatalogItem(Book* book) {
	BookCatalogItem itemNotFound("", "", 0);
	BookCatalogItem bci(book->getTitle(), book->getAuthor(), book->getYear());
	BookCatalogItem bciX = catalogItems.find(bci);
	if(bciX == itemNotFound) {
		bci.addItems(book);
		this->catalogItems.insert(bci);
	}
	else {
		this->catalogItems.remove(bciX);
		bciX.addItems(book);
		this->catalogItems.insert(bciX);
	}
	books.push_back(book);
}

BST<BookCatalogItem> ReadingClub::getCatalogItems() const {
	return this->catalogItems;
}

vector<UserRecord> ReadingClub::getUserRecords() const {
	vector<UserRecord> records;
	HashTabUserRecord::const_iterator it1 = this->userRecords.begin();
	HashTabUserRecord::const_iterator it2 = this->userRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void ReadingClub::setUserRecords(vector<UserRecord>& urs) {
	for(int i = 0; i < urs.size(); i++) userRecords.insert(urs[i]);
}

priority_queue<User> ReadingClub::getBestReaderCandidates() const {
	return readerCandidates;
}
void ReadingClub::setBestReaderCandidates(priority_queue<User>& candidates) {
	readerCandidates = candidates;
}



//
// TODO: Part I   - BST
//

void ReadingClub::generateCatalog() {
	//TODO:
	vector<Book*> temp = books;
	vector<Book*>::iterator it= temp.begin();
	for (it ; it!= temp.end();it++){
	    addCatalogItem(*it);
	}
    books = temp;
}

vector<Book*> ReadingClub::getAvailableItems(Book* book) const {
	vector<Book*> temp;
    BookCatalogItem b = getCatalogItem(book->getTitle(),book->getAuthor());
    vector<Book*> books=b.getItems();
    for(vector<Book*>::const_iterator it= books.begin(); it!= books.end();it ++){
        if((*it)->getReader() == nullptr){
            temp.push_back(*it);
        }
    }
	return temp;
}

bool ReadingClub::borrowBookFromCatalog(Book* book, User* reader) {
	//TODO:
    vector<Book*> books = getAvailableItems(book);
    if(books.size()==0)
        return false;
    reader->addReading(books.at(0)->getTitle(),books.at(0)->getAuthor());
    book->setReader(reader);
    return true;
}


//
// TODO: Part II  - Hash Table
//

void ReadingClub::addUserRecord(User* user) {
	//TODO:
	userRecords.insert(user);
}

void ReadingClub::changeUserEMail(User* user, string newEMail) {
	//TODO:
	user->setEMail(newEMail);
}


//
// TODO: Part III - Priority Queue
//

void ReadingClub::addBestReaderCandidates(const vector<User>& candidates, int min) {
	//TODO:
    vector<User>::const_iterator it=candidates.begin();
    for(it; it!= candidates.end();it++){
        if(!((*it).getReading().first.empty())){
            if(((*it).getReadings().size() +1)>=min)
                readerCandidates.push(*it);
        }

    }
}

int ReadingClub::awardReaderChampion(User& champion) {
	//TODO:
	if(readerCandidates.empty())
	    return 0;
    priority_queue<User> aux= readerCandidates;
	User u1= aux.top();
	aux.pop();
	User u2 = aux.top();
	int u_2 = u2.getReading().first.empty(), u_1=u1.getReading().first.empty();

	if ((u1.getReadings().size()+u_1)>(u2.getReadings().size()+u_2)){
        champion =u1;
        return readerCandidates.size();
	}
    else{
        return 0;
    }
}
























