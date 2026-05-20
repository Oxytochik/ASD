#pragma once

#include <iostream>
#include <initializer_list>
#include "../lib_TVector/TVector.h"

template <typename TKey, typename TValue>
struct Node {
	std::pair <TKey, TValue> _data;
	Node** _next;
	size_t _level;

	Node(TKey key, TValue value, size_t level) : _level(level){
		_data = { key, value };
		_next = new Node* [level + 1];
		for (size_t i = 0; i <= _level;i++) {
			_next[i] = nullptr;
		}
	} 

	~Node() {
		delete[] _next;
	}

};



template <typename TKey, typename TValue>
class SkipList {
	size_t _max_lvl;
	size_t _lvls;
	Node<TKey, TValue>* _heads;
};