/*
 * utils.h
 *
 *  Created on: 02/04/2017
 *      Author: Xavier Fontes
 */

#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

typedef unsigned long long BigAssInteger;

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
long double haversine_km(long double lat1, long double long1, long double lat2,
		long double long2) {
	long double dlong = (long2 - long1);
	long double dlat = (lat2 - lat1);
	long double a = pow(sin(dlat / 2.0), 2)
			+ cos(lat1) * cos(lat2) * pow(sin(dlong / 2.0), 2);
	long double c = 2 * atan2(sqrt(a), sqrt(1 - a));
	long double d = 6367 * c;

	return d;
}

#endif /* SRC_UTILS_H_ */
