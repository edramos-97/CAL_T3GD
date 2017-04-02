/*
 * aresta.h
 *
 *  Created on: 02/04/2017
 *      Author: User
 */

#ifndef SRC_ARESTA_H_
#define SRC_ARESTA_H_

#include "NoInfo.h"

class Aresta {
public:
	BigAssInteger idAresta;
	long double distancia;
	NoInfo origem;
	NoInfo destino;
	string rua;
	bool dois_sentidos;
};

struct hashFuncAresta {
	bool operator()(const Aresta &s1, const Aresta &s2) const {
		return s1.idAresta == s2.idAresta;
	}

	int operator()(const Aresta &s1) const {
		return s1.idAresta * 37;
	}
};


#endif /* SRC_ARESTA_H_ */
