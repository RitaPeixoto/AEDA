/*
 * Postman.h
 */

#ifndef SRC_POSTMAN_H_
#define SRC_POSTMAN_H_

#include "Mail.h"
#include <string>
#include <vector>
#include <iostream>

class Postman {
	unsigned int id;
	string name;
	vector<Mail *> myMail;
public:
	Postman();
	Postman(string name);
	void setName(string nm);
	void addMail(Mail *m);
	void addMail(vector<Mail *> mails);
	string getName() const;
	vector<Mail *> getMail() const;
	unsigned int getID() const;
	bool operator<(const Postman &p);
};

//alinea a
template <class T>
bool inVector(const vector<T> &v1, const T &elem) {
    for (auto &x: v1) {
        if (x == elem)
            return true;
    }
    return false;
}

template <class T>
unsigned int numberDifferent (const vector<T> & v1) {
    if (v1.size() == 0)
        return 0;
    vector<T> temp;
    for (auto &x: v1) {
        if (!inVector(temp, x))
            temp.push_back(x);
    }
    return temp.size();
}

#endif /* SRC_POSTMAN_H_ */
