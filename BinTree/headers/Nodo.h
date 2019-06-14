#ifndef NODO_H
#define NODO_H

#include <iostream>

using namespace std;

template<class T> class Nodo {

	private:
		Nodo<T>* left;
		Nodo<T>* right;
		Nodo<T>* father;
		T elem;
	public:
		Nodo();
		Nodo(const T&);
		Nodo(Nodo<T>*, Nodo<T>*, Nodo<T>*);
		Nodo(const T&, Nodo<T>*, Nodo<T>*, Nodo<T>*);
		Nodo<T>* getLeft() const;
		Nodo<T>* getRight() const;
		Nodo<T>* getFather() const;
		T getElem() const;
		void setLeft(Nodo<T>*);
		void setRight(Nodo<T>*);
		void setElem(const T& elem);
		void setFather(Nodo<T>*);
};

template<class T> Nodo<T>::Nodo(){
	this->left = NULL;
	this->right = NULL;
	this->father = NULL;
}

template<class T> Nodo<T>::Nodo(const T& elem){
	this->left = NULL;
	this->right = NULL;
	this->father = NULL;
	this->elem = elem;
}

template<class T> Nodo<T>::Nodo(Nodo<T>* left, Nodo<T>* right, Nodo<T>* father){
	this->left = left;
	this->right = right;
	this->father = father;
}

template<class T> Nodo<T>::Nodo(const T& elem, Nodo<T>* left, Nodo<T>* right, Nodo<T>* father){
	this->left = left;
	this->right = right;
	this->father = father;
	this->elem = elem;
}

template<class T> Nodo<T>* Nodo<T>::getRight() const {
	return this->right;
}

template<class T> Nodo<T>* Nodo<T>::getLeft() const {
	return this->left;
}

template<class T> Nodo<T>* Nodo<T>::getFather() const {
	return this->father;
}

template<class T> T Nodo<T>::getElem() const {
	return this->elem;
}

template<class T> void Nodo<T>::setElem(const T& elem){
	this->elem = elem;
}

template<class T> void Nodo<T>::setRight(Nodo<T>* right){
	this->right = right;
}

template<class T> void Nodo<T>::setLeft(Nodo<T>* left){
	this->left = left;
}

template<class T> void Nodo<T>::setFather(Nodo<T>* father){
	this->father = father;
}

#endif
