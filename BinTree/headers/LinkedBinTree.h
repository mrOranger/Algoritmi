#ifndef LINKEDBINTREE_H
#define LINKEDBINTREE_H

#include "../../List/headers/LinkedList.h"
#include "BinTree.h"
#include "Nodo.h"

using namespace std;

template<class T> class LinkedBinTree : public BinTree<T, Nodo<T>*>{

	typedef T tipoelem;
	typedef Nodo<T>* posizione;

	private:
		posizione radice;
		posizione getPadre(posizione) const;
		bool sxVuoto(posizione) const;
		bool dxVuoto(posizione) const;
		bool isFoglia(posizione) const;
		void setFiglioDx(posizione, const T&);
		void setFiglioSx(posizione, const T&);
		tipoelem readNodo(posizione) const;
		void writeNodo(posizione, const T&);
	public:
		LinkedBinTree();
		posizione getRadice() const;
		bool isEmpty() const;
		bool isPresent(const T&) const;
		posizione getFiglioSx(posizione) const;
		posizione getFiglioDx(posizione) const;
		int getNumNodi() const;
		void insElem(const T&);
		void insElem(const T&, posizione);
		void deleteAlbero();
		void deleteSottoAlbero(posizione);
		void deleteElem(const T&);
		LinkedList<T> toList() const;
};

template<class T> LinkedBinTree<T>::LinkedBinTree(){
	this->numNodi = 0;
	this->radice = NULL;
}

template<class T> typename LinkedBinTree<T>::posizione LinkedBinTree<T>::getPadre(posizione pos) const {
	return pos->getFather();
}

template<class T> bool LinkedBinTree<T>::sxVuoto(posizione pos) const {
	return (pos->getLeft() == NULL);
}

template<class T> bool LinkedBinTree<T>::dxVuoto(posizione pos) const {
	return (pos->getRight() == NULL);
}

template<class T> bool LinkedBinTree<T>::isFoglia(posizione pos) const {
	return (sxVuoto(pos) && dxVuoto(pos));
}

template<class T> void LinkedBinTree<T>::setFiglioDx(posizione pos, const T& elem){
	pos->getRight()->setElem(elem);
}

template<class T> void LinkedBinTree<T>::setFiglioSx(posizione pos, const T& elem){
	pos->getLeft()->setElem(elem);
}

template<class T> typename LinkedBinTree<T>::tipoelem LinkedBinTree<T>::readNodo(posizione pos) const {
	return (pos->getElem());
}

template<class T> void LinkedBinTree<T>::writeNodo(posizione pos, const T& elem) {
	pos->setElem(elem);
}

template<class T> typename LinkedBinTree<T>::posizione LinkedBinTree<T>::getRadice() const {
	return this->radice;
}

template<class T> bool LinkedBinTree<T>::isEmpty() const {
	return (this->numNodi == 0);
}

template<class T> bool LinkedBinTree<T>::isPresent(const T& elem) const {
	if(!this->isEmpty()){
		LinkedList<posizione> list;
		list.enqueue(getRadice());
		while(!list.isEmpty()){
			posizione currNodo = list.dequeue();
			if(readNodo(currNodo) == elem){
				return true;
			}
			if(!sxVuoto(currNodo)){
				list.enqueue(getFiglioSx(currNodo));
			}
			if(!dxVuoto(currNodo)){
				list.enqueue(getFiglioDx(currNodo));
			}
		}
	}
	return false;
}

template<class T> typename LinkedBinTree<T>::posizione LinkedBinTree<T>::getFiglioSx(posizione pos) const {
	return (pos->getLeft());
}

template<class T> typename LinkedBinTree<T>::posizione LinkedBinTree<T>::getFiglioDx(posizione pos) const {
	return (pos->getRight());
}

template<class T> int LinkedBinTree<T>::getNumNodi() const {
	return this->numNodi;
}

template<class T> void LinkedBinTree<T>::insElem(const T& elem){
	Nodo<tipoelem>* newNodo = new Nodo<tipoelem>(elem);
	if(isEmpty()){
		radice = newNodo;
	}else{
		posizione curr = getRadice();
		while(!isFoglia(curr)){
			if(elem > readNodo(curr)){
				if(dxVuoto(curr)){
					break;
				}else{
					curr = getFiglioDx(curr);
				}
			}else{
				if(sxVuoto(curr)){
					break;
				}else{
					curr = getFiglioSx(curr);
				}
			}
		}
		if(readNodo(curr) > elem){
			newNodo->setFather(curr);
			curr->setLeft(newNodo);
		}else{
			newNodo->setFather(curr);
			curr->setRight(newNodo);
		}
	}
	this->numNodi++;
}

template<class T> void LinkedBinTree<T>::insElem(const T& elem, posizione pos){
	Nodo<tipoelem>* newNodo = new Nodo<tipoelem>(elem);
	if(readNodo(pos) > elem){
		if(!sxVuoto(pos)){
			insElem(elem, getFiglioSx(pos));
		}else{
			newNodo->setFather(pos);
			pos->setLeft(newNodo);
		}
	}else{
		if(!dxVuoto(pos)){
			insElem(elem, getFiglioDx(pos));
		}else{
			newNodo->setFather(pos);
			pos->setRight(newNodo);
		}
	}
	this->numNodi++;
}

template<class T> void LinkedBinTree<T>::deleteAlbero() {
	this->radice = NULL;
	this->numNodi = 0;
}

template<class T> void LinkedBinTree<T>::deleteSottoAlbero(posizione pos){
	if(!isEmpty()){
		posizione padre = getPadre(pos);
		int subNodi = 1;
		/* Calcolo numero nodi da sottrarre */
		LinkedList<posizione> list;
		list.enqueue(pos);
		while(!list.isEmpty()){
			posizione currNodo = list.dequeue();
			if(!sxVuoto(currNodo)){
				list.enqueue(getFiglioSx(currNodo));
				subNodi++;
			}
			if(!dxVuoto(currNodo)){
				list.enqueue(getFiglioDx(currNodo));
				subNodi++;
			}
		}
		if(readNodo(getFiglioSx(padre)) == readNodo(pos)){
			this->numNodi -= subNodi;
			padre->setLeft(NULL);
		}else{
			this->numNodi -= subNodi;
			padre->setRight(NULL);
		}
	}
}

template<class T> void LinkedBinTree<T>::deleteElem(const T& elem){
	LinkedList<posizione> list;
	list.enqueue(getRadice());
	posizione currNodo = getRadice();
	while(!list.isEmpty()){
		currNodo = list.dequeue();
		if(readNodo(currNodo) == elem) {
			break;
		}
		if(!sxVuoto(currNodo)){
			list.enqueue(getFiglioSx(currNodo));
		}
		if(!dxVuoto(currNodo)){
			list.enqueue(getFiglioDx(currNodo));
		}
	}
	/* Inserisco in lista tutti i nodi da riordinare */
	if(readNodo(currNodo->getFather()) > readNodo(currNodo)){
		currNodo->getFather()->setLeft(NULL);
	}else{
		currNodo->getFather()->setRight(NULL);
	}
	list.cancLista();
	LinkedList<posizione> list_;
	list_.enqueue(currNodo);
	while(!list_.isEmpty()){
		currNodo = list_.dequeue();
		list.enqueue(currNodo);
		if(!sxVuoto(currNodo)){
			list_.enqueue(getFiglioSx(currNodo));
		}
		if(!dxVuoto(currNodo)){
			list_.enqueue(getFiglioDx(currNodo));
		}
	}
	list.dequeue();
	while(!list.isEmpty()){
		this->insElem(readNodo(list.dequeue()));
	}

}

template<class T> LinkedList<T> LinkedBinTree<T>::toList() const {
	LinkedList<tipoelem> list;
	LinkedList<posizione> list_;
	list_.enqueue(getRadice());
	posizione currNodo = getRadice();
	while(!list_.isEmpty()){
		currNodo = list_.dequeue();
		list.enqueue(readNodo(currNodo));
		if(!sxVuoto(currNodo)){
			list_.enqueue(getFiglioSx(currNodo));
		}
		if(!dxVuoto(currNodo)){
			list_.enqueue(getFiglioDx(currNodo));
		}
	}
	return list;
}

#endif
