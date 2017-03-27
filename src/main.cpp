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

class NoInfo {
public:
	long double longitude;
	long double latitude;
	long int idNo;

	NoInfo() {

	}
	;
	NoInfo(int id, double longe, double lat) :
			idNo(id), longitude(longe), latitude(lat) {
	}
	;

	friend ostream & operator<<(ostream & os, const NoInfo obj) {
		os << "idNo: " << obj.idNo << " long: " << obj.longitude << " lat: "
				<< obj.latitude << endl;
		return os;
	}
	;

	friend bool operator==(const NoInfo& left, const NoInfo& right) {
		return ((left.idNo == right.idNo));
	}

	friend bool operator<(const NoInfo& left, const NoInfo& right) {
		return left.idNo < right.idNo;
	}
};

class Aresta {
public:
	long int idAresta;
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

void abrirFicheiros(string A, string B, string C,Graph<NoInfo> & grafo, GraphViewer * gv) {

	ifstream inFile;
	//Ler o ficheiro A2.txt
	inFile.open(A);

	if (!inFile) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	std::string line;

	int idNo = 0;
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
		gv->addNode(idNo);
		grafo.addVertex(temp);

	}

	inFile.close();

	//abrir C2.txt sao as arestas
	inFile.open(C);

	if (!inFile) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	int idAresta;
	int idNo1;
	int idNo2;

	int i = 0;
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

		NoInfo origem(idNo1, 0, 0);  //so para efeitos de pesquisa
		Vertex<NoInfo>* source = grafo.getVertex(origem);
		NoInfo destino(idNo2, 0, 0);
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
		gv->addEdge(i, idNo1, idNo2, EdgeType::DIRECTED);
		gv->setVertexColor(idNo1,GREEN);
		i++;

		//}

	}
	gv->rearrange();
	inFile.close();
}

void abrirFicheirosImproved(string A, string B, string C, Graph<NoInfo>& grafo, GraphViewer*& gv) {
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

	long int idNo = 0;
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

	long int idAresta = 0;
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
	long int idOrigem = 0;
	long int idDestino = 0;
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

		if(itH->dois_sentidos){
			grafo.addEdge(itH->origem, itH->destino, itH->distancia);
			grafo.addEdge(itH->destino, itH->origem, itH->distancia);
			gv->addEdge(itH->idAresta, itH->origem.idNo, itH->destino.idNo,EdgeType::UNDIRECTED);
		}
		else{
			grafo.addEdge(itH->origem, itH->destino, itH->distancia);
			gv->addEdge(itH->idAresta, itH->origem.idNo, itH->destino.idNo,EdgeType::DIRECTED);
		}
		itH++;
	}

	gv->rearrange();


	itH = arestas.begin();
	int i = 0;
	while(itH != arestas.end()){
		gv->setVertexColor(itH->origem.idNo,GREEN);
		//gv->setVertexColor(itH->destino.idNo,RED);
		itH++;

	}
	gv->rearrange();


}

int main() {
	//exercicio1();
	//exercicio2();
	//exercicio3();
	//exercicioTeste();

	//CRIAR GRAFO INTERNO
	Graph<NoInfo> data;

	//CRIAR GRAPHVIEWER
	GraphViewer *gv = new GraphViewer(5000, 5000, true); //not dynamic
	gv->setBackground("background.jpg");
	gv->createWindow(5000, 5000);
	gv->defineEdgeDashed(true);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");
	//tiniest
	//abrirFicheiros("tinyA.txt","tinyB.txt", "tinyC.txt",data, gv);
	//amostra really small
	//abrirFicheiros("smallerA.txt","smallerB.txt", "smallerC.txt",data, gv);
	//amostra pequena
	//abrirFicheirosImproved("A2.txt","B2.txt", "C2.txt",data, gv);
	//amostra media
	//abrirFicheirosImproved("A.txt","B.txt", "C.txt",data, gv);
	//amostra grande
	abrirFicheiros("AnodeINFO.txt","BroadINFO.txt", "CconectionINFO.txt",data, gv);

	gv->rearrange();
	//testing serielization

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
//

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

	getchar();
	cout << "END" << endl;
	return 0;
}
