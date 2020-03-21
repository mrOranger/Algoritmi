/*
 * Graph.h
 *
 *  Created on: 22 giu 2019
 *      Author: edoar
 */

#ifndef HEADERS_GRAPH_H_
#define HEADERS_GRAPH_H_
#define INF 9999

#include "../../List/headers/LinkedList.h"
#include "../../List/headers/sorting_algorithm.h"
#include "../headers/Hash.h"
#include "Arch.h"

template<class T, class N> class Graph{

	public:
		typedef T tipoelem;
		typedef N nodo;

		/* Attributi protetti */
		unsigned int nNodi;
		const static unsigned int MAX_DIM = 1000;
		Hash<tipoelem> h; //Funzione Hash per il calcolo dell'indice
		LinkedList<nodo> listNodi; //Lista dei nodi
		LinkedList<Arch> archi; //Lista degli archi
		LinkedList<tipoelem> listElem; //Lista degli elementi

		/* Metodi protetti */
		virtual tipoelem readNode(const nodo&) const = 0;
		virtual void setSumWeight(const nodo&, unsigned int) = 0;
		virtual void setPrev(const nodo&, const nodo&) = 0;
		virtual unsigned int getSumWeight(const nodo&) const = 0;
		virtual nodo getPrev(const nodo&) const = 0;
		virtual void insNode(const nodo&) = 0;
		virtual void insArch(const nodo&, const nodo&, unsigned int) = 0;
		virtual bool isPresentNode(const nodo&) const = 0;
		virtual bool isPresentArch(const nodo&, const nodo&) const = 0;
		virtual void deleteNode(const nodo&) = 0;
		virtual void deleteArch(const nodo&, const nodo&) = 0;
		virtual unsigned int getDistance(const nodo&, const nodo&) const = 0;
		virtual N getIndex(const T&) const = 0;
		virtual void printGraph() = 0;
		virtual void initCities();
		virtual void initArchs();
	public:
		/* Metodi virtuali pubblici */
		virtual void initGrafo(Graph<T, N>& graph);
		virtual nodo getVertex() const;
		virtual bool isEmpty() const;
		virtual LinkedList<nodo> getNodes() const;
		virtual LinkedList<tipoelem> getNodeNames() const;
		virtual LinkedList<Arch> getArchs() const;
		virtual unsigned int getNumNodes() const;
		virtual unsigned int getNumArchs() const;

		/* Metodi puramente virtuali pubblici */
		virtual LinkedList<nodo> getAdj(const nodo&) const = 0;
		virtual void insNodo(const tipoelem&) = 0;
		virtual void insArco(const tipoelem&, const tipoelem&, unsigned int) = 0;
		virtual void deleteNodo(const tipoelem&) = 0;
		virtual void deleteArco(const tipoelem&, const tipoelem&) = 0;

		/* Algoritmi */
		virtual void breath_first_search(const nodo&) const;
		virtual void depth_first_search(const nodo&) const;
		virtual void dijkstra(const tipoelem&, const tipoelem&);

		template<class L, class K> friend ostream& operator<<(ostream& os, Graph<L, K>&);

		virtual ~Graph();
};

template<class T, class N> void Graph<T, N>::initCities(void) {
	this->insNodo("Arad");
	this->insNodo("Zerind");
	this->insNodo("Timisoara");
	this->insNodo("Oradea");
	this->insNodo("Sibiu");
	this->insNodo("Lugoj");
	this->insNodo("Mehadia");
	this->insNodo("Drobeta");
	this->insNodo("Craiova");
	this->insNodo("Pitesti");
	this->insNodo("Rimnicu Vilcea");
	this->insNodo("Faragas");
	this->insNodo("Bucarest");
	this->insNodo("Giurgiu");
	this->insNodo("Urziceni");
	this->insNodo("Hirsova");
	this->insNodo("Eforie");
	this->insNodo("Vaslui");
	this->insNodo("Iasi");
	this->insNodo("Neamt");
}

template<class T, class N> void Graph<T, N>::initArchs(void){
	this->insArco("Arad", "Zerind", 75);
	this->insArco("Arad", "Timisoara", 118);
	this->insArco("Arad", "Sibiu", 140);
	this->insArco("Zerind", "Oradea", 71);
	this->insArco("Oradea", "Sibiu", 151);
	this->insArco("Timisoara", "Lugoj", 111);
	this->insArco("Lugoj", "Mehadia", 70);
	this->insArco("Mehadia", "Drobeta", 75);
	this->insArco("Drobeta", "Craiova", 120);
	this->insArco("Craiova", "Rimnicu Vilcea", 146);
	this->insArco("Craiova", "Pitesti", 138);
	this->insArco("Pitesti", "Rimnicu Vilcea", 97);
	this->insArco("Rimnicu Vilcea", "Sibiu", 80);
	this->insArco("Sibiu", "Faragas", 99);
	this->insArco("Faragas", "Bucarest", 211);
	this->insArco("Pitesti", "Bucarest", 101);
	this->insArco("Bucarest", "Giurgiu", 90);
	this->insArco("Bucarest", "Urziceni", 85);
	this->insArco("Urziceni", "Hirsova", 98);
	this->insArco("Urziceni", "Vaslui", 142);
	this->insArco("Hirsova", "Eforie", 86);
	this->insArco("Vaslui", "Iasi", 92);
	this->insArco("Iasi", "Neamt", 87);
}

template<class T, class N> void Graph<T, N>::initGrafo(Graph<T, N>& graph){
	this->initCities();
	this->initArchs();
}

template<class T, class N> typename Graph<T, N>::nodo Graph<T, N>::getVertex() const {
	return this->listNodi.getElemUsingIndex(0);
}

template<class T, class N> bool Graph<T, N>::isEmpty() const {
	return this->nNodi == 0;
}

template<class T, class N> LinkedList<typename Graph<T, N>::nodo> Graph<T, N>::getNodes() const {
	return this->listNodi;
}

template<class T, class N> LinkedList<Arch> Graph<T, N>::getArchs() const {
	return this->archi;
}

template<class T, class N> LinkedList<typename Graph<T, N>::tipoelem> Graph<T, N>::getNodeNames() const {
	return this->listElem;
}

template<class T, class N> unsigned int Graph<T, N>::getNumNodes() const {
	return this->nNodi;
}

template<class T, class N> unsigned int Graph<T, N>::getNumArchs() const {
	return this->archi.getLength();
}

template<class T, class N> ostream& operator<<(ostream& os, Graph<T, N>& g){
	os << "( " << endl;
	g.printGraph();
	os << " )" << endl;
	return os;
}

template<class T, class N> void Graph<T, N>::breath_first_search(const nodo& n) const {
	LinkedList<nodo> queue;
	LinkedList<nodo> visited;
	queue.enqueue(n);
	while(!queue.isEmpty()){
		nodo curr = queue.dequeue();
		cout << this->readNode(curr) << ", ";
		visited.enqueue(curr);
		for(int i = 0; i < this->getAdj(curr).getLength(); i++){
			if(!visited.isPresent(this->getAdj(curr).getElemUsingIndex(i)) && !queue.isPresent(this->getAdj(curr).getElemUsingIndex(i))){
				queue.enqueue(this->getAdj(curr).getElemUsingIndex(i));
			}
		}
	}
}

template<class T, class N> void Graph<T, N>::depth_first_search(const nodo& n) const {
	LinkedList<nodo> stack;
	LinkedList<nodo> visited;
	stack.push(n);
	while(!stack.isEmpty()){
		nodo curr = stack.pop();
		cout << this->readNode(curr) << ", ";
		visited.enqueue(curr);
		for(int i = 0; i < this->getAdj(curr).getLength(); i++){
			if(!visited.isPresent(this->getAdj(curr).getElemUsingIndex(i)) && !stack.isPresent(this->getAdj(curr).getElemUsingIndex(i))){
				stack.push(this->getAdj(curr).getElemUsingIndex(i));
			}
		}
	}
}

template<class T, class N> void Graph<T, N>::dijkstra(const tipoelem& src, const tipoelem& dest){
	nodo start = this->getNodes().getElemUsingIndex(this->getIndex(src));
	sorting_algorithm<tipoelem> path;
	sorting_algorithm<nodo> etichettati;
	sorting_algorithm<nodo> daEtichettare;
	etichettati.push(start);
	bool trovato = false;
	for(unsigned int i = 0; i < this->getNumNodes(); i++){
		if(this->getNodes().getElemUsingIndex(i) != start){
			daEtichettare.push(this->getNodes().getElemUsingIndex(i));
		}
	}
	for(unsigned int i = 0; i < this->getNumNodes(); i++){
		this->setSumWeight(this->getNodes().getElemUsingIndex(i), INF);
	}
	for(int i = 0; i < this->getAdj(etichettati.getElem(etichettati.getHead())).getLength(); i++){
		nodo srcNodo = etichettati.getElem(etichettati.getHead());
		nodo destNodo = this->getAdj(etichettati.getElem(etichettati.getHead())).getElemUsingIndex(i);
		this->setSumWeight(destNodo, this->getDistance(srcNodo, destNodo));
		this->setPrev(destNodo, srcNodo);
	}
	daEtichettare.bubble_sort();
	while(!daEtichettare.isEmpty()){
		nodo currNodo = daEtichettare.dequeue();
		if(this->readNode(currNodo) == dest){
			trovato = true;
		}
		for(int i = 0; i < this->getAdj(currNodo).getLength(); i++){
			if(!etichettati.isPresent(this->getAdj(currNodo).getElemUsingIndex(i))){
				unsigned int costoDistanzaNodo = this->getDistance(this->getAdj(currNodo).getElemUsingIndex(i), currNodo);
				unsigned int costoCorrente = this->getSumWeight(this->getAdj(currNodo).getElemUsingIndex(i));
				unsigned int costoPrecedente = this->getSumWeight(currNodo);
				if((costoDistanzaNodo + costoPrecedente) < costoCorrente){
					this->setSumWeight(this->getAdj(currNodo).getElemUsingIndex(i), (costoDistanzaNodo + costoPrecedente));
					this->setPrev(this->getAdj(currNodo).getElemUsingIndex(i), currNodo);
				}
			}
		}
		etichettati.enqueue(currNodo);
		daEtichettare.bubble_sort();
	}
	if(trovato){
		nodo stop = this->getNodes().getElemUsingIndex(this->getIndex(dest));
		nodo currNodo = stop;
		unsigned int totalCost = this->getSumWeight(stop);
		while(currNodo != start){
			path.push(this->readNode(currNodo));
			currNodo = this->getPrev(currNodo);
		}
		path.push(this->readNode(start));
		cout << "Il percorso più breve è: ";
		cout << path << endl;
		cout << "Con costo: " << totalCost << endl;
	}else{
		cout << "Non ho trovato alcun percorso!" << endl;
	}
}

template<class T, class N> Graph<T, N>::~Graph(){
	this->listElem.~LinkedList();
	this->archi.~LinkedList();
	this->listNodi.~LinkedList();
	this->nNodi = 0;
}

#endif /* HEADERS_GRAPH_H_ */

