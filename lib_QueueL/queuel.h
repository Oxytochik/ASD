#include <iostream>
#include <initializer_list>
#include "../lib_List/List.h"

template <class T>
class Queue {
	T* _data;
	int _size;
	//	int _top;
	int _head;
	int _tail;
	int _count;
public:
	Queue();
	Queue(int);
	Queue(std::initializer_list<T> init);
	Queue(Queue& other);

	~Queue();

	int get_size();
	int get_count();

	void push(T);
	void pop();
	inline T tail() const;
	inline bool is_empty()const noexcept;
	inline bool is_full()const noexcept;
	void clear() noexcept;
	T head() const;

};
template <class T>
Queue<T>::Queue()
	:_data(nullptr),
	_size(0),
	_head(0),
	_tail(0),
	_count(0)
{
}

template <class T>
Queue<T>::Queue(int capacity)
	:_size(capacity),
	_head(0),
	_tail(0),
	_count(0)
{
	if (capacity > 0) {
		_data = new T[capacity];
	}
	else {
		_data = nullptr;
	}
}
template <class T>
Queue<T>::Queue(std::initializer_list<T> init) {
	if (init.size() <= 0) {
		throw std::invalid_argument(
			"Queue: Invalid argument - list must not be empty");
	}
	_size = init.size();
	_data = new T[_size];
	_head = 0;
	_count = init.size();

	const T* src = init.begin();
	for (int i = 0; i < _size; i++) {
		_data[i] = src[i];
	}
	_tail = _count % _size;
}

template <class T>
Queue<T>::Queue(Queue<T>& other)
	:_size(other._size),
	_head(other._head),
	_tail(other._tail),
	_count(other._count)
{
	if (_size > 0) {
		_data = new T[_size];
		for (int i = 0; i < _size; i++) {
			_data[i] = other._data[i];
		}
	}
	else {
		_data = nullptr;
	}
}

template <class T>
Queue<T>::~Queue() {
	delete[] _data;
}

template <class T>
int Queue<T>::get_size() {
	return _size;
}
template <class T>
int Queue<T>::get_count() {
	return _count;
}

template <class T>
void Queue<T>::push(T val) {
	if (is_full()) {
		throw std::logic_error("Queue is full");
	}
	else {
		_count++;
		_data[_tail] = val;
		_tail = (_tail + 1) % _size;
	}
}
template <class T>
void Queue<T>::pop() {
	if (is_empty()) {
		throw std::logic_error("Queue is empty");
	}
	else {
		_count--;
		_head = (_head + 1) % _size;
	}
}

template <class T>
inline T Queue<T>::tail() const {
	if (is_empty()) {
		throw std::logic_error("Queue it empty");
	}
	return _data[(_tail + _size - 1) % _size];
}

template <class T>
inline bool Queue<T>::is_empty()const noexcept {
	return _count == 0;
}

template <class T>
inline bool Queue<T>::is_full()const noexcept {
	return _count == _size;
}

template <class T>
void Queue<T>::clear() noexcept {
	_head = 0;
	_tail = 0;
	_count = 0;
}

template <class T>
inline T Queue<T>::head() const {
	if (is_empty()) {
		throw std::logic_error("Queue it empty");
	}
	return _data[_head];
}


