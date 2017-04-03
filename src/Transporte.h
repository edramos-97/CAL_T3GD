/*
 * Transporte.h
 *
 *  Created on: 02/04/2017
 *      Author: Xavier Fontes
 */

#ifndef SRC_TRANSPORTE_H_
#define SRC_TRANSPORTE_H_

#include<string>

using namespace std;

class Transporte {
	string nome;
	double custo;
	double tempo_espera;
public:
	Transporte();
	Transporte(string nome, double custo, double tempo){
		this->nome = nome;
		this->custo = custo;
		this->tempo_espera = tempo;
	}
	virtual ~Transporte();

	double getCusto() const {
		return custo;
	}

	void setCusto(double custo) {
		this->custo = custo;
	}

	const string& getNome() const {
		return nome;
	}

	void setNome(const string& nome) {
		this->nome = nome;
	}
};

#endif /* SRC_TRANSPORTE_H_ */
