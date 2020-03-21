/*
 * Nodo.h
 *
 *  Created on: 27 giu 2019
 *      Author: edoar
 */

#ifndef HEADERS_NODO_H_
#define HEADERS_NODO_H_

#include <iostream>

using std::ostream;

template<class N> class Nodo {

	private:
		unsigned int weight;
		unsigned int sumWeight;
		N prev;
	public:
		Nodo(){
			this->weight = 0;
			this->sumWeight = 0;
		}

		Nodo(unsigned int weight, unsigned int sum, N prev){
			this->weight = weight;
			this->sumWeight = sum;
			this->prev = prev;
		}

		unsigned int getWeight() const{
			return this->weight;
		}

		unsigned int getSumWeight() const{
			return this->sumWeight;
		}

		N getPrev() const{
			return this->prev;
		}

		void setWeight(const unsigned int& weight){
			this->weight = weight;
		}

		void setSumWeight(const unsigned int& sum){
			this->sumWeight = sum;
		}

		void setPrev(const N& prev){
			this->prev = prev;
		}

		bool operator==(const Nodo<N>& n){
			return (this->getSumWeight() == n.getSumWeight());
		}

		bool operator!=(const Nodo<N>& n){
			return (this->getSumWeight() != n.getSumWeight());
		}

		bool operator>=(const Nodo<N>& n){
			return (this->getSumWeight() >= n.getSumWeight());
		}

		bool operator<=(const Nodo<N>& n){
			return (this->getSumWeight() <= n.getSumWeight());
		}

		bool operator<(const Nodo<N>& n){
			return (this->getSumWeight() < n.getSumWeight());
		}

		bool operator>(const Nodo<N>& n){
			return (this->getSumWeight() > n.getSumWeight());
		}

		void operator=(const Nodo<N>& n){
			this->prev = n.getPrev();
			this->sumWeight = n.getSumWeight();
			this->weight = n.getWeight();
		}

		friend ostream& operator<<(ostream& os, const Nodo<N>& n){
			return os << n.getSumWeight() << " ";
		}
};



#endif /* HEADERS_NODO_H_ */
