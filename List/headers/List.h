/*
 * Interfaccia List.h
 *  Created on: 4 giu 2019
 *      Author: mrOranger
 */
#ifndef LIST_H_
#define LIST_H_

#include <iostream>

using namespace std;

template<class T, class P> class List{

	public:
		typedef T tipoelem;
		typedef P posizione;

		virtual bool isEmpty() const = 0;
		virtual int getLength() const = 0;
		virtual posizione getHead() const = 0;
		virtual posizione getTail() const = 0;
		virtual void insElem(posizione, const tipoelem&) = 0;
		virtual void insElem(const tipoelem&) = 0;
		virtual void cancElem(const tipoelem&) = 0;
		virtual void cancElemByIndex(posizione) = 0;
		virtual void cancLista() = 0;
		virtual void push(const tipoelem&) = 0;
		virtual tipoelem pop() = 0;
		virtual void enqueue(const tipoelem&) = 0;
		virtual tipoelem dequeue() = 0;
		virtual tipoelem getMax() const;
		virtual tipoelem getMin() const;
		virtual bool isPresent(const tipoelem&) const = 0;
		virtual int getIndex(const tipoelem&) const = 0;
		virtual tipoelem getElemUsingIndex(int) const = 0;
		virtual posizione getPosition(const tipoelem&) const = 0;
		virtual tipoelem getElem(posizione) const = 0;
		virtual tipoelem* toArray() const = 0;
		friend bool operator==(const List<T,P>& list, const List<T,P>& list_){
			if(list.getLength() != list_.getLength()){
				return false;
			}else{
				for(typename List<T, P>::posizione pos = list.getHead(); !list.endList(pos); pos = list.getNext(pos)){
					if(list.readList(pos) != list_.readList(pos)){
						return false;
					}
				}
				return true;
			}
		}
		friend bool operator!=(const List<T,P>& list, const List<T,P>& list_){
			if(list.getLength() == list_.getLength()){
				return false;
			}else{
				for(typename List<T, P>::posizione pos = list.getHead(); !list.endList(pos); pos = list.getNext(pos)){
					if(list.readList(pos) == list_.readList(pos)){
						return false;
					}
				}
				return true;
			}
		}
		friend bool operator<(const List<T,P>& list, const List<T,P>& list_){
			if(list.getLength() >= list_.getLength()){
				return false;
			}else{
				for(typename List<T, P>::posizione pos = list.getHead(); !list.endList(pos); pos = list.getNext(pos)){
					if(list.readList(pos) > list_.readList(pos)){
						return false;
					}
				}
				return true;
			}
		}
		friend bool operator>(const List<T,P>& list, const List<T,P>& list_){
			if(list.getLength() >= list_.getLength()){
				return false;
			}else{
				for(typename List<T, P>::posizione pos = list.getHead(); !list.endList(pos); pos = list.getNext(pos)){
					if(list.readList(pos) > list_.readList(pos)){
						return false;
					}
				}
				return true;
			}
		}
		friend bool operator<=(const List<T,P>& list, const List<T,P>& list_){
			if(list.getLength() > list_.getLength()){
				return false;
			}else{
				for(typename List<T, P>::posizione pos = list.getHead(); !list.endList(pos); pos = list.getNext(pos)){
					if(list.readList(pos) <= list_.readList(pos)){
						return false;
					}
				}
				return true;
			}
		}
		friend bool operator>=(const List<T,P>& list, const List<T,P>& list_){
			if(list.getLength() < list_.getLength()){
				return false;
			}else{
				for(typename List<T, P>::posizione pos = list.getHead(); !list.endList(pos); pos = list.getNext(pos)){
					if(list.readList(pos) >= list_.readList(pos)){
						return false;
					}
				}
				return true;
			}
		}
		friend ostream& operator<<(ostream& os, const List<T, P>& list){
			os << "Lunghezza della lista: " << list.getLength() << endl;
			os << "[ ";
			typename List<T, P>::posizione pos = list.getHead();
			while(!list.endList(pos)){
				cout << list.readList(pos) << " ";
				pos = list.getNext(pos);
			}
			os << " ]" << endl;
			return os;
		}
		void operator=(List<T, P>& list);
	protected:
		int MAX_SIZE = 10000;
		posizione head;
		posizione tail;
		int length;
		int max_size;
		virtual tipoelem readList(posizione) const = 0;
		virtual void writeList(posizione, const tipoelem&) = 0;
		virtual posizione getPrev(posizione) const = 0;
		virtual posizione getNext(posizione) const = 0;
		virtual bool endList(posizione) const = 0;
		virtual posizione getFirst() const = 0;
		virtual posizione getLast() const = 0;
};

template<class T, class K> typename List<T, K>::tipoelem List<T, K>::getMax() const {
	tipoelem currMax = this->readList(this->getHead());
	for(posizione pos = this->getHead(); !this->endList(pos); pos = this->getNext(pos)){
		if(this->readList(pos) >= currMax){
			currMax = this->readList(pos);
		}
	}
	return currMax;
}

template<class T, class K> typename List<T, K>::tipoelem List<T, K>::getMin() const {
	tipoelem currMin = this->readList(this->getHead());
	for(posizione pos = this->getHead(); !this->endList(pos); pos = this->getNext(pos)){
		if(this->readList(pos) <= currMin){
			currMin = this->readList(pos);
		}
	}
	return currMin;
}


#endif /* LIST_H_ */
