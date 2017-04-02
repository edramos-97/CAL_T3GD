/*
 * utils.cpp
 *
 *  Created on: 02/04/2017
 *      Author: User
 */

#include <fstream>
#include <iostream>
#include <sstream>

typedef unsigned long long BigAssInteger;

long double haversine_km(long double lat1, long double long1, long double lat2,
		long double long2);

class NoInfo {
public:
	long double longitude;
	long double latitude;
	BigAssInteger idNo;

	NoInfo() {
	}

	NoInfo(BigAssInteger id, long double longe, long double lat) :
			idNo(id), longitude(longe), latitude(lat) {
	}

	friend ostream & operator<<(ostream & os, const NoInfo obj) {
		os << "idNo: " << obj.idNo << " long: " << obj.longitude << " lat: "
				<< obj.latitude << endl;
		return os;
	}

	friend bool operator==(const NoInfo& left, const NoInfo& right) {
		return ((left.idNo == right.idNo));
	}

	friend bool operator!=(const NoInfo& left, const NoInfo& right) {
		return ((left.idNo != right.idNo));
	}

	friend bool operator<(const NoInfo& left, const NoInfo& right) {
		return left.idNo < right.idNo;
	}

};

template<>
struct vertex_greater_than<long double> {
	bool operator()(Vertex<NoInfo> * a, Vertex<NoInfo> * b) const {
		return a->getDist() > b->getDist();
	}
};

template<>  //for A*
struct vertex_greater_than_A<long double>{
	bool operator()(Vertex<NoInfo> * a, Vertex<NoInfo> * b) const {
			return ((a->getDist()+a->getDestinyDistance()) > (b->getDist()+b->getDestinyDistance()));
	}
};

template<>
struct heuristicFunc<NoInfo> {
	NoInfo destino;
	bool operator()(Vertex<NoInfo> * a, Vertex<NoInfo> * b) {
		long double distOri = haversine_km(a->getInfo().latitude,
				a->getInfo().longitude, destino.latitude, destino.longitude)
				+ a->getDist();
		long double distDest = haversine_km(b->getInfo().latitude,
				b->getInfo().longitude, destino.latitude, destino.longitude)
				+ b->getDist();
		return (distOri > distDest ? true : false);
	}
	//no longer needed
	long double operator()(Vertex<NoInfo> * a) const {
		return haversine_km(a->getInfo().latitude, a->getInfo().longitude,
				destino.latitude, destino.longitude);
	}
};

class Aresta {
public:
	BigAssInteger idAresta;
	long double distancia;
	NoInfo origem;
	NoInfo destino;
	string rua;
	bool dois_sentidos;
//		bool operator==(const Aresta &other) const {
//			return idAresta == other.idAresta;
//		}
//		size_t operator()(const Aresta &are) const {
//			return idAresta * 37 + 54;
//		}
};

struct hashFunc {
	bool operator()(const Aresta &s1, const Aresta &s2) const {
		return s1.idAresta == s2.idAresta;
	}

	int operator()(const Aresta &s1) const {
		return s1.idAresta * 37;
	}

};
