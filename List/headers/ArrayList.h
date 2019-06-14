/*
 * Classe concreta ArrayList.h, lista con vettore
 *
 *  Created on: 4 giu 2019
 *      Author: mrOranger
 */

#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_

#include <iostream>
#include "List.h"

using namespace std;

template<class T> class ArrayList : public List<T, int>{

	typedef typename List<T, int>::posizione posizione;
	typedef typename List<T, int>::tipoelem tipoelem;

	protected:
		tipoelem* elems;
		tipoelem readList(posizione) const;
		void writeList(posizione, const tipoelem&);
		posizione getPrev(posizione) const;
		posizione getNext(posizione) const;
		bool endList(posizione) const;
		posizione getFirst() const;
		posizione getLast() const;

	public:
		ArrayList();
		ArrayList(int);
		ArrayList(T[]);
		ArrayList(int, T[]);
		bool isEmpty() const;
		int getLength() const;
		posizione getHead() const;
		posizione getTail() const;
		void insElem(posizione, const tipoelem&);
		void insElem(const tipoelem&);
		void cancElem(const tipoelem&);
		void cancElemByIndex(posizione);
		void cancLista();
		void push(const tipoelem&);
		tipoelem pop();
		void enqueue(const tipoelem&);
		tipoelem dequeue();
		bool isPresent(const tipoelem&) const;
		int getIndex(const tipoelem&) const;
		posizione getPosition(const tipoelem&) const;
		tipoelem getElem(posizione) const;
		tipoelem getElemUsingIndex(int) const;
		tipoelem* toArray() const;
		~ArrayList();
};

template<class T> ArrayList<T>::ArrayList(){
	this->max_size = this->MAX_SIZE;
	this->length = 0;
	this->tail = this->head = 1; /* Testa e coda coincidono */
	this->elems = new T[this->max_size];
}

template<class T> ArrayList<T>::ArrayList(int max_size){
	this->max_size = max_size;
	this->length = 0;
	this->tail = this->head = 1;
	this->elems = new T[this->max_size];
}

template<class T> ArrayList<T>::ArrayList(T elems[]){
	this->max_size = this->MAX_SIZE;
	this->elems = new T[this->max_size];
	for(int i = 0; elems[i + 1] != NULL; i++){
		if(this->getLength() < (i + 1)){
			this->elems[i] = elems[i];
			this->length++;
		}
	}
	this->head = 1;
	this->tail = this->length;
}

template<class T> ArrayList<T>::ArrayList(int max_size, T elems[]){
	this->max_size = max_size;
	this->elems = new T[this->max_size];
	for(int i = 0; elems[i] != NULL; i++){
		if(this->getLength() < (i + 1)){
			this->elems[i] = elems[i];
			this->length++;
		}
	}
	this->head = 1;
	this->tail = this->length;
}

template<class T> bool ArrayList<T>::isEmpty() const {
	return (this->length == 0);
}

template<class T> int ArrayList<T>::getLength() const {
	return (this->length);
}

template<class T> typename ArrayList<T>::tipoelem ArrayList<T>::readList(posizione pos) const {
	if(pos > 0 && pos < this->getLength() + 1){
		return (this->elems[pos - 1]);
	}
}

template<class T> void ArrayList<T>::writeList(posizione pos, const tipoelem& elem) {
	if(this->isEmpty()){
		/* Se la lista è vuota posso scrivere sola nella prima posizione */
		if(pos == 1){
			this->elems[pos - 1] = elem;
		}
	}else{
		if((pos > 0) && (pos < this->getLength() + 1)){
			this->elems[pos - 1] = elem;
		}
	}
}

template<class T> typename ArrayList<T>::posizione ArrayList<T>::getPrev(posizione pos) const {
	if((pos > 1) && (pos < this->length + 1)){
		return (pos - 1);
	}else{
		return (pos);
	}
}

template<class T> typename ArrayList<T>::posizione ArrayList<T>::getNext(posizione pos) const {
	if((pos > 0) && (pos < (this->length + 1))){
		return (pos + 1);
	}else{
		return (pos);
	}
}

template<class T> bool ArrayList<T>::endList(posizione pos) const {
	return (pos == (this->getLength() + 1));
}

template<class T> typename ArrayList<T>::posizione ArrayList<T>::getFirst() const {
	return (posizione)1;
}

template<class T> typename ArrayList<T>::posizione ArrayList<T>::getLast() const {
	if(this->isEmpty()){
		return 1;
	}else{
		return (posizione)this->length;
	}
}

template<class T> typename ArrayList<T>::posizione ArrayList<T>::getHead() const {
	return this->head;
}

template<class T> typename ArrayList<T>::posizione ArrayList<T>::getTail() const {
	return this->tail;
}

template<class T> void ArrayList<T>::insElem(posizione pos, const tipoelem& elem){
	if(this->isEmpty()){
		/* Unica posizione valida = testa */
		if((pos == this->getHead())){
			this->elems[pos - 1] = elem;
		}
	}else{
		if((pos != this->head) && (pos == this->tail)){
			this->elems[pos] = elem;
		}else{
			for(int i = this->getLength(); i > (pos-1); i--){
				this->elems[i] = this->elems[i-1];
			}
			this->writeList(pos, elem);
		}
	}
	this->length++;
	this->tail = this->length;
}

template<class T> void ArrayList<T>::insElem(const tipoelem& elem){
	if(this->getLength() < this->MAX_SIZE){
		if(this->isEmpty()){
			this->elems[0] = elem;
		}else{
			if((this->getLength() == 1)){
				if(this->readList(this->getHead()) > elem){
					this->elems[1] = this->readList(this->getHead());
					this->elems[0] = elem;
				}else{
					this->elems[1] = elem;
				}
			}else{
				posizione curr = this->getHead();
				while((this->readList(curr) < elem) && !this->endList(curr)){
					curr = curr + 1;
				}
				for(int index = (this->length); index > (curr - 1); index--){
					this->elems[index] = this->elems[index-1];
				}
				this->elems[curr - 1] = elem;
			}
		}
		this->length++;
		this->tail = this->length;
	}
}

template<class T> void ArrayList<T>::cancElem(const tipoelem& elem){
	if(!this->isEmpty()){
		posizione curr;
		if(elem == this->readList(this->getHead())){
			curr = this->getHead();
			for(int i = (curr - 1); i < this->getLength(); i++){
				this->elems[i] = this->elems[i+1];
			}
			this->length--;
			this->tail = this->getTail() - 1;
			return;
		}
		if(elem == this->readList(this->getTail())){
			this->length--;
			this->tail = this->getTail() - 1;
			return;
		}
		curr = this->getHead();
		while((this->readList(curr) != elem) && !this->endList(curr)){
			curr = curr + 1;
		}
		for(int index = (curr -1); index < this->getLength(); index++){
			this->elems[index] = this->elems[index + 1];
		}
		this->length--;
		this->tail = this->getTail() - 1;
	}
}

template<class T> void ArrayList<T>::cancElemByIndex(posizione pos){
	if(!this->isEmpty()){
		if(pos > 0 && pos < (this->getLength() + 1)){
			for(int i = (pos - 1); i < this->getLength(); i++){
				this->elems[i] = this->elems[i + 1];
			}
			this->length--;
			this->tail = this->getTail() - 1;
		}
	}
}

template<class T> void ArrayList<T>::cancLista() {
	delete this->elems;
	this->tail = this->head;
	this->length = 0;
}

template<class T> void ArrayList<T>::push(const tipoelem& elem){
	if(this->isEmpty()){
		this->elems[this->getHead() - 1] = elem;
		this->length++;
		this->tail = this->getLength();
	}else{
		if(this->getLength() < this->MAX_SIZE){
			for(int i = (this->length + 1); i > 0; i--){
				this->elems[i] = this->elems[i - 1];
			}
			this->elems[0] = elem;
			this->length++;
			this->tail = this->getLength();
		}
	}
}

template<class T> typename ArrayList<T>::tipoelem ArrayList<T>::pop() {
	if(!this->isEmpty()){
		for(int i = 0; i < (this->getLength() - 1); i++){
			this->elems[i] = this->elems[i+1];
		}
		this->length--;
		this->tail = this->length;
	}
}

template<class T> void ArrayList<T>::enqueue(const tipoelem& elem){
	if(this->getLength() < this->MAX_SIZE){
		this->elems[this->getTail()] = elem;
		this->length++;
		this->tail = this->length;
	}
}

template<class T> typename ArrayList<T>::tipoelem ArrayList<T>::dequeue(){
	if(!this->isEmpty()){
		tipoelem oldhead = this->readList(this->getHead());
		for(int i = 0; i < (this->getLength() - 1); i++){
			this->elems[i] = this->elems[i+1];
		}
		this->length--;
		this->tail = this->length;
		return oldhead;
	}else{
		return -1;
	}
}

template<class T> bool ArrayList<T>::isPresent(const tipoelem& elem) const {
	if(this->isEmpty()){
		return false;
	}else{
		for(int i = 0; i < this->getLength(); i++){
			if(this->elems[i] == elem){
				return true;
			}
		}
	}
	return false;
}

template<class T> int ArrayList<T>::getIndex(const tipoelem& elem) const {
	if(this->isEmpty()){
		return -1;
	}else{
		for(int i = 0; i < this->getLength(); i++){
			if(this->elems[i] == elem){
				return i;
			}
		}
	}
	return -1;
}

template<class T> typename ArrayList<T>::posizione ArrayList<T>::getPosition(const tipoelem& elem) const {
	if(this->isEmpty()){
		return -1;
	}else{
		for(posizione pos = this->getHead(); !this->endList(pos); pos = this->getNext(pos)){
			if(this->readList(pos) == elem){
				return pos;
			}
		}
	}
	return -1;
}

template<class T> typename ArrayList<T>::tipoelem ArrayList<T>::getElem(posizione pos) const {
	if(this->isEmpty()){
		return -1;
	}else{
		if((pos > (this->getHead() - 1)) && (pos < (this->getLength() + 1))){
			return (this->readList(pos));
		}
	}
	return -1;
}

template<class T> typename ArrayList<T>::tipoelem ArrayList<T>::getElemUsingIndex(int index) const {
	if(this->isEmpty()){
		return -1;
	}else{
		if((index > 0) && (index < this->getLength())){
			return this->elems[index];
		}
	}
	return -1;
}


template<class T> typename ArrayList<T>::tipoelem* ArrayList<T>::toArray() const {
	if(this->isEmpty()){
		return new tipoelem[0];
	}else{
		tipoelem* array = new tipoelem[this->getLength()];
		for(posizione pos = this->getHead(); !this->endList(pos); pos = this->getNext(pos)){
			array[pos - 1] = this->readList(pos);
		}
		return array;
	}
}

template<class T> ArrayList<T>::~ArrayList(){
	this->length = 0;
	this->tail = this->head = 1;
	delete this->elems;
}

#endif /* ARRAYLIST_H_ */
