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

/**
 * Transportes are modes of transportation. Each transport has a name, a travel cost for the fare,
 * a wait time, and an average speed. All of these are accounted for in the graph.
 */
class Transporte {
	string nome;
	double custo;
	double tempo_espera;
	double velocidade_media;
public:
	Transporte();
	Transporte(string nome, double custo, double tempo, double velo){
		this->nome = nome;
		this->custo = custo;
		this->tempo_espera = tempo;
		this->velocidade_media = velo;
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
