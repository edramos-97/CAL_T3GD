/*
 * file_reading.h
 *
 *  Created on: 03/04/2017
 *      Author: User
 */

#ifndef SRC_FILE_READING_H_
#define SRC_FILE_READING_H_

#include <fstream>
#include <string>
#include <iostream>
#include "Transporte.h"
#include "utils.h"
#include <vector>
#include "Graph.h"

/**
 * @brief Method that reads the nodes from a text file and adds them to both GraphViwer and a Graph
 * @param A the xxx_a.txt file
 * @param gv the GraphViewer being used
 * @param grafo the graph being worked on
 * @param corners Struct that contains the latitude and longitude of the map.
 * @param maxXWindow Window max X coordinate size.
 * @param maxYWindow Window max Y coordinate size.
 */
void read_nodes_degrees(const std::string& A, GraphViewer*& gv,
		Graph<NoInfo>& grafo, struct cantos corners, int maxXwindow,
		int maxYwindow) {
	ifstream inFile;
	//Ler o ficheiro A2.txt
	inFile.open(A);

	if (!inFile) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	std::string line;

	BigAssInteger idNo = 0;
	long double X = 0;
	long double Y = 0;

	while (std::getline(inFile, line)) {
		std::stringstream linestream(line);
		std::string data;

		linestream >> idNo;

		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;). LATITUDE
		linestream >> Y;
		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;). LONGITUDE
		linestream >> X;    //X and Y are in degrees

		long double x = ((X * 100000) - (corners.minLong * 100000))
				* (maxXwindow
						/ ((corners.maxLong * 100000)
								- (corners.minLong * 100000)));
		long double y =
				((Y * 100000) - (corners.minLat * 100000))
						* (maxYwindow
								/ ((corners.maxLat * 100000)
										- (corners.minLat * 100000)));

		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> X;
		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> Y;    //X and Y are in radians

		NoInfo temp(idNo % 100000000, X, Y); //x long, y lat

		gv->addNode(idNo % 100000000, x, maxYwindow - y);
		cout << "x: " << x << " y: " << y << endl;
		grafo.addVertex(temp);

	}

	inFile.close();
}

/**
 * @brief Method that reads the edges from a text file and adds them to both a GraphViwer and a Graph. Also calculates the weight of the edge wich is added to the Graph
 * @param C xxx_c.txt file
 * @param gv the GraphViewer being used
 * @param grafo the graph being worked on
 */
void read_edges(unordered_set<Aresta, hashFuncAresta, hashFuncAresta> arestas,
		const std::string& C, GraphViewer*& gv, Graph<NoInfo>& grafo) {

	ifstream inFile;
	string line;

	inFile.open(C);

	if (!inFile) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	BigAssInteger idAresta;
	BigAssInteger idNo1;
	BigAssInteger idNo2;

	BigAssInteger i = 0;
	while (std::getline(inFile, line)) {
		std::stringstream linestream(line);
		std::string data;
		linestream >> idAresta;
		Aresta temp;
		temp.idAresta = idAresta;
		unordered_set<Aresta, hashFuncAresta, hashFuncAresta>::iterator itAre =
				arestas.find(temp);

		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> idNo1;
		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> idNo2;    //X and Y are in degrees

		NoInfo origem(idNo1 % 100000000, 0, 0);  //so para efeitos de pesquisa
		Vertex<NoInfo>* source = grafo.getVertex(origem);
		NoInfo destino(idNo2 % 100000000, 0, 0);
		Vertex<NoInfo>* destiny = grafo.getVertex(destino);

		//pre processamento do grafico pelo parser ja garante informacao sem erros //i think
		if (grafo.removeEdge(origem, destino)) //conseguiu remover
				{
			grafo.addEdge(origem, destino,
					haversine_km(source->getInfo().latitude,
							source->getInfo().longitude,
							destiny->getInfo().latitude,
							destiny->getInfo().longitude) / VELOCIDADE_PE, i);
		}
		grafo.addEdge(origem, destino,
				haversine_km(source->getInfo().latitude,
						source->getInfo().longitude,
						destiny->getInfo().latitude,
						destiny->getInfo().longitude) / VELOCIDADE_PE, i);

		gv->addEdge(i, idNo1 % 100000000, idNo2 % 100000000,
				EdgeType::DIRECTED);
		gv->setVertexColor(idNo1 % 100000000, GREEN);

		if (itAre->dois_sentidos) {
			i++;
			grafo.addEdge(destino, origem,
					haversine_km(source->getInfo().getLatitude(),
							source->getInfo().getLongitude(),
							destiny->getInfo().getLatitude(),
							destiny->getInfo().getLongitude()) / VELOCIDADE_PE,
					i); //distancia entre A e B == distancia entre B e A;
			gv->addEdge(i, idNo2 % 100000000, idNo1 % 100000000,
					EdgeType::DIRECTED);
			gv->setVertexColor(idNo2 % 100000000, GREEN);
		}
		i++;

	}
	inFile.close();
}

/**
 * @brief Method to assign a name to an Edge and determine if it is one or two ways.
 * @param B xxx_b.txt file
 */
unordered_set<Aresta, hashFuncAresta, hashFuncAresta> read_edges_names(
		const std::string& B) {
	ifstream inFile;
	string line;
	unordered_set<Aresta, hashFuncAresta, hashFuncAresta> arestas;
	//unordered_set<Aresta> arestas;

	inFile.open(B);

	if (!inFile) {
		cerr << "Unable to open file B2.txt";
		exit(1);   // call system to stop
	}

	BigAssInteger idAresta = 0;
	string Rua = "";
	string dois_sent = "False";

	while (std::getline(inFile, line)) {
		std::stringstream linestream(line);
		std::string data;

		linestream >> idAresta;

		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).

		char teste;
		linestream >> teste;
		if (teste == ';') {
			Rua = "unnamed";

		} else {
			string resto;
			std::getline(linestream, resto, ';');
			Rua = teste;
			Rua = teste + resto;
		}

		linestream >> dois_sent;

		Aresta temp;
		temp.origem = NoInfo(0, 0, 0);
		temp.destino = NoInfo(0, 0, 0);
		temp.distancia = 0;
		temp.idAresta = idAresta;
		temp.rua = Rua;
		if (dois_sent == "True")
			temp.dois_sentidos = true;
		else if (dois_sent == "False")
			temp.dois_sentidos = false;

		arestas.insert(temp);

	}

	inFile.close();

	return arestas;
}

/**
 * @brief Method to assign a name to an Edge and determine if it is one or two ways.
 * @param A Nodes file to be read.
 * @param B Street name file to be read.
 * @param C Edges file to be read.
 * @param grafo graph that will be modified when reading the files.
 * @param gv graphviewer that is going to represent the graph.
 * @param corners Struct that contains the latitude and longitude of the map.
 * @param maxXWindow Window max X coordinate size.
 * @param maxYWindow Window max Y coordinate size.
 */
void abrirFicheiroXY(const std::string& A, const std::string& B,
		const std::string& C, Graph<NoInfo>& grafo, GraphViewer*& gv,
		struct cantos corners, int maxXwindow, int maxYwindow) {

	ifstream inFile;
	std::string line;

	read_nodes_degrees(A, gv, grafo, corners, maxXwindow, maxYwindow);

	unordered_set<Aresta, hashFuncAresta, hashFuncAresta> arestas =
			read_edges_names(B);

	//abrir C2.txt sao as arestas
	read_edges(arestas, C, gv, grafo);
}

/**
 * @brief Generates the bus and metro lines and adds them to a graph.
 * @param data the graph being worked on
 * @param linhas_metro the number of subway lines
 * @param linhas_autocarro the number of bus lines
 * @param comp_metro the length of subway lines
 * @param comp_autocarro the length of bus lines
 */
vector<vector<NoInfo>> gera_linhas(Graph<NoInfo>& data, unsigned int linhas_metro, unsigned int linhas_autocarro,
		unsigned int comp_metro, unsigned int comp_autocarro) {
	vector<vector<NoInfo>> linhas_geradas;

	//indices random
	unsigned int indiceSource = 0;
	unsigned int indiceDestiny = 0;
	//vertices random
	Vertex<NoInfo> * vertice_ori = NULL;
	Vertex<NoInfo> * vertice_des = NULL;
	//linha proposta
	vector<NoInfo> linha_provisoria;

	//gerar linhas de autocarro
	unsigned int numero_linhas_autocarro = 0;
	while (numero_linhas_autocarro < linhas_autocarro) {

		indiceSource = rand() % data.getVertexSet().size();
		indiceDestiny = rand() % data.getVertexSet().size();
		vertice_ori = data.getVertex(
				NoInfo(data.getVertexSet()[indiceSource]->getInfo().idNo, 0, 0,
						' '));
		vertice_des = data.getVertex(
				NoInfo(data.getVertexSet()[indiceDestiny]->getInfo().idNo, 0, 0,
						' '));

		if (vertice_ori == NULL || vertice_des == NULL
				|| vertice_ori == vertice_des)
			continue;

		linha_provisoria = data.getDijkstraPath(vertice_ori->getInfo(),
				vertice_des->getInfo());
		if (linha_provisoria.size() < comp_autocarro)
			continue;

		//cria linha autocarro equivalente à provisoria mas com layer A;
		vector<NoInfo> linha_autocarro;
		for(unsigned int i = 0; i < linha_provisoria.size(); i++)
			 linha_autocarro.push_back(NoInfo(linha_provisoria[i].idNo,linha_provisoria[i].longitude, linha_provisoria[i].latitude, 'A'));

		//guarda linha gerada
		linhas_geradas.push_back(linha_autocarro);

		unsigned int indice_paragem = 0;
		while(indice_paragem < linha_provisoria.size())
		{
			//nos intermedios
			if(indice_paragem != 0 && indice_paragem !=  (linha_provisoria.size()-1)){
				//pode entrar e sair do autocarro, no ja foi adicionado pelo anterior
				data.addEdge(linha_autocarro[indice_paragem], linha_provisoria[indice_paragem],0);
				data.addEdge(linha_provisoria[indice_paragem], linha_autocarro[indice_paragem],0);

				//adiciona o no seguinte frente
				data.addVertex(linha_autocarro[indice_paragem+1]);
				//liga caminho do autocarro com o no da frente
				data.addEdge(linha_autocarro[indice_paragem], linha_autocarro[indice_paragem+1],haversine_km(linha_autocarro[indice_paragem].latitude,
										linha_autocarro[indice_paragem].longitude,
										linha_autocarro[indice_paragem+1].latitude,
										linha_autocarro[indice_paragem+1].longitude) / VELOCIDADE_AUTOCARRO);


			}//inicial
			else if(indice_paragem == 0){
				//adiciona novo nó "sobreposto"
				data.addVertex(linha_autocarro[indice_paragem]);


				//so pode entrar no autocarro
				data.addEdge(linha_provisoria[indice_paragem], linha_autocarro[indice_paragem],0);

				//adiciona o no seguinte frente
				data.addVertex(linha_autocarro[indice_paragem+1]);
				//liga caminho do autocarro
				data.addEdge(linha_autocarro[indice_paragem], linha_autocarro[indice_paragem+1],haversine_km(linha_autocarro[indice_paragem].latitude,
						linha_autocarro[indice_paragem].longitude,
						linha_autocarro[indice_paragem+1].latitude,
						linha_autocarro[indice_paragem+1].longitude) / VELOCIDADE_AUTOCARRO);

			} //no final
			else if(indice_paragem ==  (linha_provisoria.size()-1)){
				//so pode sair
				data.addEdge(linha_autocarro[indice_paragem], linha_provisoria[indice_paragem],0);
			}
			indice_paragem++;
		}
		numero_linhas_autocarro++;
	}

	//gerar linhas de metro
	unsigned int numero_linhas_metro = 0;
	while (numero_linhas_metro < linhas_metro) {
		indiceSource = rand() % data.getVertexSet().size();
		indiceDestiny = rand() % data.getVertexSet().size();
		vertice_ori = data.getVertex(
				NoInfo(data.getVertexSet()[indiceSource]->getInfo().idNo, 0, 0,
						' '));
		vertice_des = data.getVertex(
				NoInfo(data.getVertexSet()[indiceDestiny]->getInfo().idNo, 0, 0,
						' '));

		if (vertice_ori == NULL || vertice_des == NULL
				|| vertice_ori == vertice_des)
			continue;

		linha_provisoria = data.getDijkstraPath(vertice_ori->getInfo(),
				vertice_des->getInfo());

		if (linha_provisoria.size() < comp_metro)
			continue;

		/////
		//cria linha metro equivalente à provisoria mas com layer M;
		vector<NoInfo> linha_metro;
		for(unsigned int i = 0; i < linha_provisoria.size(); i++)
			linha_metro.push_back(NoInfo(linha_provisoria[i].idNo,linha_provisoria[i].longitude, linha_provisoria[i].latitude, 'M'));

		//guarda linha gerada
		linhas_geradas.push_back(linha_metro);

		unsigned int indice_paragem = 0;
		while(indice_paragem < linha_provisoria.size())
		{
			//nos intermedios
			if(indice_paragem != 0 && indice_paragem !=  (linha_provisoria.size()-1)){
				//pode entrar e sair do metro, no ja foi adicionado pelo anterior
				data.addEdge(linha_metro[indice_paragem], linha_provisoria[indice_paragem],0);
				data.addEdge(linha_provisoria[indice_paragem], linha_metro[indice_paragem],0);

				//adiciona o no seguinte frente
				data.addVertex(linha_metro[indice_paragem+1]);
				//liga caminho do metro com o no da frente
				data.addEdge(linha_metro[indice_paragem], linha_metro[indice_paragem+1],haversine_km(linha_metro[indice_paragem].latitude,
						linha_metro[indice_paragem].longitude,
						linha_metro[indice_paragem+1].latitude,
						linha_metro[indice_paragem+1].longitude) / VELOCIDADE_METRO);


			}//inicial
			else if(indice_paragem == 0){
				//adiciona novo nó "sobreposto"
				data.addVertex(linha_metro[indice_paragem]);


				//so pode entrar no metro
				data.addEdge(linha_provisoria[indice_paragem], linha_metro[indice_paragem],0);

				//adiciona o no seguinte frente
				data.addVertex(linha_metro[indice_paragem+1]);
				//liga caminho do metro
				data.addEdge(linha_metro[indice_paragem], linha_metro[indice_paragem+1],haversine_km(linha_metro[indice_paragem].latitude,
						linha_metro[indice_paragem].longitude,
						linha_metro[indice_paragem+1].latitude,
						linha_metro[indice_paragem+1].longitude) / VELOCIDADE_AUTOCARRO);

			} //no final
			else if(indice_paragem ==  (linha_provisoria.size()-1)){
				//so pode sair
				data.addEdge(linha_metro[indice_paragem], linha_provisoria[indice_paragem],0);
			}
			indice_paragem++;
		}
		/////
		numero_linhas_metro++;
	}


	return linhas_geradas;
}

#endif /* SRC_FILE_READING_H_ */
