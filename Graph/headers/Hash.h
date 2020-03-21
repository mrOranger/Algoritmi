/*
 * Hash.h
 *
 *  Created on: 24 giu 2019
 *      Author: edoar
 */

#ifndef HEADERS_HASH_H_
#define HEADERS_HASH_H_


#include <iostream>

using std::string;

template<class T> class Hash {
	public: size_t operator()(const T key) const;
};

template<> class Hash<string>{
	public: size_t operator()(const string key) const {
		unsigned int hashValue = 0;
		int length = (int)key.length();
		for(int i = 0; i < length; i++){
			hashValue = 5*hashValue + (int)key.at(i);
		}
		return (size_t)hashValue;
	}
};

template<> class Hash<int>{
	public: size_t operator()(const int key) const {
		return key;
	}
};

template<> class Hash<char>{
	public: size_t operator()(const char key) const {
		return (size_t)key;
	}
};


#endif /* HEADERS_HASH_H_ */
