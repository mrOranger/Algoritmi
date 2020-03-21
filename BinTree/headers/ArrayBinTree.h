/*
 * ArrayBinTree.h
 *
 *  Created on: 12 giu 2019
 *      Author: mrOranger
 */

#ifndef ARRAYBINTREE_H_
#define ARRAYBINTREE_H_

#include "BinTree.h"
#include "Cella.h"

template<class T> class ArrayBinTree : public BinTree<T, int>{

	private:
		Cella<T>* nodi;
		int getPadre(int) const;
		bool sxVuoto(int) const;
		bool dxVuoto(int) const;
		bool isUsedNodo(int) const;
		bool isFoglia(int) const;
		void setFiglioDx(int, const T&);
		void setFiglioSx(int, const T&);
		T readNodo(int) const;
		void writeNodo(int, const T&);
	public:
		ArrayBinTree();
		ArrayBinTree(int);
		ArrayBinTree(const T&);
		ArrayBinTree(const T&, int);
		int getRadice() const;
		int getFiglioSx(int) const;
		int getFiglioDx(int) const;
		void printAlbero() const;
		bool isEmpty() const;
		bool isPresent(const T&) const;
		void insElem(const T&);
		void insElem(const T&, int);
		void deleteElem(const T&);
		void deleteSottoAlbero(int);
		void deleteAlbero();
		int getNumNodi() const;
		LinkedList<T> toList() const;
		~ArrayBinTree();
};

template<class T> ArrayBinTree<T>::ArrayBinTree(){
	this->numNodi = 0;
	this->nodi = new Cella<T>[this->MAX_DIM];
}

template<class T> ArrayBinTree<T>::ArrayBinTree(int max_dim){
	this->numNodi = 0;
	this->nodi = new Cella<T>[max_dim];
}

template<class T> ArrayBinTree<T>::ArrayBinTree(const T& radice){
	this->numNodi = 0;
	this->nodi = new Cella<T>[this->MAX_DIM];
	this->nodi[0]->setElem(radice);
}

template<class T> ArrayBinTree<T>::ArrayBinTree(const T& radice, int max_dim){
	this->numNodi = 0;
	this->nodi = new Cella<T>[max_dim];
	this->nodi[0]->setElem(radice);
}

template<class T> int ArrayBinTree<T>::getRadice() const {
	return 1;
}

template<class T> int ArrayBinTree<T>::getPadre(int figlio) const {
	/* Se il figlio non � la radice */
	if(figlio != 1){
		if(figlio % 2 == 0){
			if(figlio/2 == 1){
				return 1;
			}else{
				return (figlio/2);
			}
		}else{
			if(figlio/2 == 1){
				return 1;
			}else{
				return ((figlio - 1)/2);
			}
		}
	}
}

template<class T> int ArrayBinTree<T>::getFiglioDx(int padre) const {
	return (padre*2 + 1);
}

template<class T> int ArrayBinTree<T>::getFiglioSx(int padre) const {
	return (padre*2);
}

template<class T> bool ArrayBinTree<T>::sxVuoto(int padre) const {
	return (this->nodi[this->getFiglioSx(padre) - 1].isUsed() == false);
}

template<class T> bool ArrayBinTree<T>::dxVuoto(int padre) const {
	return (this->nodi[this->getFiglioDx(padre) - 1].isUsed() == false);
}

template<class T> bool ArrayBinTree<T>::isUsedNodo(int nodo) const {
	return this->nodi[nodo - 1].isUsed();
}

template<class T> bool ArrayBinTree<T>::isFoglia(int nodo) const {
	return (this->sxVuoto(nodo) && this->dxVuoto(nodo));
}

template<class T> void ArrayBinTree<T>::setFiglioDx(int nodo, const T& elem) {
	this->nodi[this->getFiglioDx(nodo)].setElem(elem);
}

template<class T> void ArrayBinTree<T>::setFiglioSx(int nodo, const T& elem) {
	this->nodi[this->getFiglioSx(nodo)].setElem(elem);
}

template<class T> T ArrayBinTree<T>::readNodo(int nodo) const {
	if(this->nodi[nodo - 1].isUsed()){
		return this->nodi[nodo - 1].getElem();
	}
}

template<class T> void ArrayBinTree<T>::writeNodo(int nodo, const T& elem){
	this->nodi[nodo - 1].setElem(elem);
}

template<class T> bool ArrayBinTree<T>::isEmpty() const {
	return (this->numNodi == 0);
}

template<class T> bool ArrayBinTree<T>::isPresent(const T& elem) const {
	for(int i = 0; i < this->MAX_DIM; i++){
		if(this->nodi[i].getElem() == elem){
			return true;
		}
	}
	return false;
}

template<class T> void ArrayBinTree<T>::insElem(const T& elem){
	bool trovato = false;
	int currIndex = this->getRadice();
	while(!trovato){
		if(!this->isUsedNodo(currIndex)){
			trovato = true;
			this->writeNodo(currIndex, elem);
			this->numNodi++;
		}else{
			if(this->readNodo(currIndex) < elem){
				currIndex = this->getFiglioDx(currIndex);
			}else{
				currIndex = this->getFiglioSx(currIndex);
			}
		}
	}
}

template<class T> void ArrayBinTree<T>::insElem(const T& elem, int nodo){
	bool trovato = false;
	int currIndex = nodo;
	while(!trovato){
		if(!this->isUsedNodo(currIndex)){
			trovato = true;
			this->writeNodo(currIndex, elem);
			this->numNodi++;
		}else{
			if(this->readNodo(currIndex) < elem){
				currIndex = this->getFiglioDx(currIndex);
			}else{
				currIndex = this->getFiglioSx(currIndex);
			}
		}
	}
}

template<class T> void ArrayBinTree<T>::deleteElem(const T& elem){
	bool found = false;
	int nodo = 0;
	for(int i = 0; i < this->MAX_DIM || !found; i++){
		if(this->nodi[i].getElem() == elem){
			nodo = (i + 1);
			found = true;
		}
	}
	if(found){
		if(isFoglia(nodo)){
			nodi[nodo - 1].cancCella();
			this->numNodi--;
		}else{
			if(!sxVuoto(nodo)){
				int currElem = nodo;
				int precElem = getFiglioSx(nodo);
				while(!isFoglia(currElem)){
					writeNodo(currElem, readNodo(precElem));
					currElem = precElem;
					precElem = getFiglioSx(currElem);
				}
				nodi[currElem - 1].cancCella();
				this->numNodi--;
			}else{
				int currElem = nodo;
				int precElem = getFiglioDx(nodo);
				while(!isFoglia(currElem)){
					writeNodo(currElem, readNodo(precElem));
					currElem = precElem;
					precElem = getFiglioDx(currElem);
				}
				nodi[currElem - 1].cancCella();
				this->numNodi--;
			}
		}
	}
}

template<class T> void ArrayBinTree<T>::deleteSottoAlbero(int nodo){
	if(!sxVuoto(nodo)){
		deleteSottoAlbero(getFiglioSx(nodo));
	}
	if(!dxVuoto(nodo)){
		deleteSottoAlbero(getFiglioDx(nodo));
	}
	nodi[nodo - 1].cancCella();
	this->numNodi--;
}

template<class T> void ArrayBinTree<T>::deleteAlbero(){
	deleteSottoAlbero(getRadice());
}

template<class T> int ArrayBinTree<T>::getNumNodi() const {
	return this->numNodi;
}

template<class T> LinkedList<T> ArrayBinTree<T>::toList() const {
	LinkedList<T> list;
	for(int i = 0; i < this->MAX_DIM; i++){
		if(this->nodi[i].isUsed()){
			list.enqueue(nodi[i].getElem());
		}
	}
	return list;
}

template<class T> void ArrayBinTree<T>::printAlbero() const {
	cout << "Numero nodi: " << this->numNodi << endl;
	for(int i = 0; i < this->MAX_DIM; i++){
		if(this->nodi[i].isUsed()){
			cout << "(" << readNodo(i + 1) << ", " << i+1 << ")";
		}
	}
	cout << endl;
}

template<class T> ArrayBinTree<T>::~ArrayBinTree(){
	this->numNodi = 0;
	delete nodi;
}

#endif /* ARRAYBINTREE_H_ */
