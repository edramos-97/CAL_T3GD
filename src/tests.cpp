/*
 * tests.cpp
 *
 *  Created on: 02/04/2017
 *      Author: User
 */

#include "tests.h"

tests::tests() {
	// TODO Auto-generated constructor stub

}

tests::~tests() {
	// TODO Auto-generated destructor stub
}

void tests::testFloidWarshal_med(Graph<NoInfo>& data, GraphViewer*& gv) {
	//----------------------------teste floyd warshal

	NoInfo ori = data.getVertex(NoInfo(42809630, 0, 0))->getInfo();
	NoInfo des = data.getVertex(NoInfo(42809660, 0, 0))->getInfo();
	vector<NoInfo> path = data.getfloydWarshallPath(ori, des);

	for (unsigned int i = 0; i < path.size(); i++) {
		Sleep(100);
		cout << path[i] << endl;
		gv->setVertexColor(path[i].idNo, YELLOW);
	}
	//------------------------------fim teste floyd warshal
}

