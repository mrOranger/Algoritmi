/*
 * LinkedTree.h
 *
 *  Created on: 17 giu 2019
 *      Author: edoar
 */

#ifndef LINKEDTREE_H_
#define LINKEDTREE_H_

#include "Tree.h"
#include "Nodo.h"

template<class T> class LinkedTree : public Tree<T, Nodo<T>*>{

	private:
		typedef typename Tree<T, Nodo<T>*>::tipoelem tipoelem;
		typedef typename Tree<T, Nodo<T>*>::nodo nodo;
		tipoelem leggiNodo(const nodo&) const;
		bool isPadre(nodo, nodo) const;
		bool isFoglia(nodo) const;
		bool isUltimoFratello(nodo) const;
		bool isFiglio(nodo, nodo) const;
		nodo getPadre(nodo) const;
		nodo getPrimoFiglio(nodo) const;
		nodo getProxFratello(nodo) const;
		void insRadice(nodo);
		void insFratello(nodo, const nodo&);
		void insPrimoFiglio(nodo, const nodo&);
		void cancNodo(nodo);
		void cancSottoAlbero(nodo);
	public:
		nodo getRadice() const;
		void insSottoalberoAsFratello(nodo, const Tree<T, Nodo<T>*>&);
		void insSottoalberoAsFiglio(nodo, const Tree<T, Nodo<T>*>&);
		void insRadice(const tipoelem&);
		void insFiglio(const tipoelem&, const tipoelem&);
		void insFratello(const tipoelem&, const tipoelem&);
		void cancNodo(const tipoelem&);
		void cancSottoAlbero(const tipoelem&);
		void cancAlbero();
		LinkedTree();
		LinkedTree(unsigned int);
		~LinkedTree();
};

template<class T> LinkedTree<T>::LinkedTree() {
	this->radice = NULL;
	this->num_nodi = 0;
	this->max_nodi = this->MAX_DIM;
}

template<class T> LinkedTree<T>::LinkedTree(unsigned int max_nodi) {
	this->radice = NULL;
	this->num_nodi = 0;
	this->max_nodi = max_nodi;
}

template<class T> void LinkedTree<T>::insRadice(nodo radice){
	if(this->isEmpty()){
		this->num_nodi = 1;
	}
	this->radice = radice;
}

template<class T> typename LinkedTree<T>::tipoelem LinkedTree<T>::leggiNodo(const nodo& n) const {
	return (n->getElem());
}

template<class T> typename LinkedTree<T>::nodo LinkedTree<T>::getRadice() const{
	return this->radice;
}

template<class T> bool LinkedTree<T>::isPadre(nodo padre, nodo figlio) const {
	return (figlio->getPadre() == padre);
}

template<class T> bool LinkedTree<T>::isFoglia(nodo n) const{
	return (n->getPrimoFiglio() == NULL);
}

template<class T> bool LinkedTree<T>::isFiglio(nodo padre, nodo figlio) const {
	typename LinkedTree<T>::nodo currFiglio = getPrimoFiglio(padre);
	while(!isUltimoFratello(currFiglio)){
		if(currFiglio == figlio)
			return true;
		currFiglio = currFiglio->getProxFratello();
	}
	return false;
}

template<class T> typename LinkedTree<T>::nodo LinkedTree<T>::getPadre(nodo n) const {
	return (n->getPadre());
}

template<class T> typename LinkedTree<T>::nodo LinkedTree<T>::getPrimoFiglio(nodo padre) const {
	return (padre->getPrimoFiglio());
}

template<class T> bool LinkedTree<T>::isUltimoFratello(nodo n) const {
	return (n->getProxFratello() == NULL);
}

template<class T> typename LinkedTree<T>::nodo LinkedTree<T>::getProxFratello(nodo n) const {
	return (n->getProxFratello());
}

template<class T> void LinkedTree<T>::insFratello(nodo fratello, const nodo& newFratello){
	typename LinkedTree<T>::nodo currFratello = fratello;
	while(!isUltimoFratello(currFratello)){
		currFratello = getProxFratello(currFratello);
	}
	currFratello->setProxFratello(newFratello);
	newFratello->setPadre(getPadre(fratello));
	this->num_nodi++;
}

template<class T> void LinkedTree<T>::insPrimoFiglio(nodo padre, const nodo& newPrimoFiglio){
	if(isFoglia(padre)){
		padre->setPrimoFiglio(newPrimoFiglio);
	}else{
		typename LinkedTree<T>::nodo oldPrimoFiglio = getPrimoFiglio(padre);
		newPrimoFiglio->setProxFratello(oldPrimoFiglio);
		padre->setPrimoFiglio(newPrimoFiglio);
	}
	newPrimoFiglio->setPadre(padre);
	this->num_nodi++;
}

template<class T> void LinkedTree<T>::insSottoalberoAsFratello(nodo padre, const Tree<T, Nodo<T>*>& tree){
	if(isFoglia(padre)){
		padre->setPrimoFiglio(tree.getRadice());
	}else{
		typename LinkedTree<T>::nodo oldFratello = padre->getPrimoFiglio()->getProxFratello();
		tree.getRadice()->setPadre(padre);
		padre->getPrimoFiglio()->setProxFratello(tree.getRadice());
		padre->getPrimoFiglio()->getProxFratello()->setProxFratello(oldFratello);
	}
	this->num_nodi += tree.getNumNodi();
}

template<class T> void LinkedTree<T>::insSottoalberoAsFiglio(nodo padre, const Tree<T, Nodo<T>*>& tree){
	if(isFoglia(padre)){
		padre->setPrimoFiglio(tree.getRadice());
	}else{
		typename LinkedTree<T>::nodo oldPrimoFiglio = getPrimoFiglio(padre);
		tree.getRadice()->setPadre(padre);
		padre->setPrimoFiglio(tree.getRadice());
		padre->getPrimoFiglio()->setProxFratello(oldPrimoFiglio);
	}
	this->num_nodi += tree.getNumNodi();
}

template<class T> void LinkedTree<T>::insRadice(const tipoelem& elem){
	if(this->isEmpty()){
		this->num_nodi = 1;
		this->radice = new Nodo<T>(elem);
	}else{
		getRadice()->setElem(elem);
	}
}

template<class T> void LinkedTree<T>::insFiglio(const tipoelem& e, const tipoelem& e_){
	LinkedList<nodo> coda;
	coda.enqueue(getRadice());
	nodo trovato = getRadice();
	while(!coda.isEmpty()){
		nodo currNodo = coda.dequeue();
		if(leggiNodo(currNodo) == e){
			trovato = currNodo;
			break;
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
	/* Se il nodo è una foglia, imposto come primo figlio il nuovo nodo */
	if(isFoglia(trovato)){
		trovato->setPrimoFiglio(new Nodo<T>(e_, trovato, NULL, NULL));
	}else{
		/* Altrimenti inserisco il nuovo nodo come fratello dei figli */
		nodo fratello = getPrimoFiglio(trovato);
		while(!isUltimoFratello(fratello)){
			fratello = getProxFratello(fratello);
		}
		fratello->setProxFratello(new Nodo<T>(e_, fratello->getPadre(), NULL, NULL));
	}
	this->num_nodi++;
}

template<class T> void LinkedTree<T>::insFratello(const tipoelem& e, const tipoelem& e_){
	LinkedList<nodo> coda;
	coda.enqueue(getRadice());
	nodo trovato = getRadice();
	while(!coda.isEmpty()){
		nodo currNodo = coda.dequeue();
		if(leggiNodo(currNodo) == e){
			trovato = currNodo;
			break;
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
	/* Se il nodo è una foglia, imposto come primo figlio il nuovo nodo */
	if(isUltimoFratello(trovato)){
		trovato->setProxFratello(new Nodo<T>(e_, trovato, NULL, NULL));
	}else{
		nodo fratello = getProxFratello(trovato);
		while(!isUltimoFratello(fratello)){
			fratello = getProxFratello(fratello);
		}
		fratello->setProxFratello(new Nodo<T>(e_, fratello->getPadre(), NULL, NULL));
	}
	this->num_nodi++;
}

template<class T> void LinkedTree<T>::cancNodo(nodo n) {
	if(isFoglia(n)){
		nodo padre = getPadre(n);
		/* Se il nodo da eliminare è il primo figlio del padre */
		if(leggiNodo(padre->getPrimoFiglio()) == leggiNodo(n)){
			padre->setPrimoFiglio(padre->getPrimoFiglio()->getProxFratello());
		}else{
			/* Altrimenti il nodo da eliminare è un figlio generico */
			nodo precFiglio = padre->getPrimoFiglio();
			nodo currFiglio = precFiglio;
			while(!isUltimoFratello(currFiglio)){
				if(leggiNodo(currFiglio) == leggiNodo(n)){
					break;
				}
				precFiglio = currFiglio;
				currFiglio = getProxFratello(currFiglio);
			}
			/* Se il nodo da eliminare è l'ultimo */
			if(currFiglio->getProxFratello() == NULL){
				delete currFiglio;
				precFiglio->setProxFratello(NULL);
			}else{
				/* Il nodo da eliminare è in posizione centrale */
				precFiglio->setProxFratello(currFiglio->getProxFratello());
				delete currFiglio;
			}
		}
	}else{
		/* Se il nodo da eliminare è la radice, elimina l'albero */
		if(leggiNodo(getRadice()) == leggiNodo(n)){
			cancAlbero();
		}else{
			/* Se il nodo da eliminare è in posizione centrale ed ha dei figli */
			nodo padre = n;
			nodo figlio = getPrimoFiglio(padre);
			nodo proxFratello = padre->getPadre()->getPrimoFiglio()->getProxFratello();
			getPadre(padre)->setPrimoFiglio(getPrimoFiglio(padre));
			/* Imposta i figli del padre come figlio del nonno */
			while(!isUltimoFratello(figlio)){
				figlio->setPadre(getPadre(padre));
				figlio = getProxFratello(figlio);
			}
			/* Imposto il fratello dell'ultimo figlio come il secondo figlio del padre */
			figlio->setProxFratello(proxFratello);
			delete padre;
		}
 	}
	this->num_nodi--;
}

template<class T> void LinkedTree<T>::cancNodo(const tipoelem& e){
	LinkedList<nodo> coda;
	coda.enqueue(getRadice());
	nodo trovato = getRadice();
	while(!coda.isEmpty()){
		nodo currNodo = coda.dequeue();
		if(leggiNodo(currNodo) == e){
			trovato = currNodo;
			break;
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
	cancNodo(trovato);
}

template<class T> void LinkedTree<T>::cancSottoAlbero(nodo n){
	this->num_nodi -= this->getNumFigli(n);
	n->setPrimoFiglio(NULL);
}

template<class T> void LinkedTree<T>::cancSottoAlbero(const tipoelem& e){
	LinkedList<nodo> coda;
	coda.enqueue(getRadice());
	nodo trovato = getRadice();
	while(!coda.isEmpty()){
		nodo currNodo = coda.dequeue();
		if(leggiNodo(currNodo) == e){
			trovato = currNodo;
			break;
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
	cancSottoAlbero(trovato);
}


template<class T> void LinkedTree<T>::cancAlbero() {
	this->radice = NULL;
	this->num_nodi = 0;
}

template<class T> LinkedTree<T>::~LinkedTree() {
	this->radice = NULL;
	this->num_nodi = 0;
}


#endif /* LINKEDTREE_H_ */
