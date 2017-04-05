#include <cstdio>
//#include "graphviewer.h"
//#include <fstream>
//#include <iostream>
//#include <sstream>
#include <cmath>
//#include "Graph.h"
#include <string>
#include <map>
#include <cstring>
#include <unordered_set>
#include <utility>
//#include <tr1/unordered_set>
#include <time.h>
#include "utils.h"
#include "aresta.h"
//#include "NoInfo.h"
#include "map_tests.h"
#include "file_reading.h"

//class NoInfo {
//public:
//	long double longitude;
//	long double latitude;
//	BigAssInteger idNo;
//
//	NoInfo() {
//		longitude = 0.0;
//		latitude = 0.0;
//		idNo = 0;
//	}
//
//	NoInfo(BigAssInteger id, long double longe, long double lat) {
//		this->idNo = id;
//		this->longitude = longe;
//		this->latitude = lat;
//
//	}
//
//	friend ostream & operator<<(ostream & os, const NoInfo obj) {
//		os << "idNo: " << obj.idNo << " long: " << obj.longitude << " lat: "
//				<< obj.latitude << endl;
//		return os;
//	}
//
//	friend bool operator==(const NoInfo& left, const NoInfo& right) {
//		return ((left.idNo == right.idNo));
//	}
//
//	friend bool operator!=(const NoInfo& left, const NoInfo& right) {
//		return ((left.idNo != right.idNo));
//	}
//
//	friend bool operator<(const NoInfo& left, const NoInfo& right) {
//		return left.idNo < right.idNo;
//	}
//
//};

template<>
struct vertex_greater_than<long double> {
	bool operator()(Vertex<NoInfo> * a, Vertex<NoInfo> * b) const {
		return a->getDist() > b->getDist();
	}
};

template<>  //for A*
struct vertex_greater_than_A<long double> {
	bool operator()(Vertex<NoInfo> * a, Vertex<NoInfo> * b) const {
		return ((a->getDist() + a->getDestinyDistance())
				> (b->getDist() + b->getDestinyDistance()));
	}
};

template<>
struct heuristicFunc<NoInfo> {
	NoInfo destino;
	bool operator()(Vertex<NoInfo> * a, Vertex<NoInfo> * b) {
		long double distOri = haversine_km(a->getInfo().latitude,
				a->getInfo().longitude, destino.latitude, destino.longitude)
				+ a->getDist();
		long double distDest = haversine_km(b->getInfo().latitude,
				b->getInfo().longitude, destino.latitude, destino.longitude)
				+ b->getDist();
		return (distOri > distDest ? true : false);
	}
	//no longer needed
	long double operator()(Vertex<NoInfo> * a) const {
		return haversine_km(a->getInfo().latitude, a->getInfo().longitude,
				destino.latitude, destino.longitude);
	}
};

//class Aresta {
//public:
//	BigAssInteger idAresta;
//	long double distancia;
//	NoInfo origem;
//	NoInfo destino;
//	string rua;
//	bool dois_sentidos;
//};

//struct hashFuncAresta {
//	bool operator()(const Aresta &s1, const Aresta &s2) const {
//		return s1.idAresta == s2.idAresta;
//	}
//
//	int operator()(const Aresta &s1) const {
//		return s1.idAresta * 37;
//	}
//
//};

//TODO se puser lat e long dentro do Vertex<T>, � possivel nao chamar esta fun�ao e diminuir o nr de vezes
//que a mesma � chamada, em vez de ser pa cada no so vai pos nos que entram na fila de prioridade, que sao
//em pratica muito menos
//void preparaA_star(Graph<NoInfo> &data, const NoInfo& destino) {
//
//	for (unsigned int i = 0; i < data.getVertexSet().size(); i++) {
//		data.getVertexSet()[i]->setDestiny(
//				haversine_km(data.getVertexSet()[i]->getInfo().latitude,
//						data.getVertexSet()[i]->getInfo().longitude,
//						destino.longitude, destino.longitude));
//	}
//}

void abrirFicheiros(string A, string B, string C, Graph<NoInfo> & grafo,
		GraphViewer * gv) {

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

		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> X;
		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> Y;    //X and Y are in degrees

		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> X;
		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> Y;    //X and Y are in radians
		//cout << "idNo: " << idNo << " long: " << X << " lat: " << Y << endl;
		NoInfo temp(idNo % 100000000, X, Y);
		gv->addNode(idNo % 100000000);
		grafo.addVertex(temp);

	}

	inFile.close();

	//abrir C2.txt sao as arestas
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
							destiny->getInfo().longitude), i);
		}
		grafo.addEdge(origem, destino,
				haversine_km(source->getInfo().latitude,
						source->getInfo().longitude,
						destiny->getInfo().latitude,
						destiny->getInfo().longitude), i);
		gv->addEdge(i, idNo1 % 100000000, idNo2 % 100000000,
				EdgeType::DIRECTED);
		gv->setVertexColor(idNo1 % 100000000, GREEN);
		i++;

		//}

	}
	gv->rearrange();
	inFile.close();
}

//void testFloidWarshal_big(Graph<NoInfo>& data, GraphViewer*& gv) {
//	//teste floyd warshal bigger
//	int i = 0;
//
//	while (i < 6) {
//		int ind0 = rand() % data.getVertexSet().size();
//		int ind1 = rand() % data.getVertexSet().size();
//		Vertex<NoInfo> * ori = data.getVertex(
//				NoInfo(data.getVertexSet()[ind0]->getInfo().idNo, 0, 0));
//		Vertex<NoInfo> * des = data.getVertex(
//				NoInfo(data.getVertexSet()[ind1]->getInfo().idNo, 0, 0));
//		if (ori == NULL || des == NULL || ori == des)
//			continue;
//
//		vector<NoInfo> path = data.getDijkstraPath(ori->getInfo(),
//				des->getInfo());
//		string color = "BLACK";
//		switch (i) {
//		case 0:
//			color = YELLOW;
//			break;
//		case 1:
//			color = ORANGE;
//			break;
//		case 2:
//			color = RED;
//			break;
//		case 3:
//			color = PINK;
//			break;
//		case 4:
//			color = GRAY;
//			break;
//		case 5:
//			color = BLACK;
//			break;
//		}
//
//		cout << "novo caminho: " << i << endl;
//		for (unsigned int i = 0; i < path.size(); i++) {
//			//Sleep(100);
//			cout << path[i] << endl;
//			gv->setVertexColor(path[i].idNo, color);
//		}
//
//		i++;
//	}
////-----------------------fim floydwarshal bigger
//
//}

//void abrirFicheirosImproved(string A, string B, string C, Graph<NoInfo>& grafo,
//		GraphViewer*& gv) {
//	NoInfo nulo(0, 0, 0);
//	map<NoInfo, bool> nos_todos;
//	ifstream inFile;
//
//	//Ler o ficheiro A2.txt
//	inFile.open(A);
//
//	if (!inFile) {
//		cerr << "Unable to open file A2.txt";
//		exit(1);   // call system to stop
//	}
//
//	std::string line;
//
//	BigAssInteger idNo = 0;
//	long double X = 0;
//	long double Y = 0;
//
//	while (std::getline(inFile, line)) {
//		std::stringstream linestream(line);
//		std::string data;
//
//		linestream >> idNo;
//
//		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//		linestream >> X;
//		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//		linestream >> Y;    //X and Y are in degrees
//
//		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//		linestream >> X;
//		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//		linestream >> Y;    //X and Y are in radians
//		//cout << "idNo: " << idNo << " long: " << X << " lat: " << Y << endl;
//		NoInfo temp(idNo, X, Y);
//		pair<NoInfo, bool> par(temp, false);
//		nos_todos.insert(par);
//	}
//
//	inFile.close();
//	// insere todos os nos a falso, no final so estarao a true aqueles que sao cruzamentos
//
//	unordered_set<Aresta, hashFuncAresta, hashFuncAresta> arestas;
//	//unordered_set<Aresta> arestas;
//
//	//ler arestas
//
//	inFile.open(B);
//
//	if (!inFile) {
//		cerr << "Unable to open file B2.txt";
//		exit(1);   // call system to stop
//	}
//
//	BigAssInteger idAresta = 0;
//	string Rua = "";
//	string dois_sent = "False";
//
//	while (std::getline(inFile, line)) {
//		std::stringstream linestream(line);
//		std::string data;
//
//		linestream >> idAresta;
//
//		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//
//		char teste;
//		linestream >> teste;
//		if (teste == ';') {
//			Rua = "unnamed";
//
//		} else {
//			string resto;
//			std::getline(linestream, resto, ';');
//			Rua = teste;
//			Rua = teste + resto;
//		}
//
//		linestream >> dois_sent;
//
//		Aresta temp;
//		temp.origem = NoInfo(0, 0, 0);
//		temp.destino = NoInfo(0, 0, 0);
//		temp.distancia = 0;
//		temp.idAresta = idAresta;
//		temp.rua = Rua;
//		if (dois_sent == "True")
//			temp.dois_sentidos = true;
//		else if (dois_sent == "False")
//			temp.dois_sentidos = false;
//
//		arestas.insert(temp);
//
//	}
//
//	inFile.close();
//
//	//ler ligacoes arestas entre nos para so ficar com nos cruzamentos
//
//	inFile.open(C);
//
//	if (!inFile) {
//		cerr << "Unable to open file C2.txt";
//		exit(1);   // call system to stop
//	}
//
//	idAresta = 0;
//	BigAssInteger idOrigem = 0;
//	BigAssInteger idDestino = 0;
//	//double weight = 0.0;
//
//	while (std::getline(inFile, line)) {
//		std::stringstream linestream(line);
//		std::string data;
//
//		linestream >> idAresta;
//		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//		linestream >> idOrigem;
//		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//		linestream >> idDestino;
//
//		map<NoInfo, bool>::iterator itOrigem = nos_todos.find(
//				NoInfo(idOrigem, 0, 0));
//		NoInfo ori = itOrigem->first;
//		map<NoInfo, bool>::iterator itDestino = nos_todos.find(
//				NoInfo(idDestino, 0, 0));
//		NoInfo dest = itDestino->first;
//		Aresta teste;
//		teste.idAresta = idAresta;
//		unordered_set<Aresta, hashFuncAresta, hashFuncAresta>::iterator itAresta =
//				arestas.find(teste);
//		Aresta alterada = *itAresta;
//
//		if (alterada.origem == nulo) {
//			alterada.origem = ori;
//			itOrigem->second = true;
//		}
//
//		alterada.destino = dest;
//		//haversine_km(double lat1, double long1, double lat2, double long2)
//		alterada.distancia += haversine_km(ori.latitude, ori.longitude,
//				dest.latitude, dest.longitude);
//
//		//atualiza em todas as coisas
//		arestas.erase(itAresta);
//		arestas.insert(alterada);
//
//	}
//
//	inFile.close();
//
////	//escrever consola, teste
////	map<NoInfo, bool>::const_iterator it;
////	it = nos_todos.begin();
////	while (it != nos_todos.end()) {
////		cout << "id: " << it->first.idNo << " lat: " << it->first.latitude
////				<< " long:" << it->first.longitude << " cruz:" << it->second
////				<< endl;
////		it++;
////	}
////
////	tr1::unordered_set<Aresta, hashFuncAresta, hashFuncAresta>::const_iterator itH =
////			arestas.begin();
////	while (itH != arestas.end()) {
////		cout << " idA: " << itH->idAresta << " nome: " << itH->rua << " dois: "
////				<< itH->dois_sentidos << " dist: " << itH->distancia <<endl;
////		itH++;
////	}
//
//	//Graph<NoInfo>& grafo, GraphViewer*& gv
//	//escrever para graph e graphviewer
//	unordered_set<Aresta, hashFuncAresta, hashFuncAresta>::const_iterator itH =
//			arestas.begin();
//	while (itH != arestas.end()) {
//		grafo.addVertex(itH->origem);
//		grafo.addVertex(itH->destino);
//		gv->addNode(itH->origem.idNo);
//		//gv->addNode(itH->origem.idNo, itH->origem.longitude*636700, itH->origem.latitude*636700);
//		gv->addNode(itH->destino.idNo);
//		//gv->addNode(itH->destino.idNo, itH->destino.longitude*636700, itH->destino.latitude*636700);
//
//		if (itH->dois_sentidos) {
//			grafo.addEdge(itH->origem, itH->destino, itH->distancia);
//			grafo.addEdge(itH->destino, itH->origem, itH->distancia);
//			gv->addEdge(itH->idAresta, itH->origem.idNo, itH->destino.idNo,
//					EdgeType::UNDIRECTED);
//		} else {
//			grafo.addEdge(itH->origem, itH->destino, itH->distancia);
//			gv->addEdge(itH->idAresta, itH->origem.idNo, itH->destino.idNo,
//					EdgeType::DIRECTED);
//		}
//		itH++;
//	}
//
//	gv->rearrange();
//
//	itH = arestas.begin();
//	while (itH != arestas.end()) {
//		gv->setVertexColor(itH->origem.idNo, "GREEN");
//		//gv->setVertexColor(itH->destino.idNo,RED);
//		itH++;
//
//	}
//	gv->rearrange();
//
//}

//void testFloidWarshal_med(Graph<NoInfo>& data, GraphViewer*& gv) {
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

//void testDijkstra(Graph<NoInfo>& data, GraphViewer*& gv) {
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

void testSerial() {
	//	class teste {
	//	public:
	//		int i;
	//		double j;
	//		vector<int> vetor;
	//	};
	//
	//	teste um;
	//	um.i = 100;
	//	um.j = 55.55;
	//	um.vetor.push_back(10);
	//	um.vetor.push_back(20);
	//	um.vetor.push_back(30);
	//	um.vetor.push_back(45);
	//
	//	ofstream out;
	//
	//	unsigned char testando[sizeof(teste)];
	//	memcpy(testando, &um, sizeof(teste));
	//
	//
	//	teste * dois;
	//	dois = (teste *)testando;
	//
	//	cout << dois->i << endl;
	//	cout << dois->j << endl;
	//	for(int i = 0; i < dois->vetor.size(); i++)
	//		cout << dois->vetor[i] << endl;
	//-----------------------------fim teste serialization

	//	GraphViewer *gv = new GraphViewer(600, 600, false);
	//	gv->setBackground("background.jpg");
	//	gv->createWindow(600, 600);
	//	gv->defineEdgeDashed(true);
	//	gv->defineVertexColor("blue");
	//	gv->addNode(0,30,120);
	//	gv->addNode(1,30,240);
	//	gv->addNode(2,120,30);
	//	gv->addEdge(0,1,2, EdgeType::UNDIRECTED);
	//	gv->addEdge(1,2,0, EdgeType::DIRECTED);
	//	gv->closeWindow();
	//	cout << "gv closed" << endl;
	//
	//	Sleep(1000);
	//
	//	unsigned char testando[sizeof(GraphViewer)];
	//	memcpy(testando, &(*gv), sizeof(GraphViewer));
	//
	//
	//	GraphViewer * dois;
	//	dois = (GraphViewer *)testando;
	//	cout << "dois created" << endl;
	//	dois->createWindow(600,600);
	//	dois->defineVertexColor("blue");
}

void teste_colorir(Graph<NoInfo>& data, GraphViewer*& gv, int numCaminhos,
		unsigned int sizeCaminhos, Vertex<NoInfo>* source,
		Vertex<NoInfo>* destiny, string cor) {

	if (source == NULL || destiny == NULL) {
		int i = 0;
		while (i < numCaminhos) {
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

			if (path.size() < sizeCaminhos)
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
			for (unsigned int i = 0; i < path.size(); i++) {
				Sleep(100);
				cout << path[i] << endl;

				gv->setVertexColor(path[i].idNo, color);
				gv->setVertexSize(path[i].idNo, 40);
				if (i < (path.size() - 1)) {
					cout << data.getVertex(path[i])->getIdEdge(path[i + 1])
							<< endl;
					gv->setEdgeDashed(
							data.getVertex(path[i])->getIdEdge(path[i + 1]),
							false);
					gv->setEdgeColor(
							data.getVertex(path[i])->getIdEdge(path[i + 1]),
							color);
					gv->setEdgeThickness(
							data.getVertex(path[i])->getIdEdge(path[i + 1]), 5);
				}
				gv->rearrange();
			}

			i++;
		}
	}

	else {
		vector<NoInfo> path = data.getDijkstraPath(source->getInfo(),
				destiny->getInfo());

		for (unsigned int i = 0; i < path.size(); i++) {
			Sleep(100);
			cout << path[i] << endl;

			gv->setVertexColor(path[i].idNo, cor);
			gv->setVertexSize(path[i].idNo, 40);
			if (i < (path.size() - 1)) {
				cout << data.getVertex(path[i])->getIdEdge(path[i + 1]) << endl;
				gv->setEdgeDashed(
						data.getVertex(path[i])->getIdEdge(path[i + 1]), false);
				gv->setEdgeColor(
						data.getVertex(path[i])->getIdEdge(path[i + 1]), cor);
				gv->setEdgeThickness(
						data.getVertex(path[i])->getIdEdge(path[i + 1]), 5);
			}
			gv->rearrange();
		}

	}
}

///**
// * Method that reads the nodes from a text file and adds them to both a GraphViwer a a Graph
// * @param A
// * @param gv
// * @param grafo
// * @param nos_todos
// */
//void read_node_radians(const std::string& A, GraphViewer*& gv,
//		Graph<NoInfo>& grafo, map<NoInfo, bool> nos_todos) {
//	ifstream inFile;
//	string line;
//
//	inFile.open(A);
//
//	if (!inFile) {
//		cerr << "Unable to open file A2.txt";
//		exit(1);   // call system to stop
//	}
//
//	BigAssInteger idNo = 0;
//	long double X = 0;
//	long double Y = 0;
//
//	while (std::getline(inFile, line)) {
//		std::stringstream linestream(line);
//		std::string data;
//
//		linestream >> idNo;
//
//		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//		linestream >> X;
//		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//		linestream >> Y;    //X and Y are in degrees
//
//		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//		linestream >> X;
//		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//		linestream >> Y;    //X and Y are in radians
//		//cout << "idNo: " << idNo << " long: " << X << " lat: " << Y << endl;
//		NoInfo temp(idNo, X, Y);
//		pair<NoInfo, bool> par(temp, false);
//		nos_todos.insert(par);
//	}
//
//	inFile.close();
//}
//
///**
// * Method that reads the nodes from a text file and adds them to both a GraphViwer a a Graph
// * @param A
// * @param gv
// * @param grafo
// * @param corners
// * @param maxXwindow
// * @param maxYwindow
// */
//void read_nodes_degrees(const std::string& A, GraphViewer*& gv,
//		Graph<NoInfo>& grafo, struct cantos corners, int maxXwindow,
//		int maxYwindow) {
//	ifstream inFile;
//	//Ler o ficheiro A2.txt
//	inFile.open(A);
//
//	if (!inFile) {
//		cerr << "Unable to open file datafile.txt";
//		exit(1);   // call system to stop
//	}
//
//	std::string line;
//
//	BigAssInteger idNo = 0;
//	long double X = 0;
//	long double Y = 0;
//
//	while (std::getline(inFile, line)) {
//		std::stringstream linestream(line);
//		std::string data;
//
//		linestream >> idNo;
//
//		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;). LATITUDE
//		linestream >> Y;
//		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;). LONGITUDE
//		linestream >> X;    //X and Y are in degrees
//
//		/*cout << X << endl;
//		 cout << Y << endl;
//		 cout << corners.minLong << endl;
//		 cout << corners.minLat << endl;
//		 cout << corners.maxLong << endl;
//		 cout << corners.maxLat << endl;*/
//
//		long double x = ((X * 100000) - (corners.minLong * 100000))
//				* (maxXwindow
//						/ ((corners.maxLong * 100000)
//								- (corners.minLong * 100000)));
//		long double y =
//				((Y * 100000) - (corners.minLat * 100000))
//						* (maxYwindow
//								/ ((corners.maxLat * 100000)
//										- (corners.minLat * 100000)));
//
//		/*cout << X << endl;
//		 cout << Y << endl;
//		 cout << corners.minLong << endl;
//		 cout << corners.minLat << endl;
//		 cout << corners.maxLong << endl;
//		 cout << corners.maxLat << endl;*/
//
//		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//		linestream >> X;
//		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//		linestream >> Y;    //X and Y are in radians
//
//		//cout << "idNo: " << idNo << " long: " << X << " lat: " << Y << endl;
//
//		NoInfo temp(idNo % 100000000, X, Y); //x long, y lat
//
//		gv->addNode(idNo % 100000000, x, maxYwindow - y);
//		cout << "x: " << x << " y: " << y << endl;
//		grafo.addVertex(temp);
//
//	}
//
//	inFile.close();
//}
//
///**
// * Method that reads the edges from a text file and adds them to both a GraphViwer and a Graph. Also calculates the weight of the edge wich is added to the Graph
// * @param C
// * @param gv
// * @param grafo
// */
//void read_edges(
//	unordered_set<Aresta, hashFuncAresta, hashFuncAresta> arestas,
//	const std::string& C, GraphViewer*& gv, Graph<NoInfo>& grafo) {
//
//	ifstream inFile;
//	string line;
//
//	inFile.open(C);
//
//	if (!inFile) {
//		cerr << "Unable to open file datafile.txt";
//		exit(1);   // call system to stop
//	}
//
//	BigAssInteger idAresta;
//	BigAssInteger idNo1;
//	BigAssInteger idNo2;
//
//	BigAssInteger i = 0;
//	//	bool novo = true;
//	//	double weigth = 0;
//	//
//	//	int anterior;
//	while (std::getline(inFile, line)) {
//		std::stringstream linestream(line);
//		std::string data;
//		linestream >> idAresta;
//		Aresta temp;
//		temp.idAresta = idAresta;
//		unordered_set<Aresta, hashFuncAresta, hashFuncAresta>::iterator itAre =
//				arestas.find(temp);
//		//		if(novo){
//		//						anterior = idAresta;
//		//						novo = false;
//		//					}
//
//		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//		linestream >> idNo1;
//		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//		linestream >> idNo2;    //X and Y are in degrees
//
//		NoInfo origem(idNo1 % 100000000, 0, 0);  //so para efeitos de pesquisa
//		Vertex<NoInfo>* source = grafo.getVertex(origem);
//		NoInfo destino(idNo2 % 100000000, 0, 0);
//		Vertex<NoInfo>* destiny = grafo.getVertex(destino);
//
//		//pre processamento do grafico pelo parser ja garante informacao sem erros //i think
//		//if(source != NULL && destiny != NULL){
//
//		if (grafo.removeEdge(origem, destino)) //conseguiu remover
//				{
//			grafo.addEdge(origem, destino,
//					haversine_km(source->getInfo().latitude,
//							source->getInfo().longitude,
//							destiny->getInfo().latitude,
//							destiny->getInfo().longitude));
//		}
//		grafo.addEdge(origem, destino,
//				haversine_km(source->getInfo().latitude,
//						source->getInfo().longitude,
//						destiny->getInfo().latitude,
//						destiny->getInfo().longitude));
//
//		gv->addEdge(i, idNo1 % 100000000, idNo2 % 100000000,
//				EdgeType::DIRECTED);
//		gv->setVertexColor(idNo1 % 100000000, GREEN);
//
//		if (itAre->dois_sentidos) {
//			i++;
//			grafo.addEdge(destino, origem,
//					haversine_km(source->getInfo().getLatitude(),
//							source->getInfo().getLongitude(),
//							destiny->getInfo().getLatitude(),
//							destiny->getInfo().getLongitude())); //distancia entre A e B == distancia entre B e A;
//			gv->addEdge(i, idNo2 % 100000000, idNo1 % 100000000,
//					EdgeType::DIRECTED);
//			gv->setVertexColor(idNo2 % 100000000, GREEN);
//		}
//		i++;
//
//		//}
//
//	}
//	//gv->rearrange();
//	inFile.close();
//}
//
///**
// * Method to assign a name to an Edge and determine if it is one or two ways.
// * @param B
// * @param gv
// * @param grafo
// */
//unordered_set<Aresta, hashFuncAresta, hashFuncAresta> read_edges_names(
//		const std::string& B) {
//	ifstream inFile;
//	string line;
//	unordered_set<Aresta, hashFuncAresta, hashFuncAresta> arestas;
//	//unordered_set<Aresta> arestas;
//
//	inFile.open(B);
//
//	if (!inFile) {
//		cerr << "Unable to open file B2.txt";
//		exit(1);   // call system to stop
//	}
//
//	BigAssInteger idAresta = 0;
//	string Rua = "";
//	string dois_sent = "False";
//
//	while (std::getline(inFile, line)) {
//		std::stringstream linestream(line);
//		std::string data;
//
//		linestream >> idAresta;
//
//		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//
//		char teste;
//		linestream >> teste;
//		if (teste == ';') {
//			Rua = "unnamed";
//
//		} else {
//			string resto;
//			std::getline(linestream, resto, ';');
//			Rua = teste;
//			Rua = teste + resto;
//		}
//
//		linestream >> dois_sent;
//
//		Aresta temp;
//		temp.origem = NoInfo(0, 0, 0);
//		temp.destino = NoInfo(0, 0, 0);
//		temp.distancia = 0;
//		temp.idAresta = idAresta;
//		temp.rua = Rua;
//		if (dois_sent == "True")
//			temp.dois_sentidos = true;
//		else if (dois_sent == "False")
//			temp.dois_sentidos = false;
//
//		arestas.insert(temp);
//
//	}
//
//	inFile.close();
//
//	return arestas;
//}
//
//void abrirFicheiroXY(const std::string& A, const std::string& B,
//		const std::string& C, Graph<NoInfo>& grafo, GraphViewer*& gv,
//		struct cantos corners, int maxXwindow, int maxYwindow) {
//
//	ifstream inFile;
//	std::string line;
//	//Ler o ficheiro A2.txt
//	/*inFile.open(A);
//
//	 if (!inFile) {
//	 cerr << "Unable to open file datafile.txt";
//	 exit(1);   // call system to stop
//	 }
//
//	 std::string line;
//
//	 BigAssInteger idNo = 0;
//	 long double X = 0;
//	 long double Y = 0;
//
//	 while (std::getline(inFile, line)) {
//	 std::stringstream linestream(line);
//	 std::string data;
//
//	 linestream >> idNo;
//
//	 std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//	 linestream >> Y;
//	 std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//	 linestream >> X;    //X and Y are in degrees
//
//	 //		cout << X << endl;
//	 //		cout << Y << endl;
//	 //		cout << corners.minLong << endl;
//	 //		cout << corners.minLat << endl;
//	 //		cout << corners.maxLong << endl;
//	 //		cout << corners.maxLat << endl;
//	 long double x = ((X * 100000) - (corners.minLong * 100000))
//	 * (maxXwindow
//	 / ((corners.maxLong * 100000)
//	 - (corners.minLong * 100000)));
//	 long double y =
//	 ((Y * 100000) - (corners.minLat * 100000))
//	 * (maxYwindow
//	 / ((corners.maxLat * 100000)
//	 - (corners.minLat * 100000)));
//
//	 std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//	 linestream >> X;
//	 std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
//	 linestream >> Y;    //X and Y are in radians
//	 //cout << "idNo: " << idNo << " long: " << X << " lat: " << Y << endl;
//	 NoInfo temp(idNo % 100000000, X, Y); //x long, y lat
//
//	 gv->addNode(idNo % 100000000, x, maxYwindow - y);
//	 cout << "x: " << x << " y: " << y << endl;
//	 grafo.addVertex(temp);
//
//	 }
//
//	 inFile.close();*/
//
//	read_nodes_degrees(A, gv, grafo, corners, maxXwindow, maxYwindow);
//
//	unordered_set<Aresta, hashFuncAresta, hashFuncAresta> arestas =
//			read_edges_names(B);
//
//	//abrir C2.txt sao as arestas
//	read_edges(arestas, C, gv, grafo);
//}

//void TesteOtherMap() {
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
//	testFloidWarshal_big(data, gv);
//}

//void TesteNewYork() {
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
//	testFloidWarshal_big(data, gv);
//}

//void paintPath(GraphViewer *gv, vector<NoInfo> vect, string COLOR) {
//	for (unsigned int i = 0; i < vect.size(); i++) {
//		cout << vect[i] << endl;
//		gv->setVertexColor(vect[i].idNo, COLOR);
//		//gv->setVertexSize(vect[i].idNo, 20);
//	}
//}



int main(int argc, char * argv[]) {
	srand(time(NULL));
	//argv[1] auto, comp or startNode
	//argv[2] endNode or number_of_nodes
	//argv[3] algorithm to use in case startNode->endNode
	//argv[4]	linhas metro
	//argv[5]	comp metro
	//argv[6]	linhas autocarro
	//argv[7]	comp autocarro
	//argv[8]	radical do ficheiro
	//argv[9]	xMaxWindow
	//argv[10]	yMaxWindow
	//argv[11]  minLong
	//argv[12]	minLat
	//argv[13] maxLong
	//argv[14] maxLat
	if(argc != 15){
		cerr << "There was an input error, please contact the developers." << endl;
		return 1;
	}

	string ficheiro = argv[8];
	Graph<NoInfo> data;
	int xMaxW = atoi(argv[9]);
	int yMaxW = atoi(argv[10]);

	GraphViewer * gv = new GraphViewer(xMaxW, yMaxW, false); //not dynamic
	gv->setBackground(ficheiro+".png");
	gv->createWindow(xMaxW, yMaxW);
	gv->defineEdgeCurved(false);
	gv->defineEdgeDashed(true);
	gv->defineVertexColor(GREEN);
	gv->defineVertexSize(4);
	gv->defineEdgeColor(BLACK);
	struct cantos corners;
	corners.minLong = atof(argv[11]);
	corners.minLat = atof(argv[12]);
	corners.maxLong = atof(argv[13]);
	corners.maxLat = atof(argv[14]);

	abrirFicheiroXY(ficheiro+"A.txt", ficheiro+"B.txt",ficheiro+"C.txt", data, gv, corners, xMaxW, yMaxW);

	int linhas_metro = atoi(argv[4]);
	int linhas_autocarro = atoi(argv[6]);
	int comp_metro = atoi(argv[5]);
	int comp_autocarro = atoi(argv[7]);
	gera_linhas(data, linhas_metro, linhas_autocarro, comp_metro, comp_autocarro);

	//	for (unsigned int i = 0; i < data.getVertexSet().size(); i++) {
	//		if (data.getVertexSet()[i]->getInfo().layer == 'M')
	//			gv->setVertexColor(data.getVertexSet()[i]->getInfo().idNo, ORANGE);
	//		else if (data.getVertexSet()[i]->getInfo().layer == 'A')
	//			gv->setVertexColor(data.getVertexSet()[i]->getInfo().idNo, RED);
	//	}

	int number_of_paths = -1;
	if(strcmp(argv[1],"auto")==0){
		number_of_paths = atoi(argv[2]);
		testFloidWarshal_big(data,gv,number_of_paths);
		getchar();
		cout << "END" << endl;
		return 0;

	}
	else if(strcmp(argv[1],"comp")==0){
		testExecutionTimes(data,gv);
		getchar();
		cout << "END" << endl;
		return 0;
	}
	else { //no inicio para o fim

		Vertex<NoInfo> * origem = data.getVertex(NoInfo(atoi(argv[1]),0,0,' '));
		Vertex<NoInfo> * destino = data.getVertex(NoInfo(atoi(argv[2]),0,0,' '));
		if(origem == NULL || destino == NULL){
			cout << "There is no such path" << endl;
			return 2;
		}
		vector<NoInfo> caminho;
		if(strcmp(argv[3],"A*")==0){
			preparaA_star(data, destino->getInfo());
			caminho = data.getA_starPath(origem->getInfo(),destino->getInfo());

		}else if (strcmp(argv[3],"Dijkstra")==0){
			caminho = data.getDijkstraPath(origem->getInfo(),destino->getInfo());

		}else if(strcmp(argv[3],"Floyd-Warshall")==0){
			caminho = data.getfloydWarshallPath(origem->getInfo(),destino->getInfo());
		}


		printPathColored(data,gv,caminho);

		getchar();
		cout << "END" << endl;
		return 0;

	}



	getchar();
	cout << "END" << endl;
	return 0;
}
