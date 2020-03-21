/*
 * Nodo.h
 *
 *  Created on: 17 giu 2019
 *      Author: edoar
 */

#ifndef NODO_H_
#define NODO_H_

#include <iostream>

template<class T> class Nodo{

	typedef Nodo<T>* nodo;
	typedef T tipoelem;

	private:
		tipoelem elem;
		nodo padre;
		nodo primoFiglio;
		nodo proxFratello;
	public:
		Nodo();
		Nodo(tipoelem);
		Nodo(tipoelem, nodo, nodo, nodo);
		tipoelem getElem() const;
		nodo getPadre() const;
		nodo getPrimoFiglio() const;
		nodo getProxFratello() const;
		void setElem(tipoelem);
		void setPadre(nodo);
		void setPrimoFiglio(nodo);
		void setProxFratello(nodo);
		std::ostream& operator<<(const Nodo<T>&) const;
		bool operator==(const Nodo<T>&) const;
		bool operator<(const Nodo<T>&) const;
		bool operator!=(const Nodo<T>&) const;
		bool operator>(const Nodo<T>&) const;
		void operator=(const Nodo<T>&);
};

template<class T> Nodo<T>::Nodo(){
	this->padre = NULL;
	this->primoFiglio = NULL;
	this->proxFratello = NULL;
}

template<class T> Nodo<T>::Nodo(tipoelem elem){
	this->elem = elem;
	this->padre = NULL;
	this->primoFiglio = NULL;
	this->proxFratello = NULL;
}

template<class T> Nodo<T>::Nodo(tipoelem elem, nodo padre, nodo figlio, nodo fratello){
	this->elem = elem;
	this->padre = padre;
	this->primoFiglio = figlio;
	this->proxFratello = fratello;
}

template<class T> typename Nodo<T>::tipoelem Nodo<T>::getElem() const {
	return this->elem;
}

template<class T> typename Nodo<T>::nodo Nodo<T>::getPadre() const {
	return this->padre;
}

template<class T> typename Nodo<T>::nodo Nodo<T>::getPrimoFiglio() const {
	return this->primoFiglio;
}

template<class T> typename Nodo<T>::nodo Nodo<T>::getProxFratello() const {
	return this->proxFratello;
}

template<class T> void Nodo<T>::setElem(tipoelem elem){
	this->elem = elem;
}

template<class T> void Nodo<T>::setPadre(nodo padre){
	this->padre = padre;
}

template<class T> void Nodo<T>::setPrimoFiglio(nodo figlio){
	this->primoFiglio = figlio;
}

template<class T> void Nodo<T>::setProxFratello(nodo fratello){
	this->proxFratello = fratello;
}

template<class T> std::ostream& Nodo<T>::operator <<(const Nodo<T>& nodo) const{
	return std::cout << nodo.getElem() << std::endl;
}

template<class T> bool Nodo<T>::operator ==(const Nodo<T>& nodo) const {
	return (this->getElem() == nodo.getElem());
}

template<class T> bool Nodo<T>::operator !=(const Nodo<T>& nodo) const {
	return (this->getElem() != nodo.getElem());
}

template<class T> bool Nodo<T>::operator >(const Nodo<T>& nodo) const {
	return (this->getElem() > nodo.getElem());
}

template<class T> bool Nodo<T>::operator <(const Nodo<T>& nodo) const {
	return (this->getElem() < nodo.getElem());
}

template<class T> void Nodo<T>::operator =(const Nodo<T>& nodo) {
	this->setElem(nodo.getElem());
}

#endif /* NODO_H_ */
