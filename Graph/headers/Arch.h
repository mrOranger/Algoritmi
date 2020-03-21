/*
 * Arch.h
 *
 *  Created on: 24 giu 2019
 *      Author: edoar
 */

#ifndef HEADERS_ARCH_H_
#define HEADERS_ARCH_H_

#include <iostream>

using std::ostream;

class Arch{

	private:
		unsigned int node_1;
		unsigned int node_2;
		unsigned int weight;
	public:
		Arch();
		Arch(unsigned int, unsigned int, unsigned int);
		unsigned int getFirstNode() const;
		unsigned int getSecondNode() const;
		unsigned int getWeight() const;
		void setFirstNode(unsigned int);
		void setSecondNode(unsigned int);
		void setWeight(unsigned int);
		friend ostream& operator<<(ostream& os, const Arch& a){
			return os << "(" << a.getFirstNode() << ", " << a.getSecondNode() << ", " << a.getWeight() << ")";
		}
		friend bool operator==(const Arch& a1, const Arch& a2){
			if((a1.getFirstNode() == a2.getFirstNode()) && (a1.getSecondNode() == a2.getSecondNode())){
				return (a1.getWeight() == a2.getWeight());
			}else{
				return false;
			}
		}
		friend bool operator>(const Arch& a1, const Arch& a2){
			if((a1.getFirstNode() == a2.getFirstNode()) && (a1.getSecondNode() == a2.getSecondNode())){
				return (a1.getWeight() > a2.getWeight());
			}else{
				return false;
			}
		}
		friend bool operator<(const Arch& a1, const Arch& a2){
			if((a1.getFirstNode() == a2.getFirstNode()) && (a1.getSecondNode() == a2.getSecondNode())){
				return (a1.getWeight() < a2.getWeight());
			}else{
				return false;
			}
		}
		friend bool operator>=(const Arch& a1, const Arch& a2){
			if((a1.getFirstNode() == a2.getFirstNode()) && (a1.getSecondNode() == a2.getSecondNode())){
				return (a1.getWeight() >= a2.getWeight());
			}else{
				return false;
			}
		}
		friend bool operator<=(const Arch& a1, const Arch& a2){
			if((a1.getFirstNode() == a2.getFirstNode()) && (a1.getSecondNode() == a2.getSecondNode())){
				return (a1.getWeight() <= a2.getWeight());
			}else{
				return false;
			}
		}
		void operator=(const Arch& a2){
			this->node_1 = a2.node_1;
			this->node_2 = a2.node_2;
			this->weight = a2.weight;
		}
};

Arch::Arch(){
	this->node_1 = 0;
	this->node_2 = 0;
	this->weight = 0;
}

Arch::Arch(unsigned int n1, unsigned int n2, unsigned int w){
	this->node_1 = n1;
	this->node_2 = n2;
	this->weight = w;
}

unsigned int Arch::getFirstNode() const {
	return this->node_1;
}

unsigned int Arch::getSecondNode() const {
	return this->node_2;
}

unsigned int Arch::getWeight() const {
	return this->weight;
}

void Arch::setFirstNode(unsigned int n1){
	this->node_1 = n1;
}

void Arch::setSecondNode(unsigned int n2){
	this->node_2 = n2;
}

void Arch::setWeight(unsigned int w){
	this->weight = w;
}



#endif /* HEADERS_ARCH_H_ */
