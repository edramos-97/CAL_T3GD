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

/**
 * Method that reads the nodes from a text file and adds them to both a GraphViwer a a Graph
 * @param A
 * @param gv
 * @param grafo
 * @param nos_todos
 */
static void read_node_radians(const std::string& A, GraphViewer*& gv,
		Graph<NoInfo>& grafo, map<NoInfo, bool> nos_todos) {
	ifstream inFile;
	string line;

	inFile.open(A);

	if (!inFile) {
		cerr << "Unable to open file A2.txt";
		exit(1);   // call system to stop
	}

	BigAssInteger idNo = 0;
	long double X = 0;
	long double Y = 0;

	while (std::getline(inFile, line)) {
		std::stringstream linestream(line);
		std::string data;

		linestream >> idNo;

		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> X;
		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> Y;    //X and Y are in degrees

		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> X;
		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> Y;    //X and Y are in radians
		//cout << "idNo: " << idNo << " long: " << X << " lat: " << Y << endl;
		NoInfo temp(idNo, X, Y);
		pair<NoInfo, bool> par(temp, false);
		nos_todos.insert(par);
	}

	inFile.close();
}

/**
 * Method that reads the nodes from a text file and adds them to both a GraphViwer a a Graph
 * @param A
 * @param gv
 * @param grafo
 * @param corners
 * @param maxXwindow
 * @param maxYwindow
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

		/*cout << X << endl;
		 cout << Y << endl;
		 cout << corners.minLong << endl;
		 cout << corners.minLat << endl;
		 cout << corners.maxLong << endl;
		 cout << corners.maxLat << endl;*/

		long double x = ((X * 100000) - (corners.minLong * 100000))
				* (maxXwindow
						/ ((corners.maxLong * 100000)
								- (corners.minLong * 100000)));
		long double y =
				((Y * 100000) - (corners.minLat * 100000))
						* (maxYwindow
								/ ((corners.maxLat * 100000)
										- (corners.minLat * 100000)));

		/*cout << X << endl;
		 cout << Y << endl;
		 cout << corners.minLong << endl;
		 cout << corners.minLat << endl;
		 cout << corners.maxLong << endl;
		 cout << corners.maxLat << endl;*/

		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> X;
		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> Y;    //X and Y are in radians

		//cout << "idNo: " << idNo << " long: " << X << " lat: " << Y << endl;

		NoInfo temp(idNo % 100000000, X, Y); //x long, y lat

		gv->addNode(idNo % 100000000, x, maxYwindow - y);
		cout << "x: " << x << " y: " << y << endl;
		grafo.addVertex(temp);

	}

	inFile.close();
}

/**
 * Method that reads the edges from a text file and adds them to both a GraphViwer and a Graph. Also calculates the weight of the edge wich is added to the Graph
 * @param C
 * @param gv
 * @param grafo
 */
void read_edges(
	unordered_set<Aresta, hashFuncAresta, hashFuncAresta> arestas,
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
	//	bool novo = true;
	//	double weigth = 0;
	//
	//	int anterior;
	while (std::getline(inFile, line)) {
		std::stringstream linestream(line);
		std::string data;
		linestream >> idAresta;
		Aresta temp;
		temp.idAresta = idAresta;
		unordered_set<Aresta, hashFuncAresta, hashFuncAresta>::iterator itAre =
				arestas.find(temp);
		//		if(novo){
		//						anterior = idAresta;
		//						novo = false;
		//					}

		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> idNo1;
		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> idNo2;    //X and Y are in degrees

		NoInfo origem(idNo1 % 100000000, 0, 0);  //so para efeitos de pesquisa
		Vertex<NoInfo>* source = grafo.getVertex(origem);
		NoInfo destino(idNo2 % 100000000, 0, 0);
		Vertex<NoInfo>* destiny = grafo.getVertex(destino);

		//pre processamento do grafico pelo parser ja garante informacao sem erros //i think
		//if(source != NULL && destiny != NULL){

		if (grafo.removeEdge(origem, destino)) //conseguiu remover
				{
			grafo.addEdge(origem, destino,
					haversine_km(source->getInfo().latitude,
							source->getInfo().longitude,
							destiny->getInfo().latitude,
							destiny->getInfo().longitude),i);
		}
		grafo.addEdge(origem, destino,
				haversine_km(source->getInfo().latitude,
						source->getInfo().longitude,
						destiny->getInfo().latitude,
						destiny->getInfo().longitude),i);

		gv->addEdge(i, idNo1 % 100000000, idNo2 % 100000000,
				EdgeType::DIRECTED);
		gv->setVertexColor(idNo1 % 100000000, GREEN);

		if (itAre->dois_sentidos) {
			i++;
			grafo.addEdge(destino, origem,
					haversine_km(source->getInfo().getLatitude(),
							source->getInfo().getLongitude(),
							destiny->getInfo().getLatitude(),
							destiny->getInfo().getLongitude()),i); //distancia entre A e B == distancia entre B e A;
			gv->addEdge(i, idNo2 % 100000000, idNo1 % 100000000,
					EdgeType::DIRECTED);
			gv->setVertexColor(idNo2 % 100000000, GREEN);
		}
		i++;

		//}

	}
	//gv->rearrange();
	inFile.close();
}

/**
 * Method to assign a name to an Edge and determine if it is one or two ways.
 * @param B
 * @param gv
 * @param grafo
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

void abrirFicheiroXY(const std::string& A, const std::string& B,
		const std::string& C, Graph<NoInfo>& grafo, GraphViewer*& gv,
		struct cantos corners, int maxXwindow, int maxYwindow) {

	ifstream inFile;
	std::string line;
	//Ler o ficheiro A2.txt
	/*inFile.open(A);

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

	 std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
	 linestream >> Y;
	 std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
	 linestream >> X;    //X and Y are in degrees

	 //		cout << X << endl;
	 //		cout << Y << endl;
	 //		cout << corners.minLong << endl;
	 //		cout << corners.minLat << endl;
	 //		cout << corners.maxLong << endl;
	 //		cout << corners.maxLat << endl;
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
	 //cout << "idNo: " << idNo << " long: " << X << " lat: " << Y << endl;
	 NoInfo temp(idNo % 100000000, X, Y); //x long, y lat

	 gv->addNode(idNo % 100000000, x, maxYwindow - y);
	 cout << "x: " << x << " y: " << y << endl;
	 grafo.addVertex(temp);

	 }

	 inFile.close();*/

	read_nodes_degrees(A, gv, grafo, corners, maxXwindow, maxYwindow);

	unordered_set<Aresta, hashFuncAresta, hashFuncAresta> arestas =
			read_edges_names(B);

	//abrir C2.txt sao as arestas
	read_edges(arestas, C, gv, grafo);
}




#endif /* SRC_FILE_READING_H_ */
