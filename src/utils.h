/*
 * utils.h
 *
 *  Created on: 02/04/2017
 *      Author: Xavier Fontes
 */

#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <cmath>
#include "NoInfo.h"
#include "Graph.h"
#include "graphviewer.h"
#include "Transporte.h"

#define VELOCIDADE_PE 5 //km/h
#define VELOCIDADE_AUTOCARRO 25
#define VELOCIDADE_METRO 50

#define COR_METRO "ORANGE"
#define COR_AUTOCARRO "BLUE"
#define COR_PE "YELLOW"
#define DELTA_TAMANHO_PARAGENS 10

/*
 * This class facilitates the station naming.
 */
class par {
public:
	string nome_estacao;
	bool usado;
	par(string nome, bool usado):nome_estacao(nome),usado(usado){};
	par():nome_estacao(""),usado(false){};
};

/**
 * This struct defines the map borders using the OpenStreetMap coordinates.
 */
struct cantos {
	long double minLong;
	long double minLat;
	long double maxLong;
	long double maxLat;
};

/**
 * Declaration of means of transportation used:
 *     - Travelling by foot is free, has no wait time but is the slowest mode of transportation
 *     - Travelling by bus is cheaper than subway, but the wait time is longer and the bus runs slower
 *     - Travelling by subway is the most expensive, but has a short wait time and is the fastest
 */
vector<Transporte> todos_transportes =
		{ Transporte("Pe", 0.0, 0.0, 4),
			Transporte("Autocarro", 1.0, 0.2, 20),
			Transporte("Metro", 2.0, 0.1, 50) };

/**
 * Method to calculate the distance between two points of a spherical surface. This function applies the Haversine formula.
 * @param lat1 Latitude in radians of the first point.
 * @param long1 Longitude in radians of the first point.
 * @param lat2 Latitude in radians of the second point.
 * @param long2 Longitude in radians of the second point.
 */
static long double haversine_km(long double lat1, long double long1,
		long double lat2, long double long2) {
	long double dlong = (long2 - long1);
	long double dlat = (lat2 - lat1);
	long double a = pow(sin(dlat / 2.0), 2)
			+ cos(lat1) * cos(lat2) * pow(sin(dlong / 2.0), 2);
	long double c = 2 * atan2(sqrt(a), sqrt(1 - a));
	long double d = 6367 * c;

	return d;
}

/**
 * @brief Prepares the usage of the A* algorithm by calculating the distance from all nodes to the destination.
 * @param data the graph being worked on
 * @param destino the destination
 */
static void preparaA_star(Graph<NoInfo> &data, const NoInfo& destino) {

	for (unsigned int i = 0; i < data.getVertexSet().size(); i++) {
		data.getVertexSet()[i]->setDestiny(
				haversine_km(data.getVertexSet()[i]->getInfo().latitude,
						data.getVertexSet()[i]->getInfo().longitude,
						destino.longitude, destino.longitude)/VELOCIDADE_METRO);
	}
}

#endif /* SRC_UTILS_H_ */
