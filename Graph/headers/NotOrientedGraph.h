/*
 * NotOrientedGraph.h
 *
 *  Created on: 23 giu 2019
 *      Author: edoar
 */

#ifndef HEADERS_NOTORIENTEDGRAPH_H_
#define HEADERS_NOTORIENTEDGRAPH_H_
#define INF 9999

#include "Graph.h"
#include "Arch.h"
#include "Nodo.h"
#include "../../List/headers/LinkedList.h"

template<class T> class NotOrientedGraph : public Graph<T, unsigned int>{

	public:
		typedef typename Graph<T, unsigned int>::tipoelem tipoelem;
		typedef typename Graph<T, unsigned int>::nodo nodo;

		/* Attributi protetti */
		Nodo<nodo>** matrix;
		unsigned int maxDim;

		/* Metodo protetti */
		tipoelem readNode(const nodo&) const;
		void setSumWeight(const nodo&, unsigned int);
		void setPrev(const nodo&, const nodo&);
		unsigned int getSumWeight(const nodo&) const;
		nodo getPrev(const nodo&) const;
		void insNode(const nodo&);
		void insArch(const nodo&, const nodo&, unsigned int);
		bool isPresentNode(const nodo&) const;
		bool isPresentArch(const nodo&, const nodo&) const;
		void deleteNode(const nodo&);
		void deleteArch(const nodo&, const nodo&);
		unsigned int getDistance(const nodo&, const nodo&) const;
		nodo getIndex(const tipoelem&) const;
		void printGraph();
	public:
		NotOrientedGraph();
		NotOrientedGraph(unsigned int);

		LinkedList<nodo> getAdj(const nodo&) const;
		void insNodo(const tipoelem&);
		void insArco(const tipoelem&, const tipoelem&, unsigned int);
		void deleteNodo(const tipoelem&);
		void deleteArco(const tipoelem&, const tipoelem&);
};

template<class T> NotOrientedGraph<T>::NotOrientedGraph(){
	this->nNodi = 0;
	this->matrix = new Nodo<nodo>*[this->MAX_DIM];
	for(unsigned int i = 0; i < this->MAX_DIM; i++){
		this->matrix[i] = new Nodo<nodo>[this->MAX_DIM];
	}
	for(unsigned int  i = 0; i < this->MAX_DIM; i++){
		for(unsigned int j = 0; j < this->MAX_DIM; j++){
			this->matrix[i][j].setWeight(INF);
		}
	}
	this->maxDim = this->MAX_DIM;
}

template<class T> NotOrientedGraph<T>::NotOrientedGraph(unsigned int dim){
	this->nNodi = 0;
	this->matrix = new nodo*[dim];
	for(unsigned int i = 0; i < dim; i++){
		this->matrix[i] = new nodo[this->MAX_DIM];
	}
	for(int i = 0; i < dim; i++){
		for(int j = 0; j < dim; j++){
			this->matrix[i][j] = INF;
		}
	}
	this->maxDim = dim;
}

template<class T> typename NotOrientedGraph<T>::tipoelem NotOrientedGraph<T>::readNode(const nodo& n) const {
	return this->listElem.getElemUsingIndex(this->listNodi.getIndex(n) - 1);
}


template<class T> void NotOrientedGraph<T>::insNode(const nodo& n){
	if(!this->listNodi.isPresent(n)){
		this->listNodi.enqueue(n);
	}
	this->nNodi = (unsigned int)this->listNodi.getLength();
}

template<class T> void NotOrientedGraph<T>::insArch(const nodo& n, const nodo& n_, unsigned int weight){
	if(this->listNodi.isPresent(n) && this->listNodi.isPresent(n_)){
		matrix[n][n_].setWeight(weight);
		matrix[n_][n].setWeight(weight);
		Arch a(n , n_, weight);
		Arch a_(n_ , n, weight);
		this->archi.push(a);
		this->archi.push(a_);
	}
}

template<class T> void NotOrientedGraph<T>::setPrev(const nodo& n, const nodo& prev){
	if(this->listNodi.isPresent(n)){
		for(unsigned int i = 0; i < this->maxDim; i++){
			this->matrix[n][i].setPrev(prev);
			this->matrix[i][n].setPrev(prev);
		}
	}
}

template<class T> void NotOrientedGraph<T>::setSumWeight(const nodo& n, unsigned int weight){
	if(this->listNodi.isPresent(n)){
		for(unsigned int i = 0; i < this->maxDim; i++){
			this->matrix[n][i].setSumWeight(weight);
			this->matrix[i][n].setSumWeight(weight);
		}
	}
}

template<class T> unsigned int NotOrientedGraph<T>::getSumWeight(const nodo& n) const {
	if(this->listNodi.isPresent(n)){
		return this->matrix[n][n].getSumWeight();
	}
	return INF;
}

template<class T> typename  NotOrientedGraph<T>::nodo NotOrientedGraph<T>::getPrev(const nodo& n) const {
	if(this->listNodi.isPresent(n)){
		return this->matrix[n][n].getPrev();
	}
	return (NotOrientedGraph<T>::nodo)NULL;
}

template<class T> bool NotOrientedGraph<T>::isPresentNode(const nodo& n) const {
	return (this->listNodi.isPresent(n));
}

template<class T> bool NotOrientedGraph<T>::isPresentArch(const nodo& n, const nodo& n_) const {
	if(this->listNodi.isPresent(n) && this->listNodi.isPresent(n_)){
		if(this->matrix[n][n_].getWeight() != INF){
			return true;
		}
	}
	return false;
}

template<class T> void NotOrientedGraph<T>::deleteNode(const nodo& n) {
	if(this->listNodi.isPresent(n)){
		while(!this->getAdj(n).isEmpty()){
			nodo adiacente = (nodo)this->getAdj(n).dequeue();
			this->deleteArch(n, adiacente);
		}
	}
	this->nNodi = (unsigned int)this->listNodi.getLength();
}

template<class T> void NotOrientedGraph<T>::deleteArch(const nodo& n, const nodo& n_) {
	if(this->listNodi.isPresent(n) && this->listNodi.isPresent(n_)){
		unsigned int weight = this->matrix[n][n_].getWeight();
		this->matrix[n][n_].setWeight(INF);
		this->matrix[n_][n].setWeight(INF);
		Arch a(n, n_, weight);
		Arch a_(n_, n, weight);
		this->archi.cancElem(a);
		this->archi.cancElem(a_);
	}
}

template<class T> LinkedList<typename NotOrientedGraph<T>::nodo> NotOrientedGraph<T>::getAdj(const nodo& n) const {
	LinkedList<nodo> list;
	for(unsigned int i = 0; i < this->maxDim; i++){
		if(this->matrix[n][i].getWeight() != INF){
			list.enqueue(i);
		}
	}
	return list;
}

template<class T> typename NotOrientedGraph<T>::nodo NotOrientedGraph<T>::getIndex(const tipoelem& elem) const {
	for(int i = 0; i < this->getNodes().getLength(); i++){
		if(this->getNodeNames().getElemUsingIndex(i) == elem){
			return (nodo)i;
		}
	}
	return (NotOrientedGraph<T>::nodo)NULL;
}

template<class T> void NotOrientedGraph<T>::printGraph() {
	for(int i = 0; i < this->listNodi.getLength(); i++){
		for(int j = 0; j < this->listNodi.getLength(); j++){
			if(this->matrix[this->listNodi.getElemUsingIndex(i)][this->listNodi.getElemUsingIndex(j)].getWeight() != INF){
				cout << this->listElem.getElemUsingIndex(i) << " -> " << this->listElem.getElemUsingIndex(j) << "(" << this->matrix[this->listNodi.getElemUsingIndex(i)][this->listNodi.getElemUsingIndex(j)].getWeight() << ")" << endl;
			}
		}
	}
}

template<class T> unsigned int NotOrientedGraph<T>::getDistance(const nodo& n, const nodo& n_) const {
	if(this->listNodi.isPresent(n) && this->listNodi.isPresent(n_)){
		return this->matrix[n][n_].getWeight();
	}else{
		return 0;
	}
}

template<class T> void NotOrientedGraph<T>::insNodo(const tipoelem& elem) {
	this->listElem.enqueue(elem);
	this->insNode((nodo)this->h(elem)%this->maxDim);
}

template<class T> void NotOrientedGraph<T>::insArco(const tipoelem& elem, const tipoelem& elem_, unsigned int weight){
	this->insArch((nodo)this->h(elem)%this->maxDim, (nodo)this->h(elem_)%this->maxDim, weight);
}

template<class T> void NotOrientedGraph<T>::deleteNodo(const tipoelem& elem){
	this->listElem.cancElem(elem);
	this->deleteNode((nodo)this->h(elem)%this->maxDim);
	this->listNodi.cancElem(this->h(elem)%this->maxDim);
}

template<class T> void NotOrientedGraph<T>::deleteArco(const tipoelem& elem, const tipoelem& elem_){
	this->deleteArch((nodo)this->h(elem)%this->maxDim, (nodo)this->h(elem_)%this->maxDim);
}


#endif /* HEADERS_NOTORIENTEDGRAPH_H_ */
