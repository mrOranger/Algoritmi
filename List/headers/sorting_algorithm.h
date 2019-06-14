/*
 * Classe concreta sorting_algorithm.h contenente i seguenti algoritmi di ordinamento:
 * 1.Bubble sort
 * 2.Selection sort
 * 3.Insertion sort
 * 4.Quick sort
 *
 *  Created on: 11 giu 2019
 *      Author: edoar
 */

#ifndef SORTING_ALGORITHM_H_
#define SORTING_ALGORITHM_H_

#include "LinkedList.h"

template <class T> class sorting_algorithm : public LinkedList<T>{

	public:
		typedef T tipoelem;
		typedef typename LinkedList<T>::posizione posizione;
		sorting_algorithm(void);
		sorting_algorithm(T*);
		void printList(void) const;
		void bubble_sort(void);
		void selection_sort(void);
		void insertion_sort(void);
		void quick_sort(int, int);
		~sorting_algorithm(void);
	private:
		void swap(posizione, posizione);
		int partition(int, int);
};

template<class T> sorting_algorithm<T>::sorting_algorithm(void){
	this->head = (posizione)NULL;
	this->tail = (posizione)NULL;
	this->max_size = this->MAX_SIZE;
	this->length = 0;
}

template<class T> sorting_algorithm<T>::sorting_algorithm(T* elems){
	this->head = (posizione)NULL;
	this->tail = (posizione)NULL;
	this->max_size = this->MAX_SIZE;
	this->length = 0;
	this->insElemArray(elems);
}

template<class T> void sorting_algorithm<T>::printList(void) const {
	posizione pos = this->getHead();
	cout << "[";
	while(!this->endList(pos)){
		cout << this->readList(pos) << " ";
		pos = this->getNext(pos);
	}
	cout << "]" << endl;
}

template<class T> void sorting_algorithm<T>::swap(posizione pos, posizione pos_){
	tipoelem app = this->readList(pos);
	pos->setValue(this->readList(pos_));
	pos_->setValue(app);
}

template<class T> void sorting_algorithm<T>::bubble_sort(void){
	int last = this->getLength();
	int n = this->getLength() - 1;
	while(last > 0){
		last = 0;
		posizione prec = this->getHead();
		posizione curr = this->getNext(prec);
		for(int i = 0; i < n; i++){
			if(this->readList(prec) > this->readList(curr)){
				this->swap(prec, curr);
				last = i;
			}
			prec = this->getNext(prec);
			curr = this->getNext(curr);
		}
		n = last;
	}
}

template<class T> void sorting_algorithm<T>::selection_sort(void){
	int minIndex = 0;
	for(int i = 0; i < (this->getLength() - 1); i++){
		minIndex = i;
		for(int j = (i + 1); j < this->getLength(); j++){
			if(this->getElemUsingIndex(j) < this->getElemUsingIndex(minIndex)){
				minIndex = j;
			}
		}
		if(minIndex != i){
			this->swap(this->getPosition(this->getElemUsingIndex(i)), this->getPosition(this->getElemUsingIndex(minIndex)));
		}
	}
}

template<class T> void sorting_algorithm<T>::insertion_sort(void){
	LinkedList<T> list(this->MAX_SIZE);
	for(posizione pos = this->getHead(); !this->endList(pos); pos = this->getNext(pos)){
		list.insElem(this->readList(pos));
	}
	this->head = list.getHead();
	this->tail = list.getTail();
	this->length = list.getLength();
}

template<class T> void sorting_algorithm<T>::quick_sort(int first, int last){
	if(first >= last){
		return;
	}
	int pivot = partition(first, last);
	quick_sort(first, pivot - 1);
	quick_sort(pivot + 1, last);
}

template<class T> int sorting_algorithm<T>::partition(int first, int last){
	int k = first + 1;
	for(int i = first + 1; i <= last; i++){
		if(this->getElemUsingIndex(i) < this->getElemUsingIndex(first)){
			swap(this->getPosition(this->getElemUsingIndex(i)), this->getPosition(this->getElemUsingIndex(k++)));
		}
	}
	swap(this->getPosition(this->getElemUsingIndex(first)), this->getPosition(this->getElemUsingIndex(k - 1)));
	return k - 1;
}

template<class T> sorting_algorithm<T>::~sorting_algorithm(void){
	this->head = NULL;
	this->tail = NULL;
	this->length = 0;
}



#endif /* SORTING_ALGORITHM_H_ */
