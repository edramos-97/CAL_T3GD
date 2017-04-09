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
#include <chrono>

#define VELOCIDADE_PE 5 //km/h
#define VELOCIDADE_AUTOCARRO 25
#define VELOCIDADE_METRO 50

#define COR_METRO "ORANGE"
#define COR_AUTOCARRO "BLUE"
#define COR_PE "GREEN"
#define COR_NO_NORMAL "RED"
#define COR_NO_INICIO "CYAN"
#define COR_NO_FIM "BLACK"

#define REP_FOR 15
#define NUM_CAMINHOS 500

static void printPathColored(Graph<NoInfo>& data, GraphViewer*& gv,
		vector<NoInfo> caminho) {

	for (unsigned int i = 0; i < caminho.size() - 1; i++) {
		gv->setVertexColor(caminho[i].idNo, COR_NO_NORMAL);
		gv->setEdgeDashed(
				data.getVertex(NoInfo(caminho[i].idNo, 0, 0, ' '))->getIdEdge(
						NoInfo(caminho[i + 1].idNo, 0, 0, ' ')), false);
		gv->setEdgeThickness(
				data.getVertex(NoInfo(caminho[i].idNo, 0, 0, ' '))->getIdEdge(
						NoInfo(caminho[i + 1].idNo, 0, 0, ' ')), 10);

		if (caminho[i].layer == 'M' && caminho[i + 1].layer == 'M') {
			gv->setEdgeColor(
					data.getVertex(NoInfo(caminho[i].idNo, 0, 0, ' '))->getIdEdge(
							NoInfo(caminho[i + 1].idNo, 0, 0, ' ')), COR_METRO);
		} else if (caminho[i].layer == 'A' && caminho[i + 1].layer == 'A') {
			gv->setEdgeColor(
					data.getVertex(NoInfo(caminho[i].idNo, 0, 0, ' '))->getIdEdge(
							NoInfo(caminho[i + 1].idNo, 0, 0, ' ')),
					COR_AUTOCARRO);
		} else if (caminho[i].layer == ' ' && caminho[i + 1].layer == ' ') {
			gv->setEdgeColor(
					data.getVertex(NoInfo(caminho[i].idNo, 0, 0, ' '))->getIdEdge(
							NoInfo(caminho[i + 1].idNo, 0, 0, ' ')), COR_PE);
		} else
			gv->setEdgeColor(
					data.getVertex(NoInfo(caminho[i].idNo, 0, 0, ' '))->getIdEdge(
							NoInfo(caminho[i + 1].idNo, 0, 0, ' ')), BLACK);

	}
	gv->setVertexSize(caminho[0].idNo, 30);
	gv->setVertexColor(caminho[0].idNo, COR_NO_INICIO);
	gv->setVertexSize(caminho[caminho.size() - 1].idNo, 30);
	gv->setVertexColor(caminho[caminho.size() - 1].idNo, COR_NO_FIM);
	gv->rearrange();
}

static void printPathColored(Graph<NoInfo>& data, GraphViewer*& gv,
		vector<NoInfo> caminho, vector<vector<NoInfo>> linhas_geradas) {

	for (unsigned int i = 0; i < caminho.size() - 1; i++) {
		gv->setVertexColor(caminho[i].idNo, COR_NO_NORMAL);
		gv->setEdgeDashed(
				data.getVertex(NoInfo(caminho[i].idNo, 0, 0, ' '))->getIdEdge(
						NoInfo(caminho[i + 1].idNo, 0, 0, ' ')), false);
		gv->setEdgeThickness(
				data.getVertex(NoInfo(caminho[i].idNo, 0, 0, ' '))->getIdEdge(
						NoInfo(caminho[i + 1].idNo, 0, 0, ' ')), 10);

		if (caminho[i].layer == 'M' && caminho[i + 1].layer == 'M') {
			gv->setEdgeColor(
					data.getVertex(NoInfo(caminho[i].idNo, 0, 0, ' '))->getIdEdge(
							NoInfo(caminho[i + 1].idNo, 0, 0, ' ')), COR_METRO);
		} else if (caminho[i].layer == 'A' && caminho[i + 1].layer == 'A') {
			gv->setEdgeColor(
					data.getVertex(NoInfo(caminho[i].idNo, 0, 0, ' '))->getIdEdge(
							NoInfo(caminho[i + 1].idNo, 0, 0, ' ')),
					COR_AUTOCARRO);
		} else if (caminho[i].layer == ' ' && caminho[i + 1].layer == ' ') {
			gv->setEdgeColor(
					data.getVertex(NoInfo(caminho[i].idNo, 0, 0, ' '))->getIdEdge(
							NoInfo(caminho[i + 1].idNo, 0, 0, ' ')), COR_PE);
		} else
			gv->setEdgeColor(
					data.getVertex(NoInfo(caminho[i].idNo, 0, 0, ' '))->getIdEdge(
							NoInfo(caminho[i + 1].idNo, 0, 0, ' ')), BLACK);
	}

	gv->setVertexSize(caminho[0].idNo, 30);
		gv->setVertexColor(caminho[0].idNo, COR_NO_INICIO);
		gv->setVertexSize(caminho[caminho.size() - 1].idNo, 30);
		gv->setVertexColor(caminho[caminho.size() - 1].idNo, COR_NO_FIM);
		gv->rearrange();
}

/**
 * @brief Run djikstra algorithm from one to all nodes.
 * @param data graph that will be run in the algorithm.
 * @param gv graph viewer that will be updated after the algorithm is run.
 */
//static void testDijkstra(Graph<NoInfo>& data, GraphViewer*& gv) {
//	Vertex<NoInfo>* origem = data.getVertex(
//			NoInfo(173452776 % 100000000, 0, 0));
//	data.dijkstraShortestPath_all(origem->getInfo());
//
//	vector<Vertex<NoInfo>*> todos = data.getVertexSet();
//
//	Vertex<NoInfo>* destino = data.getVertex(
//			NoInfo(541769885 % 100000000, 0, 0));
//	while (destino != NULL) {
//
//		gv->setVertexColor(destino->getInfo().idNo, YELLOW);
//		gv->setVertexSize(destino->getInfo().idNo, 50);
//		destino = destino->path;
//	}
//
//	gv->rearrange();
//	// --------------------------fim teste dijkstra
//}
/**
 * @brief Run Floid-Warshall algorithm from one to all nodes.
 * @param data graph that will be run in the algorithm.
 * @param gv graph viewer that will be updated after the algorithm is run.
 */
//static void testFloidWarshal_med(Graph<NoInfo>& data, GraphViewer*& gv) {
//	//----------------------------teste floyd warshal
//	NoInfo temp(42809630, 0, 0);
//	NoInfo ori = data.getVertex(temp)->getInfo();
//	NoInfo des = data.getVertex(NoInfo(42809660, 0, 0))->getInfo();
//	vector<NoInfo> path = data.getfloydWarshallPath(ori, des);
//
//	for (unsigned int i = 0; i < path.size(); i++) {
//		Sleep(100);
//		cout << path[i] << endl;
//		gv->setVertexColor(path[i].idNo, YELLOW);
//	}
//	//------------------------------fim teste floyd warshal
//}
/**
 * @brief Run Floid-Warshall algorithm from one to all nodes and find a certain amount of paths.
 * @param data graph that will be run in the algorithm.
 * @param gv graph viewer that will be updated after the algorithm is run.
 */
static void testFloidWarshal_big(Graph<NoInfo>& data, GraphViewer*& gv,
		int num) {
	//teste floyd warshal bigger
	int i = 0;

	while (i < num) {
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

		if (path.size() < 50)
			continue;

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
//		for (unsigned int i = 0; i < path.size(); i++) {
//			Sleep(100);
//			cout << path[i] << endl;
//			gv->setVertexColor(path[i].idNo, color);
//			gv->setVertexSize(path[i].idNo, 30);
//		}
		printPathColored(data, gv, path);

		i++;
	}
//-----------------------fim floydwarshal bigger

}

/**
 * @brief Run Floid-Warshall algorithm from one to all nodes with a certain map.
 */
//static void TesteOtherMap() {
//	Graph<NoInfo> data;
//	int xMaxW = 1000, yMaxW = 947;
//	GraphViewer * gv = new GraphViewer(xMaxW, yMaxW, false); //not dynamic
//	gv->setBackground("10IMG1000-947.png");
//	gv->createWindow(xMaxW, yMaxW);
//	gv->defineEdgeCurved(false);
//	gv->defineEdgeDashed(true);
//	gv->defineVertexColor("blue");
//	gv->defineVertexSize(4);
//	gv->defineEdgeColor("black");
//	struct cantos corners;
//	corners.maxLat = 40.72988;
//	corners.maxLong = -73.87300;
//	corners.minLat = 40.72638;
//	corners.minLong = -73.87790;
//	abrirFicheiroXY("10IMG1000-947A.txt", "10IMG1000-947B.txt",
//			"10IMG1000-947C.txt", data, gv, corners, xMaxW, yMaxW);
//
//	testFloidWarshal_big(data, gv,6);
//}
/**
 * @brief Run Floid-Warshall algorithm from one to all nodes with a New York map.
 */
//static void TesteNewYork() {
//
//	//CRIAR GRAFO INTERNO
//	Graph<NoInfo> data;
//	int xMaxW = 5000, yMaxW = 1910;
//	GraphViewer * gv = new GraphViewer(xMaxW, yMaxW, false); //not dynamic
//	gv->setBackground("NEWY.png");
//	gv->createWindow(xMaxW, yMaxW);
//	gv->defineEdgeCurved(false);
//	gv->defineEdgeDashed(true);
//	gv->defineVertexColor("blue");
//	gv->defineVertexSize(4);
//	gv->defineEdgeColor("black");
//	struct cantos corners;
//	corners.maxLat = 40.7127;
//	corners.maxLong = -73.9784;
//	corners.minLat = 40.7007;
//	corners.minLong = -74.0194;
//	abrirFicheiroXY("NEWYA.txt", "NEWYB.txt", "NEWYC.txt", data, gv, corners,
//			xMaxW, yMaxW);
//
//	testFloidWarshal_big(data, gv, 6);
//}
static void testExecutionTimes(Graph<NoInfo>& data, GraphViewer*& gv) {

	//teste 6 caminhos pelo dijkstra e pelo a*
	int i = 0;
	double mediaAstar = 0;
	double mediaDijkstra = 0;
	while (i < NUM_CAMINHOS) {
		int ind0 = rand() % data.getVertexSet().size();
		int ind1 = rand() % data.getVertexSet().size();
		Vertex<NoInfo> * ori = data.getVertex(
				NoInfo(data.getVertexSet()[ind0]->getInfo().idNo, 0, 0));
		Vertex<NoInfo> * des = data.getVertex(
				NoInfo(data.getVertexSet()[ind1]->getInfo().idNo, 0, 0));
		if (ori == NULL || des == NULL || ori == des)
			continue;


		vector<NoInfo> teste = data.getDijkstraPath(ori->getInfo(),
				des->getInfo());

		if (teste.size() < 2)
			continue;

		cout << "CAMINHO : " << i + 1 << endl;
		cout << "A* " << i + 1 << ":" << endl;
		vector<NoInfo> pathA;


		preparaA_star(data, des->getInfo());
		auto startA_star = std::chrono::high_resolution_clock::now();
		for (unsigned int i = 0; i < REP_FOR; i++) {
			pathA = data.getA_starPath(ori->getInfo(), des->getInfo());
		}
		auto endA_star = std::chrono::high_resolution_clock::now();
		cout
				<< (double) std::chrono::duration_cast<std::chrono::microseconds>(
						endA_star - startA_star).count() << endl;

		mediaAstar += (double) std::chrono::duration_cast<std::chrono::microseconds>(
				endA_star - startA_star).count();


		cout << "Dijkstra " << i + 1 << ":" << endl;
		auto dijkstra_start = std::chrono::high_resolution_clock::now();
		for (unsigned int i = 0; i < REP_FOR; i++) {
			vector<NoInfo> pathD = data.getDijkstraPath(ori->getInfo(),
					des->getInfo());
		}
		auto dijkstra_end = std::chrono::high_resolution_clock::now();
		cout
				<< (double) std::chrono::duration_cast<std::chrono::microseconds>(
						dijkstra_end - dijkstra_start).count() << endl;

		mediaDijkstra += (double) std::chrono::duration_cast<std::chrono::microseconds>(
				dijkstra_end - dijkstra_start).count();
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

	mediaAstar /= (NUM_CAMINHOS*REP_FOR);
	mediaDijkstra /= (NUM_CAMINHOS*REP_FOR);

	cout << "MEDIA A* : " << mediaAstar << endl;
	cout << "MEDIA DIJKSTRA : " << mediaDijkstra << endl;
 }

#endif /* SRC_MAP_TESTS_H_ */
