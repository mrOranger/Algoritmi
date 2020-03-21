/*
 * Tree.h
 *
 *  Created on: 16 giu 2019
 *      Author: edoar
 */

#ifndef TREE_H_
#define TREE_H_

#include "../../List/headers/LinkedList.h"

template<class T, class N> class Tree {

	protected:
		typedef T tipoelem;
		typedef N nodo;
		unsigned int num_nodi;
		unsigned int max_nodi;
		static const unsigned int MAX_DIM = 1000;
		nodo radice;
		virtual tipoelem leggiNodo(const nodo&) const = 0;
		virtual bool isPadre(nodo, nodo) const = 0;
		virtual bool isFoglia(nodo) const = 0;
		virtual bool isUltimoFratello(nodo) const = 0;
		virtual bool isFiglio(nodo, nodo) const = 0;
		virtual nodo getPadre(nodo) const = 0;
		virtual nodo getPrimoFiglio(nodo) const = 0;
		virtual nodo getProxFratello(nodo) const = 0;
		virtual void insRadice(nodo) = 0;
		virtual void insFratello(nodo, const nodo&) = 0;
		virtual void insPrimoFiglio(nodo, const nodo&) = 0;
		virtual void cancNodo(nodo) = 0;
		virtual void cancSottoAlbero(nodo) = 0;
	public:
		virtual bool isEmpty() const;
		virtual nodo getRadice() const = 0;
		virtual void insSottoalberoAsFratello(nodo, const Tree<T, N>&) = 0;
		virtual void insSottoalberoAsFiglio(nodo, const Tree<T, N>&) = 0;
		virtual void insRadice(const tipoelem&) = 0;
		virtual void insFiglio(const tipoelem&, const tipoelem&) = 0;
		virtual void insFratello(const tipoelem&, const tipoelem&) = 0;
		virtual void cancNodo(const tipoelem&) = 0;
		virtual void cancAlbero() = 0;
		virtual void cancSottoAlbero(const tipoelem&) = 0;
		virtual T getMax(const nodo&) const;
		virtual T getMin(const nodo&) const;
		virtual unsigned int getNumNodi() const;
		virtual unsigned int getAltezza(const nodo& n) const;
		virtual unsigned int getFoglie() const;
		virtual unsigned int getNumFigli(const nodo&) const;
		virtual T* toArray() const;
		virtual void visitaPreOrdine(const nodo&) const;
		virtual void visitaPostOrdine(const nodo&) const;
		virtual void visitaSimmetrica(const nodo&) const;
		virtual void breathFirstSearch(const nodo&) const;
		virtual ~Tree();
};

template<class T, class N> bool Tree<T, N>::isEmpty() const{
	return (this->num_nodi == 0);
}

template<class T, class N> unsigned int Tree<T, N>::getNumNodi() const {
	return this->num_nodi;
}

template<class T, class N> unsigned int Tree<T, N>::getAltezza(const nodo& n) const {
	unsigned int maxAltezza = 0, currAltezza = 0;
	if(isFoglia(n)){
		return 1;
	}else{
		/* Esplora in profondità */
		nodo primoFiglio = getPrimoFiglio(n);
		maxAltezza = getAltezza(primoFiglio);
		while(!isUltimoFratello(primoFiglio)){
			primoFiglio = getProxFratello(primoFiglio);
			currAltezza = getAltezza(primoFiglio);
		}
		if(maxAltezza < currAltezza){
			maxAltezza = currAltezza;
		}
	}
	return (maxAltezza + 1);
}

template<class T, class N> T Tree<T, N>::getMax(const nodo& n) const {
	LinkedList<nodo> coda;
	coda.enqueue(n);
	T currElem = leggiNodo(n);
	while(!coda.isEmpty()){
		nodo currNodo = coda.dequeue();
		if(currElem < leggiNodo(currNodo)){
			currElem = leggiNodo(currNodo);
		}
		if(!isFoglia(currNodo)){
			currNodo = getPrimoFiglio(currNodo);
			coda.enqueue(currNodo);
			while(!isUltimoFratello(currNodo)){
				currNodo = getProxFratello(currNodo);
				coda.enqueue(currNodo);
			}
		}
	}
	return currElem;
}

template<class T, class N> T Tree<T, N>::getMin(const nodo& n) const {
	LinkedList<nodo> coda;
	coda.enqueue(n);
	T currElem = leggiNodo(n);
	while(!coda.isEmpty()){
		nodo currNodo = coda.dequeue();
		if(currElem > leggiNodo(currNodo)){
			currElem = leggiNodo(currNodo);
		}
		if(!isFoglia(currNodo)){
			currNodo = getPrimoFiglio(currNodo);
			coda.enqueue(currNodo);
			while(!isUltimoFratello(currNodo)){
				currNodo = getProxFratello(currNodo);
				coda.enqueue(currNodo);
			}
		}
	}
	return currElem;
}

template<class T, class N> unsigned int Tree<T, N>::getFoglie() const {
	LinkedList<nodo> coda;
	coda.enqueue(getRadice());
	unsigned int numFoglie = 0;
	while(!coda.isEmpty()){
		nodo currNodo = coda.dequeue();
		if(!isFoglia(currNodo)){
			currNodo = getPrimoFiglio(currNodo);
			coda.enqueue(currNodo);
			while(!isUltimoFratello(currNodo)){
				currNodo = getProxFratello(currNodo);
				coda.enqueue(currNodo);
			}
		}else{
			numFoglie++;
		}
	}
	return numFoglie;
}

template<class T, class N> unsigned int Tree<T, N>::getNumFigli(const nodo& n) const {
	LinkedList<nodo> coda;
	coda.enqueue(n);
	unsigned int numFigli = 0;
	while(!coda.isEmpty()){
		nodo currNodo = coda.dequeue();
		numFigli++;
		if(!isFoglia(currNodo)){
			currNodo = getPrimoFiglio(currNodo);
			coda.enqueue(currNodo);
			while(!isUltimoFratello(currNodo)){
				currNodo = getProxFratello(currNodo);
				coda.enqueue(currNodo);
			}
		}
	}
	return (numFigli - 1);
}

template<class T, class N> void Tree<T, N>::breathFirstSearch(const nodo& padre) const {
	LinkedList<nodo> coda;
	coda.enqueue(padre);
	while(!coda.isEmpty()){
		nodo currNodo = coda.dequeue();
		cout << leggiNodo(currNodo) << " ";
		if(!isFoglia(currNodo)){
			currNodo = getPrimoFiglio(currNodo);
			coda.enqueue(currNodo);
			while(!isUltimoFratello(currNodo)){
				currNodo = getProxFratello(currNodo);
				coda.enqueue(currNodo);
			}
		}
	}
	cout << endl;
}

template<class T, class N> void Tree<T, N>::visitaPreOrdine(const nodo& n) const {
	cout << leggiNodo(n) << " ";
	if(!isFoglia(n)){
		nodo figlio = getPrimoFiglio(n);
		while(!isUltimoFratello(figlio)){
			visitaPreOrdine(figlio);
			figlio = getProxFratello(figlio);
		}
		visitaPreOrdine(figlio);
	}
}

template<class T, class N> void Tree<T, N>::visitaPostOrdine(const nodo& n) const {
	if(!isFoglia(n)){
		nodo figlio = getPrimoFiglio(n);
		while(!isUltimoFratello(figlio)){
			visitaPostOrdine(figlio);
			figlio = getProxFratello(figlio);
		}
		visitaPostOrdine(figlio);
	}
	cout << leggiNodo(n) << " ";
}

template<class T, class N> void Tree<T, N>::visitaSimmetrica(const nodo& n) const {
	if(isFoglia(n)){
		cout << leggiNodo(n) << " ";
	}else{
		nodo figlio = getPrimoFiglio(n);
		visitaSimmetrica(figlio);
		cout << leggiNodo(n) << " ";
		while(!isUltimoFratello(figlio)){
			figlio = getProxFratello(figlio);
			visitaSimmetrica(figlio);
		}
	}
}

template<class T, class N> T* Tree<T, N>::toArray() const {
	LinkedList<nodo> coda;
	T* array = new T[this->getNumNodi()];
	int arrayNodi = 0;
	coda.enqueue(getRadice());
	while(!coda.isEmpty()){
		nodo currNodo = coda.dequeue();
		cout << leggiNodo(currNodo) << " ";
		array[arrayNodi] = leggiNodo(currNodo);
		if(!isFoglia(currNodo)){
			currNodo = getPrimoFiglio(currNodo);
			coda.enqueue(currNodo);
			while(!isUltimoFratello(currNodo)){
				currNodo = getProxFratello(currNodo);
				coda.enqueue(currNodo);
			}
		}
	}
	return array;
}

template<class T, class N> Tree<T, N>::~Tree(){
	this->num_nodi = 0;
}

#endif /* TREE_H_ */
