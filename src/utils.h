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

struct cantos {
	long double minLong;
	long double minLat;
	long double maxLong;
	long double maxLat;
};

//calculate haversine distance for linear distance // coordinates in radians
/**
 * Method to calculate the distance between two points of a spherical surface. This function applies the Haversine formula.
 * @param lat1 Latitude in radians of the first point.
 * @param long1 Longitude in radians of the first point.
 * @param lat2 Latitude in radians of the second point.
 * @param long2 Longitude in radians of the second point.
 */
static long double haversine_km(long double lat1, long double long1, long double lat2,	long double long2) {
	long double dlong = (long2 - long1);
	long double dlat = (lat2 - lat1);
	long double a = pow(sin(dlat / 2.0), 2)
			+ cos(lat1) * cos(lat2) * pow(sin(dlong / 2.0), 2);
	long double c = 2 * atan2(sqrt(a), sqrt(1 - a));
	long double d = 6367 * c;

	return d;
}

static void preparaA_star(Graph<NoInfo> &data, const NoInfo& destino) {

	for (unsigned int i = 0; i < data.getVertexSet().size(); i++) {
		data.getVertexSet()[i]->setDestiny(
				haversine_km(data.getVertexSet()[i]->getInfo().latitude,
						data.getVertexSet()[i]->getInfo().longitude,
						destino.longitude, destino.longitude));
	}
}

static void paintPath(GraphViewer *gv, vector<NoInfo> vect, string COLOR) {
	for (unsigned int i = 0; i < vect.size(); i++) {
		cout << vect[i] << endl;
		gv->setVertexColor(vect[i].idNo, COLOR);
		//gv->setVertexSize(vect[i].idNo, 20);
	}
}



#endif /* SRC_UTILS_H_ */
