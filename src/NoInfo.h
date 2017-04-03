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

using namespace std;

typedef unsigned long long BigAssInteger;

class NoInfo {
public:
	long double longitude;
	long double latitude;
	BigAssInteger idNo;

	NoInfo() {
		longitude = 0.0;
		latitude = 0.0;
		idNo = 0;
	}

	NoInfo(BigAssInteger id, long double longe, long double lat) {
		this->idNo = id;
		this->longitude = longe;
		this->latitude = lat;

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
