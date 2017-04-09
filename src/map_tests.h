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

/**
 * @brief Prints a path (with a start and end point) in the graphviewer window.
 * @param data the graph being displayed
 * @param gv the graphviewer instance being used
 * @param caminho the path to be printed
 */
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


/**
 * @brief Prints the bus and metro lines existent in the selected path.
 * @param data the graph being displayed
 * @param gv the graphviewer instance being used
 * @param caminho the path where the bus and metro lines are
 * @param linhas_geradas the bus and metro lines that exist in the map
 */
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
 * @brief Runs the Floyd-Warshall algorithm from one to all nodes and find a certain amount of paths.
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

		printPathColored(data, gv, path);

		i++;
	}
}

/**
 * @brief Tests algorithm execution times (called when the main function receives "comp" as the first parameter)
 * @param data the graph being used
 * @param gv the graphviewer instance being used
 */
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
