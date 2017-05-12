/*
 * NoInfo.h
 *
 *  Created on: 02/04/2017
 *      Author: User
 */

#ifndef SRC_NOINFO_H_
#define SRC_NOINFO_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include "Transporte.h"

using namespace std;

typedef unsigned long long BigAssInteger;

/**
 * This class deals with the information existent in the nodes.
 * Each node has a layer (base, bus and subway), geographical coordinates (longitude and latitude)
 * and an identification number.
 */
class NoInfo {
public:
	char layer;
	long double longitude;
	long double latitude;
	BigAssInteger idNo;
	string nome_paragem;
	NoInfo() {
		longitude = 0.0;
		latitude = 0.0;
		idNo = 0;
		layer = ' ';
		nome_paragem = "";
	}

	NoInfo(BigAssInteger id, long double longe, long double lat) {
		this->idNo = id;
		this->longitude = longe;
		this->latitude = lat;
		this->layer = ' ';
		this->nome_paragem = "";

	}



	NoInfo(BigAssInteger id, long double longe, long double lat, char lay) {
					this->idNo = id;
					this->longitude = longe;
					this->latitude = lat;
					this->layer = lay;
					this->nome_paragem = "";
				}

	//FIXME Substituir a invocacao acima por esta no gera_linhas!
	NoInfo(BigAssInteger id, long double longe, long double lat, char lay,string nome_paragem) {
						this->idNo = id;
						this->longitude = longe;
						this->latitude = lat;
						this->layer = lay;
						this->nome_paragem = nome_paragem;
					}

	friend ostream & operator<<(ostream & os, const NoInfo obj) {
		os << "idNo: " << obj.idNo << " long: " << obj.longitude << " lat: "
				<< obj.latitude << endl;
		return os;
	}

	friend bool operator==(const NoInfo& left, const NoInfo& right) {
		return ((left.idNo == right.idNo) && (left.layer == right.layer));
	}

	friend bool operator!=(const NoInfo& left, const NoInfo& right) {
		return ((left.idNo != right.idNo) || (left.layer != right.layer));
	}

	friend bool operator<(const NoInfo& left, const NoInfo& right) {
		return left.idNo < right.idNo;
	}

	long double getLatitude() const;
	long double getLongitude() const;
};

long double NoInfo::getLatitude() const {
	return latitude;
}

long double NoInfo::getLongitude() const {
	return longitude;
}


#endif /* SRC_NOINFO_H_ */
