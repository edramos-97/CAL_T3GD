/*
 * map_tests..h
 *
 *  Created on: 03/04/2017
 *      Author: User
 */

#ifndef SRC_MAP_TESTS_H_
#define SRC_MAP_TESTS_H_

#include "NoInfo.h"
#include "Graph.h"
#include "graphviewer.h"
#include "file_reading.h"


static void testDijkstra(Graph<NoInfo>& data, GraphViewer*& gv) {
	Vertex<NoInfo>* origem = data.getVertex(
			NoInfo(173452776 % 100000000, 0, 0));
	data.dijkstraShortestPath_all(origem->getInfo());

	vector<Vertex<NoInfo>*> todos = data.getVertexSet();

	Vertex<NoInfo>* destino = data.getVertex(
			NoInfo(541769885 % 100000000, 0, 0));
	while (destino != NULL) {

		gv->setVertexColor(destino->getInfo().idNo, YELLOW);
		gv->setVertexSize(destino->getInfo().idNo, 50);
		destino = destino->path;
	}

	gv->rearrange();
	// --------------------------fim teste dijkstra
}

static void testFloidWarshal_med(Graph<NoInfo>& data, GraphViewer*& gv) {
	//----------------------------teste floyd warshal
	NoInfo temp(42809630, 0, 0);
	NoInfo ori = data.getVertex(temp)->getInfo();
	NoInfo des = data.getVertex(NoInfo(42809660, 0, 0))->getInfo();
	vector<NoInfo> path = data.getfloydWarshallPath(ori, des);

	for (unsigned int i = 0; i < path.size(); i++) {
		Sleep(100);
		cout << path[i] << endl;
		gv->setVertexColor(path[i].idNo, YELLOW);
	}
	//------------------------------fim teste floyd warshal
}

static void testFloidWarshal_big(Graph<NoInfo>& data, GraphViewer*& gv) {
	//teste floyd warshal bigger
	int i = 0;

	while (i < 6) {
		int ind0 = rand() % data.getVertexSet().size();
		int ind1 = rand() % data.getVertexSet().size();
		Vertex<NoInfo> * ori = data.getVertex(
				NoInfo(data.getVertexSet()[ind0]->getInfo().idNo, 0, 0));
		Vertex<NoInfo> * des = data.getVertex(
				NoInfo(data.getVertexSet()[ind1]->getInfo().idNo, 0, 0));
		if (ori == NULL || des == NULL || ori == des)
			continue;

		vector<NoInfo> path = data.getDijkstraPath(ori->getInfo(),
				des->getInfo());
		string color = "BLACK";
		switch (i) {
		case 0:
			color = YELLOW;
			break;
		case 1:
			color = ORANGE;
			break;
		case 2:
			color = RED;
			break;
		case 3:
			color = PINK;
			break;
		case 4:
			color = GRAY;
			break;
		case 5:
			color = BLACK;
			break;
		}

		cout << "novo caminho: " << i << endl;
		for (unsigned int i = 0; i < path.size(); i++) {
			//Sleep(100);
			cout << path[i] << endl;
			gv->setVertexColor(path[i].idNo, color);
		}

		i++;
	}
//-----------------------fim floydwarshal bigger

}

static void TesteOtherMap() {
	Graph<NoInfo> data;
	int xMaxW = 1000, yMaxW = 947;
	GraphViewer * gv = new GraphViewer(xMaxW, yMaxW, false); //not dynamic
	gv->setBackground("10IMG1000-947.png");
	gv->createWindow(xMaxW, yMaxW);
	gv->defineEdgeCurved(false);
	gv->defineEdgeDashed(true);
	gv->defineVertexColor("blue");
	gv->defineVertexSize(4);
	gv->defineEdgeColor("black");
	struct cantos corners;
	corners.maxLat = 40.72988;
	corners.maxLong = -73.87300;
	corners.minLat = 40.72638;
	corners.minLong = -73.87790;
	abrirFicheiroXY("10IMG1000-947A.txt", "10IMG1000-947B.txt",
			"10IMG1000-947C.txt", data, gv, corners, xMaxW, yMaxW);

	testFloidWarshal_big(data, gv);
}

static void TesteNewYork() {

	//CRIAR GRAFO INTERNO
	Graph<NoInfo> data;
	int xMaxW = 5000, yMaxW = 1910;
	GraphViewer * gv = new GraphViewer(xMaxW, yMaxW, false); //not dynamic
	gv->setBackground("NEWY.png");
	gv->createWindow(xMaxW, yMaxW);
	gv->defineEdgeCurved(false);
	gv->defineEdgeDashed(true);
	gv->defineVertexColor("blue");
	gv->defineVertexSize(4);
	gv->defineEdgeColor("black");
	struct cantos corners;
	corners.maxLat = 40.7127;
	corners.maxLong = -73.9784;
	corners.minLat = 40.7007;
	corners.minLong = -74.0194;
	abrirFicheiroXY("NEWYA.txt", "NEWYB.txt", "NEWYC.txt", data, gv, corners,
			xMaxW, yMaxW);

	testFloidWarshal_big(data, gv);
}

static void testExecutionTimes(Graph<NoInfo>& data, GraphViewer*& gv) {

	//teste 6 caminhos pelo dijkstra e pelo a*
	int i = 0;

	while (i < 6) {
		int ind0 = rand() % data.getVertexSet().size();
		int ind1 = rand() % data.getVertexSet().size();
		Vertex<NoInfo> * ori = data.getVertex(
				NoInfo(data.getVertexSet()[ind0]->getInfo().idNo, 0, 0));
		Vertex<NoInfo> * des = data.getVertex(
				NoInfo(data.getVertexSet()[ind1]->getInfo().idNo, 0, 0));
		if (ori == NULL || des == NULL || ori == des)
			continue;

		preparaA_star(data, des->getInfo());
		vector<NoInfo> teste = data.getA_starPath(ori->getInfo(),
				des->getInfo());
		if (teste.size() < 150)
			continue;

		cout << "CAMINHO : " << i + 1 << endl;

		cout << "A* " << i + 1 << ":" << endl;
		preparaA_star(data, des->getInfo());
		clock_t tStart = clock();

		vector<NoInfo> pathA = data.getA_starPath(ori->getInfo(),
				des->getInfo());
		cout << (double) (clock() - tStart) << endl;

		cout << "Dijkstra " << i + 1 << ":" << endl;
		tStart = clock();
		vector<NoInfo> pathD = data.getDijkstraPath(ori->getInfo(),
				des->getInfo());
		cout << (double) (clock() - tStart) << endl;

		string color = "BLACK";
		switch (i) {
		case 0:
			color = YELLOW;
			break;
		case 1:
			color = ORANGE;
			break;
		case 2:
			color = RED;
			break;
		case 3:
			color = PINK;
			break;
		case 4:
			color = GRAY;
			break;
		case 5:
			color = BLACK;
			break;
		}

		//so faz caminho A*
		//cout << "novo caminho: " << i << endl;
		for (unsigned int i = 0; i < pathA.size(); i++) {
			//cout << pathA[i] << endl;
			gv->setVertexColor(pathA[i].idNo, color);
			gv->setVertexSize(pathA[i].idNo, 40);
		}

		cout << "tamanho: " << pathA.size() << endl;
		i++;

	}
}


#endif /* SRC_MAP_TESTS_H_ */