/*
 * Classe concreta Node.h, utilizzata in LinkedList.h
 *  Created on: 5 giu 2019
 *      Author: edoar
 */

#ifndef NODE_H_
#define NODE_H_

#include <iostream>

using namespace std;

template<class T> class Node{

	private:
		typedef T tipoelem;
		typedef Node<tipoelem>* puntatore;
		tipoelem elem;
		puntatore next;
		puntatore prev;
	public:
		Node();
		Node(const T&);
		Node(puntatore, puntatore);
		Node(puntatore, puntatore, const T&);
		tipoelem getValue() const;
		puntatore getNext() const;
		puntatore getPrev() const;
		void setValue(const tipoelem&);
		void setNext(puntatore);
		void setPrev(puntatore);

		bool operator==(const Node<tipoelem>& nodo);
		bool operator!=(const Node<tipoelem>& nodo);
		bool operator<(const Node<tipoelem>& nodo);
		bool operator>(const Node<tipoelem>& nodo);
		bool operator<=(const Node<tipoelem>& nodo);
		bool operator>=(const Node<tipoelem>& nodo);
		void operator=(const Node<tipoelem>& nodo);

		friend ostream& operator<<(ostream& os, const Node<tipoelem>& nodo){
			return os << nodo.getValue() << endl;
		}
};

template<class T> Node<T>::Node(){
	this->next = (void*)NULL;
	this->prev = (void*)NULL;
}

template<class T> Node<T>::Node(const T& elem){
	this->elem = elem;
	this->next = (puntatore)NULL;
	this->prev = (puntatore)NULL;
}

template<class T> Node<T>::Node(puntatore next, puntatore prev){
	this->next = next;
	this->prev = prev;
}

template<class T> Node<T>::Node(puntatore next, puntatore prev, const T& elem){
	this->elem = elem;
	this->next = next;
	this->prev = prev;
}

template<class T> typename Node<T>::tipoelem Node<T>::getValue() const {
	return this->elem;
}

template<class T> typename Node<T>::puntatore Node<T>::getNext() const {
	return this->next;
}

template<class T> typename Node<T>::puntatore Node<T>::getPrev() const {
	return this->prev;
}

template<class T> void Node<T>::setValue(const tipoelem& elem){
	this->elem = elem;
}

template<class T> void Node<T>::setNext(puntatore next){
	this->next = next;
}

template<class T> void Node<T>::setPrev(puntatore prev){
	this->prev = prev;
}

template<class T> bool Node<T>::operator !=(const Node<T>& nodo){
	return (this->getValue() != nodo.getValue());
}

template<class T> bool Node<T>::operator >(const Node<T>& nodo){
	return (this->getValue() > nodo.getValue());
}

template<class T> bool Node<T>::operator <(const Node<T>& nodo){
	return (this->getValue() < nodo.getValue());
}

template<class T> bool Node<T>::operator >=(const Node<T>& nodo){
	return (this->getValue() >= nodo.getValue());
}

template<class T> bool Node<T>::operator <=(const Node<T>& nodo){
	return (this->getValue() <= nodo.getValue());
}

template<class T> bool Node<T>::operator ==(const Node<T>& nodo){
	return (this->getValue() == nodo.getValue());
}

template<class T> void Node<T>::operator =(const Node<T>& nodo){
	this->setValue(nodo.getValue());
}




#endif /* NODE_H_ */
