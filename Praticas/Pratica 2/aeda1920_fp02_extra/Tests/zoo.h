#ifndef ZOO_H_
#define ZOO_H_

#include "animal.h"
#include <vector>


class Zoo {
	vector<Animal *> animais;
	vector<Veterinario *> veterinarios;
public:
	int numAnimais() const;
	int numVeterinarios() const;
    void adicionaAnimal(Animal *a1);
    bool animalJovem(string nomeA);
    string getInformacao() const;
    void alocaVeterinarios(istream &isV);
    bool removeVeterinario(string nomeV);
    bool operator<(Zoo &zoo2) const;
};


#endif /* ZOO_H_ */
