/*
 * Cella.h
 *
 *  Created on: 12 giu 2019
 *      Author: edoar
 */

#ifndef CELLA_H_
#define CELLA_H_

#include <iostream>

using namespace std;

template<class T> class Cella {
	private:
		bool used;
		T elem;
	public:
		Cella();
		Cella(T);
		void setElem(T);
		T getElem() const;
		bool isUsed() const;
		void cancCella();
		template<class K> friend ostream& operator<<(ostream&, const Cella<K>&);
		template<class K> friend bool operator== (const Cella<K>&, const Cella<K>&);
		template<class K> friend bool operator> (const Cella<K>&, const Cella<K>&);
		template<class K> friend bool operator< (const Cella<K>&, const Cella<K>&);
		template<class K> friend bool operator>= (const Cella<K>&, const Cella<K>&);
		template<class K> friend bool operator<= (const Cella<K>&, const Cella<K>&);
		void operator=(const Cella<T>&);
};

template<class T> Cella<T>::Cella(){
	this->used = false;
}

template<class T> Cella<T>::Cella(T elem){
	this->elem = elem;
	this->used = true;
}

template<class T> void Cella<T>::setElem(T elem){
	if(used == false){
		used = true;
	}
	this->elem = elem;
}

template<class T> T Cella<T>::getElem() const {
	return this->elem;
}

template<class T> bool Cella<T>::isUsed() const {
	return this->used;
}

template<class T> void Cella<T>::cancCella() {
	this->used = false;
}

template<class T> ostream& operator<<(ostream& os, const Cella<T>& cella){
	return os << cella.getElem() << endl;
}

template<class T> bool operator==(const Cella<T>& c, const Cella<T>& c_){
	return (c.getElem() == c_.getElem());
}

template<class T> bool operator>(const Cella<T>& c, const Cella<T>& c_){
	return (c.getElem() > c_.getElem());
}

template<class T> bool operator<(const Cella<T>& c, const Cella<T>& c_){
	return (c.getElem() < c_.getElem());
}

template<class T> bool operator>=(const Cella<T>& c, const Cella<T>& c_){
	return (c.getElem() >= c_.getElem());
}

template<class T> bool operator<=(const Cella<T>& c, const Cella<T>& c_){
	return (c.getElem() <= c_.getElem());
}

template<class T> void Cella<T>::operator=(const Cella<T>& cella){
	this->elem = cella.getElem();
}

#endif /* CELLA_H_ */
