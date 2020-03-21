/*
 * Classe concreta LinkedList.h, lista con puntatori
 *
 *  Created on: 5 giu 2019
 *      Author: edoar
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "List.h"
#include "Node.h"

template<class T> class LinkedList : public List<T, Node<T>*>{

	protected:
		typedef typename List<T, Node<T>*>::posizione posizione;
		typedef typename List<T, Node<T>*>::tipoelem tipoelem;

	protected:
		tipoelem readList(posizione) const;
		posizione getPrev(posizione) const;
		posizione getNext(posizione) const;
		bool endList(posizione) const;
		posizione getFirst() const;
		posizione getLast() const;
		void insElemArray(tipoelem[]);
	public:
		LinkedList();
		LinkedList(int);
		LinkedList(tipoelem[]);
		LinkedList(int, tipoelem[]);
		bool isEmpty() const;
		int getLength() const;
		posizione getHead() const;
		posizione getTail() const;
		void writeList(posizione, const tipoelem&);
		void insElem(posizione, const tipoelem&);
		void insElem(const tipoelem&);
		void cancElem(const tipoelem&);
		void cancElemByIndex(posizione);
		void cancLista();
		void push(const tipoelem&);
		tipoelem pop();
		void enqueue(tipoelem);
		tipoelem dequeue();
		bool isPresent(const tipoelem&) const;
		int getIndex(const tipoelem&) const;
		posizione getPosition(const tipoelem&) const;
		tipoelem getElem(posizione) const;
		tipoelem getElemUsingIndex(int) const;
		tipoelem* toArray() const;
		~LinkedList();
};

template<class T> typename LinkedList<T>::tipoelem LinkedList<T>::readList(posizione pos) const{
	return pos->getValue();
}

template<class T> void LinkedList<T>::writeList(posizione pos, const tipoelem& elem){
	pos->setValue(elem);
}

template<class T> typename LinkedList<T>::posizione LinkedList<T>::getNext(posizione pos) const {
	return pos->getNext();
}

template<class T> typename LinkedList<T>::posizione LinkedList<T>::getPrev(posizione pos) const {
	return pos->getPrev();
}

template<class T> bool LinkedList<T>::endList(posizione pos) const {
	return (pos == NULL);
}

template<class T> typename LinkedList<T>::posizione LinkedList<T>::getFirst() const{
	return this->head;
}

template<class T> typename LinkedList<T>::posizione LinkedList<T>::getLast() const{
	return this->tail;
}

template<class T> void LinkedList<T>::insElemArray(tipoelem* elems) {
	for(int i = 0; (elems[i + 1] != (T)NULL); i++){
		if(this->getLength() < this->MAX_SIZE){
			this->enqueue(elems[i]);
		}else{
			return;
		}
	}
}

template<class T> LinkedList<T>::LinkedList(){
	this->head = (posizione)NULL;
	this->tail = (posizione)NULL;
	this->max_size = this->MAX_SIZE;
	this->length = 0;
}

template<class T> LinkedList<T>::LinkedList(int max_size){
	this->head = (posizione)NULL;
	this->tail = (posizione)NULL;
	this->max_size = max_size;
	this->length = 0;
}

template<class T> LinkedList<T>::LinkedList(tipoelem* elems){
	this->head = (posizione)NULL;
	this->tail = (posizione)NULL;
	this->max_size = this->MAX_SIZE;
	this->length = 0;
	this->insElemArray(elems);
}

template<class T> LinkedList<T>::LinkedList(int max_size, tipoelem* elems){
	this->head = (posizione)NULL;
	this->tail = (posizione)NULL;
	this->max_size = max_size;
	this->length = 0;
	this->insElemArray(elems);
}

template<class T> bool LinkedList<T>::isEmpty() const {
	return (this->length == 0);
}

template<class T> int LinkedList<T>::getLength() const {
	return this->length;
}

template<class T> typename LinkedList<T>::posizione LinkedList<T>::getHead() const {
	return this->head;
}

template<class T> typename LinkedList<T>::posizione LinkedList<T>::getTail() const {
	return this->tail;
}

template<class T> void LinkedList<T>::insElem(posizione pos, const tipoelem& elem){
	Node<T>* newNodo = new Node<T>(elem);
	if(this->isEmpty()){
		/* Passo base: Lista vuota */
		newNodo->setNext(NULL);
		newNodo->setPrev(NULL);
		this->head = newNodo;
		this->tail = newNodo;
	}else{
		/* Passo induttivo: Lista composta da un solo elemento */
		if(this->getLength() == 1){
			if(pos == this->getHead()){
				newNodo->setNext(this->getHead());
				newNodo->setPrev(NULL);
				this->head->setPrev(newNodo);
				this->head = newNodo;
			}else{
				this->head->setNext(newNodo);
				newNodo->setNext(NULL);
				newNodo->setPrev(this->getHead());
				this->tail = newNodo;
			}

		}else{
			/* Caso induttivo: Lista composta da n elementi */
			if(pos == this->getTail()){
				newNodo->setPrev(pos);
				newNodo->setNext(NULL);
				pos->setNext(newNodo);
				this->tail = newNodo;
			}else{
				if(pos == this->getHead()){
					newNodo->setPrev(NULL);
					newNodo->setNext(pos);
					pos->setPrev(newNodo);
					this->head = newNodo;
				}else{
					newNodo->setPrev(pos->getPrev());
					newNodo->setNext(pos);
					pos->getPrev()->setNext(newNodo);
					pos->setPrev(newNodo);
				}
			}
		}
	}
	this->length++;
}

template<class T> void LinkedList<T>::insElem(const tipoelem& elem){
	if(this->getLength() < this->MAX_SIZE){
		if(this->isEmpty()){
			this->push(elem);
		}else{
			Node<T>* newNodo = new Node<T>(elem);
			posizione pos = this->getHead();
			while(!this->endList(pos) && (this->readList(pos) < elem)){
				pos = this->getNext(pos);
			}
			if(pos == NULL){
				newNodo->setPrev(this->getTail());
				this->tail->setNext(newNodo);
				this->tail = newNodo;
			}else{
				if(pos == this->getHead()){
					newNodo->setNext(this->getHead());
					this->head->setPrev(newNodo);
					this->head = newNodo;
				}else{
					newNodo->setNext(pos);
					newNodo->setPrev(pos->getPrev());
					pos->getPrev()->setNext(newNodo);
					pos->setPrev(newNodo);
				}
			}
		}
		this->length++;
	}
}

template<class T> void LinkedList<T>::cancElem(const tipoelem& elem){
	if(!this->isEmpty()){
		for(posizione pos = this->getHead(); !this->endList(pos); pos = this->getNext(pos)){
			if(this->readList(pos) == elem){
				if(pos == this->getHead()){
					posizione newHead = pos->getNext();
					posizione oldHead = this->head;
					newHead->setPrev(NULL);
					this->head = newHead;
					delete oldHead;
					break;
				}
				if(pos == this->getTail()){
					posizione newTail = pos->getPrev();
					posizione oldTail = pos;
					newTail->setNext(NULL);
					this->tail = newTail;
					delete oldTail;
					break;
				}else{
					pos->getPrev()->setNext(pos->getNext());
					pos->getNext()->setPrev(pos->getPrev());
					delete pos;
					break;
				}
			}
		}
		this->length--;
	}
}

template<class T> void LinkedList<T>::cancElemByIndex(posizione pos_){
	if(!this->isEmpty()){
		for(posizione pos = this->getHead(); !this->endList(pos); pos = this->getNext(pos)){
			if(pos == pos_){
				if(pos_ == this->getHead()){
					pos->getNext()->setPrev(NULL);
					posizione oldHead = this->head;
					this->head = this->head->getNext();
					delete oldHead;
					break;
				}
				if(pos_ == this->getTail()){
					pos->getPrev()->setNext(NULL);
					posizione oldTail = this->tail;
					this->tail = this->tail->getNext();
					delete oldTail;
					break;
				}else{
					pos->getPrev()->setNext(pos->getNext());
					pos->getNext()->setPrev(pos->getPrev());
					delete pos;
					break;
				}
			}
		}
		this->length--;
	}
}

template<class T> void LinkedList<T>::cancLista() {
	this->head = NULL;
	this->tail = NULL;
	this->length = 0;
}

template<class T> void LinkedList<T>::push(const tipoelem& elem){
	Node<T>* newNodo = new Node<T>(elem);
	if(this->isEmpty()){
		this->tail = newNodo;
		this->head = newNodo;
		this->length = 1;
	}else{
		if(this->getLength() < this->MAX_SIZE){
			newNodo->setPrev(this->tail);
			this->tail->setNext(newNodo);
			this->tail = newNodo;
			this->length++;
		}
	}
}

template<class T> typename LinkedList<T>::tipoelem LinkedList<T>::pop() {
	if(!this->isEmpty()){
		if(this->getLength() == 1){
			tipoelem elem = this->readList(this->tail);
			this->tail = NULL;
			this->head = NULL;
			this->length--;
			return elem;
		}
		tipoelem elem = this->readList(this->tail);
		this->tail = this->tail->getPrev();
		this->tail->setNext(NULL);
		this->length--;
		return elem;
	}
}

template<class T> void LinkedList<T>::enqueue(tipoelem elem){
	Node<T>* newNodo = new Node<T>(elem);
	if(this->isEmpty()){
		this->tail = newNodo;
		this->head = newNodo;
		this->length = 1;
	}else{
		if(this->getLength() < this->MAX_SIZE){
			newNodo->setPrev(this->tail);
			this->tail->setNext(newNodo);
			this->tail = newNodo;
			this->length++;
		}
	}
}

template<class T> typename LinkedList<T>::tipoelem LinkedList<T>::dequeue(){
	if(!this->isEmpty()){
		if(getLength() == 1){
			tipoelem elem = this->readList(this->head);
			this->head = NULL;
			this->tail = NULL;
			this->length--;
			return elem;
		}else{
			tipoelem elem = this->readList(this->head);
			this->head = this->head->getNext();
			this->head->setPrev(NULL);
			this->length--;
			return elem;
		}
	}
}

template<class T> bool LinkedList<T>::isPresent(const tipoelem& elem) const {
	for(posizione pos = this->getHead(); !this->endList(pos); pos = this->getNext(pos)){
		if(this->readList(pos) == elem){
			return true;
		}
	}
	return false;
}

template<class T> int LinkedList<T>::getIndex(const tipoelem& elem) const {
	int index = 0;
	for(posizione pos = this->getHead(); !this->endList(pos); pos = this->getNext(pos)){
		if(this->readList(pos) == elem){
			return (index + 1);
		}
		index++;
	}
	return index;
}

template<class T> typename LinkedList<T>::posizione LinkedList<T>::getPosition(const tipoelem& elem) const {
	for(posizione pos = this->getHead(); !this->endList(pos); pos = this->getNext(pos)){
		if(this->readList(pos) == elem){
			return pos;
		}
	}
	return NULL;
}

template<class T> typename LinkedList<T>::tipoelem LinkedList<T>::getElem(posizione pos_) const {
	for(posizione pos = this->getHead(); !this->endList(pos); pos = this->getNext(pos)){
		if(pos == pos_){
			return this->readList(pos);
		}
	}
}

template<class T> typename LinkedList<T>::tipoelem LinkedList<T>::getElemUsingIndex(int index) const {
	int i = 0;
	for(posizione pos = this->getHead(); !this->endList(pos); pos = this->getNext(pos)){
		if(i == index){
			return this->readList(pos);
		}
		i++;
	}
}


template<class T> typename LinkedList<T>::tipoelem* LinkedList<T>::toArray() const {
	tipoelem* array = new tipoelem[this->getLength()];
	int i = 0;
	for(posizione pos = this->getHead(); !this->endList(pos); pos = this->getNext(pos)){
		array[i] = this->readList(pos);
		i++;
	}
	return array;
}

template<class T> LinkedList<T>::~LinkedList(){
	this->head = NULL;
	this->tail = NULL;
	this->length = 0;
}


#endif /* LINKEDLIST_H_ */
