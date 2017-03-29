#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include "Graph.h"
#include <string>
#include <map>
#include <cstring>
#include <unordered_set>
#include <utility>
#include <tr1/unordered_set>

void exercicio1();
void exercicio2();
void exercicio3();

typedef unsigned long long BigAssInteger;
long double haversine_km(long double lat1, long double long1, long double lat2,
		long double long2);


class NoInfo {
public:
	long double longitude;
	long double latitude;
	BigAssInteger idNo;

	NoInfo() {}

	NoInfo(BigAssInteger id, long double longe, long double lat) : idNo(id), longitude(longe), latitude(lat) {}

	friend ostream & operator<<(ostream & os, const NoInfo obj) {
		os << "idNo: " << obj.idNo << " long: " << obj.longitude << " lat: " << obj.latitude << endl;
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

};

template<>
struct vertex_greater_than<int> {
	bool operator()(Vertex<NoInfo> * a, Vertex<NoInfo> * b) const {
		return a->getDist() > b->getDist();
	}
};


template<>
struct heuristicFunc<NoInfo>{
	NoInfo destino;
	bool operator()(Vertex<NoInfo> * a, Vertex<NoInfo> * b){
		long double distOri = haversine_km(a->getInfo().latitude,a->getInfo().longitude,destino.latitude,destino.longitude);
		long double distDest = haversine_km(b->getInfo().latitude,b->getInfo().longitude,destino.latitude,destino.longitude);
		return (distOri > distDest? true : false);
	}
	long double operator()(Vertex<NoInfo> * a) const {
			return haversine_km(a->getInfo().latitude,a->getInfo().longitude,destino.latitude,destino.longitude);
	}
};

class Aresta {
public:
	BigAssInteger idAresta;
	long double distancia;
	NoInfo origem;
	NoInfo destino;
	string rua;
	bool dois_sentidos;
//		bool operator==(const Aresta &other) const {
//			return idAresta == other.idAresta;
//		}
//		size_t operator()(const Aresta &are) const {
//			return idAresta * 37 + 54;
//		}
};

struct hashFunc {
	bool operator()(const Aresta &s1, const Aresta &s2) const {
		return s1.idAresta == s2.idAresta;
	}

	int operator()(const Aresta &s1) const {
		return s1.idAresta * 37;
	}

};

void exercicioTeste() {
	GraphViewer *gv = new GraphViewer(1000, 1000, false); //not dynamic
	gv->setBackground("background.jpg");
	gv->createWindow(1000, 1000);
	gv->defineEdgeDashed(false);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");
	for (int i = 0; i < 5; i++)
	gv->addNode(i, i * 100, i * 100);

}

void exercicio1() {
	GraphViewer *gv = new GraphViewer(600, 600, true);

	gv->setBackground("background.jpg");

	gv->createWindow(600, 600);

	gv->defineEdgeDashed(true);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	gv->addNode(0);
	gv->addNode(1);
	gv->addEdge(0, 0, 1, EdgeType::UNDIRECTED);

	Sleep(2000); // use sleep(1) in linux ; Sleep(2000) on Windows

	gv->removeEdge(0);
	gv->removeNode(1);
	gv->addNode(2);

	gv->rearrange();

	Sleep(2000);

	gv->addEdge(1, 0, 2, EdgeType::UNDIRECTED);
	gv->defineEdgeCurved(false);

	gv->setVertexLabel(0, "Isto e um no");
	gv->setEdgeLabel(1, "Isto e uma aresta");

	gv->setVertexColor(2, "green");
	gv->setEdgeColor(1, "yellow");

	gv->setVertexSize(2, 40);
	gv->setVertexIcon(0, "icon.gif");

	gv->setEdgeDashed(1, false);

	gv->rearrange();

}

void exercicio2() {
	GraphViewer *gv = new GraphViewer(600, 600, false);

	gv->createWindow(600, 600);

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");
	gv->addNode(0, 300, 50);
	gv->addNode(1, 318, 58);
	gv->addNode(4, 300, 100);
	gv->addNode(7, 282, 58);
	gv->addNode(2, 325, 75);
	gv->addNode(3, 318, 93);
	gv->addNode(6, 275, 75);
	gv->addNode(5, 282, 93);

	gv->addNode(8, 150, 200);

	gv->setVertexColor(8, "green");
	gv->setVertexColor(9, "blue");
	gv->setVertexColor(10, "green");
	gv->setVertexColor(11, "blue");
	gv->setVertexColor(12, "green");
	gv->setVertexColor(13, "green");
	gv->addNode(9, 300, 200);
	gv->addNode(10, 450, 200);
	gv->addNode(11, 300, 400);

	gv->addNode(12, 200, 550);
	gv->addNode(13, 400, 550);

	gv->addEdge(0, 0, 1, EdgeType::UNDIRECTED);
	gv->addEdge(1, 1, 2, EdgeType::UNDIRECTED);
	gv->addEdge(2, 2, 3, EdgeType::UNDIRECTED);
	gv->addEdge(3, 3, 4, EdgeType::UNDIRECTED);
	gv->addEdge(4, 4, 5, EdgeType::UNDIRECTED);
	gv->addEdge(5, 5, 6, EdgeType::UNDIRECTED);
	gv->addEdge(6, 6, 7, EdgeType::UNDIRECTED);
	gv->addEdge(7, 7, 0, EdgeType::UNDIRECTED);

	gv->addEdge(8, 4, 9, EdgeType::UNDIRECTED);
	gv->addEdge(9, 9, 8, EdgeType::UNDIRECTED);
	gv->addEdge(10, 9, 10, EdgeType::UNDIRECTED);
	gv->addEdge(11, 9, 11, EdgeType::UNDIRECTED);
	gv->addEdge(12, 11, 12, EdgeType::UNDIRECTED);
	gv->addEdge(13, 11, 13, EdgeType::UNDIRECTED);

	gv->rearrange();
	bool first = true;

	while (1) {
		Sleep(2000);
		if (first) {
			gv->removeNode(12);
			gv->removeNode(13);
			first = false;
		} else {
			gv->removeNode(20);
			gv->removeNode(21);
		}
		gv->addNode(14, 250, 550);
		gv->addNode(15, 350, 550);
		gv->addEdge(14, 11, 14, EdgeType::UNDIRECTED);
		gv->addEdge(15, 11, 15, EdgeType::UNDIRECTED);
		gv->rearrange();

		Sleep(2000);
		gv->removeNode(14);
		gv->removeNode(15);
		gv->addNode(16, 300, 550);
		gv->addNode(17, 300, 550);
		gv->addEdge(16, 11, 16, EdgeType::UNDIRECTED);
		gv->addEdge(17, 11, 17, EdgeType::UNDIRECTED);
		gv->rearrange();
		Sleep(2000);

		gv->removeNode(16);
		gv->removeNode(17);
		gv->addNode(18, 250, 550);
		gv->addNode(19, 350, 550);
		gv->addEdge(18, 11, 18, EdgeType::UNDIRECTED);
		gv->addEdge(19, 11, 19, EdgeType::UNDIRECTED);
		gv->rearrange();
		Sleep(2000);

		gv->removeNode(18);
		gv->removeNode(19);
		gv->addNode(20, 200, 550);
		gv->addNode(21, 400, 550);
		gv->addEdge(20, 11, 20, EdgeType::UNDIRECTED);
		gv->addEdge(21, 11, 21, EdgeType::UNDIRECTED);
		gv->rearrange();
	}
}

void exercicio3() {
	GraphViewer *gv = new GraphViewer(600, 600, false);

	gv->createWindow(600, 600);

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");

	ifstream inFile;

	//Ler o ficheiro nos.txt
	inFile.open("nos.txt");

	if (!inFile) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	std::string line;

	int idNo = 0;
	int X = 0;
	int Y = 0;

	while (std::getline(inFile, line)) {
		std::stringstream linestream(line);
		std::string data;

		linestream >> idNo;

		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> X;
		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> Y;
		gv->addNode(idNo, X, Y);

	}

	inFile.close();

	//Ler o ficheiro arestas.txt
	inFile.open("arestas.txt");

	if (!inFile) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	int idAresta = 0;
	int idNoOrigem = 0;
	int idNoDestino = 0;

	while (std::getline(inFile, line)) {
		std::stringstream linestream(line);
		std::string data;

		linestream >> idAresta;

		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> idNoOrigem;
		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> idNoDestino;
		gv->addEdge(idAresta, idNoOrigem, idNoDestino, EdgeType::UNDIRECTED);

	}

	inFile.close();

	gv->rearrange();
}

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
							destiny->getInfo().longitude));
		}
		grafo.addEdge(origem, destino,
				haversine_km(source->getInfo().latitude,
						source->getInfo().longitude,
						destiny->getInfo().latitude,
						destiny->getInfo().longitude));
		gv->addEdge(i, idNo1 % 100000000, idNo2 % 100000000,
				EdgeType::DIRECTED);
		gv->setVertexColor(idNo1 % 100000000, GREEN);
		i++;

		//}

	}
	gv->rearrange();
	inFile.close();
}

void testFloidWarshal_big(Graph<NoInfo>& data, GraphViewer*& gv) {
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

		vector<NoInfo> path = data.getfloydWarshallPath(ori->getInfo(),
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

void abrirFicheirosImproved(string A, string B, string C, Graph<NoInfo>& grafo,
		GraphViewer*& gv) {
	NoInfo nulo(0, 0, 0);
	map<NoInfo, bool> nos_todos;
	ifstream inFile;

	//Ler o ficheiro A2.txt
	inFile.open(A);

	if (!inFile) {
		cerr << "Unable to open file A2.txt";
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
		NoInfo temp(idNo, X, Y);
		pair<NoInfo, bool> par(temp, false);
		nos_todos.insert(par);
	}

	inFile.close();
	// insere todos os nos a falso, no final so estarao a true aqueles que sao cruzamentos

	tr1::unordered_set<Aresta, hashFunc, hashFunc> arestas;
	//unordered_set<Aresta> arestas;

	//ler arestas

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

	//ler ligacoes arestas entre nos para so ficar com nos cruzamentos

	inFile.open(C);

	if (!inFile) {
		cerr << "Unable to open file C2.txt";
		exit(1);   // call system to stop
	}

	idAresta = 0;
	BigAssInteger idOrigem = 0;
	BigAssInteger idDestino = 0;
	//double weight = 0.0;

	while (std::getline(inFile, line)) {
		std::stringstream linestream(line);
		std::string data;

		linestream >> idAresta;
		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> idOrigem;
		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> idDestino;

		map<NoInfo, bool>::iterator itOrigem = nos_todos.find(
				NoInfo(idOrigem, 0, 0));
		NoInfo ori = itOrigem->first;
		map<NoInfo, bool>::iterator itDestino = nos_todos.find(
				NoInfo(idDestino, 0, 0));
		NoInfo dest = itDestino->first;
		Aresta teste;
		teste.idAresta = idAresta;
		tr1::unordered_set<Aresta, hashFunc, hashFunc>::iterator itAresta =
				arestas.find(teste);
		Aresta alterada = *itAresta;

		if (alterada.origem == nulo) {
			alterada.origem = ori;
			itOrigem->second = true;
		}

		alterada.destino = dest;
		//haversine_km(double lat1, double long1, double lat2, double long2)
		alterada.distancia += haversine_km(ori.latitude, ori.longitude,
				dest.latitude, dest.longitude);

		//atualiza em todas as coisas
		arestas.erase(itAresta);
		arestas.insert(alterada);

	}

	inFile.close();

//	//escrever consola, teste
//	map<NoInfo, bool>::const_iterator it;
//	it = nos_todos.begin();
//	while (it != nos_todos.end()) {
//		cout << "id: " << it->first.idNo << " lat: " << it->first.latitude
//				<< " long:" << it->first.longitude << " cruz:" << it->second
//				<< endl;
//		it++;
//	}
//
//	tr1::unordered_set<Aresta, hashFunc, hashFunc>::const_iterator itH =
//			arestas.begin();
//	while (itH != arestas.end()) {
//		cout << " idA: " << itH->idAresta << " nome: " << itH->rua << " dois: "
//				<< itH->dois_sentidos << " dist: " << itH->distancia <<endl;
//		itH++;
//	}

	//Graph<NoInfo>& grafo, GraphViewer*& gv
	//escrever para graph e graphviewer
	tr1::unordered_set<Aresta, hashFunc, hashFunc>::const_iterator itH =
			arestas.begin();
	while (itH != arestas.end()) {
		grafo.addVertex(itH->origem);
		grafo.addVertex(itH->destino);
		gv->addNode(itH->origem.idNo);
		//gv->addNode(itH->origem.idNo, itH->origem.longitude*636700, itH->origem.latitude*636700);
		gv->addNode(itH->destino.idNo);
		//gv->addNode(itH->destino.idNo, itH->destino.longitude*636700, itH->destino.latitude*636700);

		if (itH->dois_sentidos) {
			grafo.addEdge(itH->origem, itH->destino, itH->distancia);
			grafo.addEdge(itH->destino, itH->origem, itH->distancia);
			gv->addEdge(itH->idAresta, itH->origem.idNo, itH->destino.idNo,
					EdgeType::UNDIRECTED);
		} else {
			grafo.addEdge(itH->origem, itH->destino, itH->distancia);
			gv->addEdge(itH->idAresta, itH->origem.idNo, itH->destino.idNo,
					EdgeType::DIRECTED);
		}
		itH++;
	}

	gv->rearrange();

	itH = arestas.begin();
	int i = 0;
	while (itH != arestas.end()) {
		gv->setVertexColor(itH->origem.idNo, GREEN);
		//gv->setVertexColor(itH->destino.idNo,RED);
		itH++;

	}
	gv->rearrange();

}

void testFloidWarshal_med(Graph<NoInfo>& data, GraphViewer*& gv) {
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

void testDijkstra(Graph<NoInfo>& data, GraphViewer*& gv) {
	Vertex<NoInfo>* origem = data.getVertex(
			NoInfo(173452776 % 100000000, 0, 0));
	data.dijkstraShortestPath(origem->getInfo());

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

struct cantos {
	long double minLong;
	long double minLat;
	long double maxLong;
	long double maxLat;
};

/**
 * Method that reads the nodes from a text file and adds them to both a GraphViwer a a Graph
 * @param A
 * @param gv
 * @param grafo
 * @param nos_todos
 */
void read_node_radians(const std::string& A,GraphViewer*& gv,Graph<NoInfo>& grafo,map<NoInfo, bool> nos_todos){
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
void read_nodes_degrees(const std::string& A,GraphViewer*& gv,Graph<NoInfo>& grafo,struct cantos corners,int maxXwindow, int maxYwindow){
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
void read_edges(const std::string& C,GraphViewer*& gv,Graph<NoInfo>& grafo){
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
								destiny->getInfo().longitude));
			}
			grafo.addEdge(origem, destino,
					haversine_km(source->getInfo().latitude,
							source->getInfo().longitude,
							destiny->getInfo().latitude,
							destiny->getInfo().longitude));
			gv->addEdge(i, idNo1 % 100000000, idNo2 % 100000000,
					EdgeType::DIRECTED);
			gv->setVertexColor(idNo1 % 100000000, GREEN);
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
void read_edges_names(const std::string& B,GraphViewer*& gv,Graph<NoInfo>& grafo){
	ifstream inFile;
	string line;
	tr1::unordered_set<Aresta, hashFunc, hashFunc> arestas;
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
}

void abrirFicheiroXY(const std::string& A, const std::string& B,const std::string& C, Graph<NoInfo>& grafo, GraphViewer*& gv,struct cantos corners, int maxXwindow, int maxYwindow) {

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

	read_nodes_degrees(A,gv,grafo,corners,maxXwindow,maxYwindow);

	//abrir C2.txt sao as arestas
	read_edges(C,gv,grafo);
}

void TesteNewYork(){
	//	int xMaxW = 1000, yMaxW = 947;
	//		GraphViewer * gv = new GraphViewer(xMaxW, yMaxW, false); //not dynamic
	//		gv->setBackground("10IMG1000-947.png");
		//	struct cantos corners;
	//	corners.maxLat = 40.72988;
	//	corners.maxLong = -73.87300;
	//	corners.minLat = 40.72638;
	//	corners.minLong = -73.87790;
	//	abrirFicheiroXY("10IMG1000-947A.txt", "10IMG1000-947B.txt", "10IMG1000-947C.txt", data, gv, corners,xMaxW,yMaxW);



	//CRIAR GRAFO INTERNO
		Graph<NoInfo> data;
	int xMaxW = 5000, yMaxW = 1910;
		GraphViewer * gv = new GraphViewer(xMaxW, yMaxW, false); //not dynamic
		gv->setBackground("NEWY.png");
		gv->createWindow(xMaxW, yMaxW);
		gv->defineEdgeDashed(true);
		gv->defineVertexColor("blue");
		gv->defineVertexSize(4);
		gv->defineEdgeColor("black");
		struct cantos corners;
		corners.maxLat = 40.7127;
		corners.maxLong = -73.9784;
		corners.minLat = 40.7007;
		corners.minLong = -74.0194;
		abrirFicheiroXY("NEWYA.txt", "NEWYB.txt", "NEWYC.txt", data, gv, corners,xMaxW,yMaxW);
}

int main() {
	//CRIAR GRAFO INTERNO
	Graph<NoInfo> data;

	//CRIAR GRAPHVIEWER
	GraphViewer *gv = new GraphViewer(1000, 1000, true); //not dynamic
	gv->setBackground("background.jpg");
	gv->createWindow(1000, 1000);
	gv->defineEdgeDashed(false);
	gv->defineVertexColor("blue");
	gv->defineVertexSize(5);
	gv->defineEdgeColor("black");




	//------------------------tiniest
	//abrirFicheiros("tinyA.txt","tinyB.txt", "tinyC.txt",data, gv);
	//-------------------------amostra really small
	abrirFicheiros("smallerA.txt", "smallerB.txt", "smallerC.txt", data, gv);
	//-----------------------amostra pequena
	//abrirFicheiros("A2.txt","B2.txt", "C2.txt",data, gv);
	//----------------------amostra media
	//abrirFicheiros("A.txt", "B.txt", "C.txt", data, gv);
	//--------------------------------amostra grande
	//abrirFicheiros("AnodeINFO.txt","BroadINFO.txt", "CconectionINFO.txt",data, gv);


	NoInfo ori = data.getVertex(NoInfo(42809632, 0, 0))->getInfo();
	NoInfo des = data.getVertex(NoInfo(42809642, 0, 0))->getInfo();
		vector<NoInfo> path = data.getA_starPath(ori, des);

		for (unsigned int i = 0; i < path.size(); i++) {
			Sleep(100);
			cout << path[i] << endl;
			gv->setVertexColor(path[i].idNo, YELLOW);
			//gv->setVertexSize(path[i].idNo, 20);
		}



	//abrirFicheiros("smallerA.txt","smallerB.txt", "smallerC.txt",data, gv); //com esta
	//testFloidWarshal_med(data, gv);

	//testFloidWarshal_big(data, gv);

	//abrirFicheiros("A2.txt","B2.txt", "C2.txt",data, gv);
	//testDijkstra(data, gv);

	//gv->rearrange();

	getchar();
	cout << "END" << endl;
	return 0;
}
