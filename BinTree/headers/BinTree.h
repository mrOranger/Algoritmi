/*
 * BinTree.h
 *
 *  Created on: 12 giu 2019
 *      Author: mrOranger
 */

#ifndef BINTREE_H_
#define BINTREE_H_

#include <iostream>
#include "../../List/headers/LinkedList.h"

using namespace std;

template<class T, class N> class BinTree{
	protected:
		int numNodi;
		static const int MAX_DIM = 1000;
		virtual N getPadre(N) const = 0;
		virtual bool sxVuoto(N) const = 0;
		virtual bool dxVuoto(N) const = 0;
		virtual bool isFoglia(N) const = 0;
		virtual void setFiglioDx(N, const T&) = 0;
		virtual void setFiglioSx(N, const T&) = 0;
		virtual T readNodo(N) const = 0;
		virtual void writeNodo(N, const T&) = 0;
	public:
		virtual N getRadice() const = 0;
		virtual bool isEmpty() const = 0;
		virtual bool isPresent(const T&) const = 0;
		virtual N getFiglioSx(N) const = 0;
		virtual N getFiglioDx(N) const = 0;
		virtual T getMin() const;
		virtual T getMax() const;
		virtual int getAltezza(N) const;
		virtual int getNumNodi() const = 0;
		virtual void insElem(const T&) = 0;
		virtual void insElem(const T&, N) = 0;
		virtual void insSottoalbero(N, const BinTree<T, N>&);
		virtual void deleteAlbero() = 0;
		virtual void deleteSottoAlbero(N) = 0;
		virtual void deleteElem(const T&) = 0;
		virtual void visitaPreOrdine(N) const;
		virtual void visitaPostOrdine(N) const;
		virtual void visitaSimmetrica(N) const;
		virtual LinkedList<T> toList() const = 0;
		virtual void breadthFirst_search() const;
		template<class L, class K> friend ostream& operator<< (ostream&, const BinTree<L, K>&);
		template<class L, class K> friend bool operator== (const BinTree<L, K>&, const BinTree<L, K>&);
		template<class L, class K> friend void operator+ (BinTree<L, K>&, const N);
		template<class L, class K> friend void operator+ (BinTree<L, K>&, const BinTree<L, K>&);
};

template<class T, class N> T BinTree<T, N>::getMin() const {
	N currNodo = getRadice();
	while(!sxVuoto(currNodo)){
		currNodo = getFiglioSx(currNodo);
	}
	return readNodo(currNodo);
}

template<class T, class N> T BinTree<T, N>::getMax() const {
	N currNodo = getRadice();
	while(!dxVuoto(currNodo)){
		currNodo = getFiglioDx(currNodo);
	}
	return readNodo(currNodo);
}

template<class T, class N> int BinTree<T, N>::getAltezza(N nodo) const {
	if(isFoglia(nodo)){
		return 1;
	}else{
		int altezzaSx = 0;
		int altezzaDx = 0;
		if(!sxVuoto(nodo)){
			altezzaSx = getAltezza(getFiglioSx(nodo));
		}
		if(!dxVuoto(nodo)){
			altezzaDx = getAltezza(getFiglioDx(nodo));
		}
		if(altezzaSx > altezzaDx){
			return altezzaSx + 1;
		}else{
			return altezzaDx + 1;
		}
	}
}

template<class T, class N> void BinTree<T, N>::breadthFirst_search() const {
	if(!isEmpty()){
		LinkedList<N> list;
		list.enqueue(getRadice());
		while(!list.isEmpty()){
			N currNodo = list.dequeue();
			cout << readNodo(currNodo) << " ";
			if(!sxVuoto(currNodo)){
				list.enqueue(getFiglioSx(currNodo));
			}
			if(!dxVuoto(currNodo)){
				list.enqueue(getFiglioDx(currNodo));
			}
		}
	}
}

template<class T, class N> void BinTree<T, N>::insSottoalbero(N nodo, const BinTree<T, N>& albero){
	LinkedList<T> list = albero.toList();
	while(!list.isEmpty()){
		insElem(list.pop(), nodo);
	}
}

template<class T, class N> void BinTree<T, N>::visitaPreOrdine(N nodo) const {
	cout << this->readNodo(nodo) << " ";
	if(!sxVuoto(nodo)){
		this->visitaPreOrdine(getFiglioSx(nodo));
	}
	if(!dxVuoto(nodo)){
		this->visitaPreOrdine(getFiglioDx(nodo));
	}
}

template<class T, class N> void BinTree<T, N>::visitaPostOrdine(N nodo) const {
	if(!sxVuoto(nodo)){
		this->visitaPreOrdine(getFiglioSx(nodo));
	}
	if(!dxVuoto(nodo)){
		this->visitaPreOrdine(getFiglioDx(nodo));
	}
	cout << this->readNodo(nodo) << " ";
}

template<class T, class N> void BinTree<T, N>::visitaSimmetrica(N nodo) const {
	if(!sxVuoto(nodo)){
		this->visitaPreOrdine(getFiglioSx(nodo));
	}
	cout << this->readNodo(nodo) << " ";
	if(!dxVuoto(nodo)){
		this->visitaPreOrdine(getFiglioDx(nodo));
	}
}

template<class T, class N> ostream& operator<<(ostream& os, const BinTree<T, N>& tree){
	os << "Numero dei nodi: " << tree.getNumNodi() << endl;
	os << "Altezza: " << tree.getAltezza(tree.getRadice()) << endl;
	os << "Valore massimo: " << tree.getMax() << endl;
	os << "Valore minimo: " << tree.getMin() << endl;
	os << "[ ";
	tree.breadthFirst_search();
	os << " ]";
	return os;
}

template<class T, class N> bool operator==(const BinTree<T, N>& tree1, const BinTree<T, N>& tree2){
	if(tree1.getAltezza(tree1.getRadice()) == tree2.getAltezza(tree2.getRadice())){
		LinkedList<T> list1 = tree1.toList();
		LinkedList<T> list2 = tree2.toList();
		return (list1 == list2);
	}else{
		return false;
	}
}

template<class T, class N> void operator+(BinTree<T, N>& tree1, const N nodo){
	tree1.insElem(readNodo(nodo));
}

template<class T, class N> void operator+(BinTree<T, N>& tree1, const BinTree<T, N>& tree2){
	LinkedList<T> list = tree2.toList();
	while(!list.isEmpty()){
		tree1.insElem(list.dequeue());
	}
}


#endif /* BINTREE_H_ */
