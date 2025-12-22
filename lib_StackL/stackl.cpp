#pragma once

#include <iostream>
#include <initializer_list>
#include "../lib_list/list.h"

#define STANDARD_CAPACITY 15

template<class T>
class Stack {
	List<T> _data;

public:
	Stack();
	Stack(int);
	Stack(List<T>&);
	Stack(std::initializer_list<T>);
	Stack(Stack<T>&);

	void push(T val);
	void pop();
	inline T top();
	inline bool is_empty() noexcept;
	inline bool is_full() noexcept;
	void clear() noexcept;
};

template <class T>
Stack<T>::Stack() {
	// List не имеет метода reserve, поэтому ничего не делаем
}

template <class T>
Stack<T>::Stack(int size) {
	// List не имеет метода reserve, поэтому просто игнорируем размер
	// Можно было бы добавить элементы, но это противоречит семантике стека
	(void)size; // Подавляем предупреждение о неиспользуемом параметре
}

template <class T>
Stack<T>::Stack(List<T>& list) {
	// Копируем элементы из списка в стек
	// Обратите внимание: поскольку в стеке вершина - последний добавленный элемент,
	// а в List push_back добавляет в конец, нам нужно скопировать в обратном порядке
	for (auto it = list.begin(); it != list.end(); ++it) {
		_data.push_front(*it); // Используем push_front для сохранения порядка
	}
}

template <class T>
Stack<T>::Stack(std::initializer_list<T> init_list) {
	// Добавляем элементы из initializer_list
	for (const auto& item : init_list) {
		_data.push_front(item);
	}
}

template <class T>
Stack<T>::Stack(Stack<T>& other) {
	// Копируем элементы из другого стека
	// Нужно сохранить порядок элементов
	auto it = other._data.begin();
	while (it != other._data.end()) {
		_data.push_front(*it);
		++it;
	}
}

template <class T>
void Stack<T>::push(T val) {
	if (is_full()) throw std::logic_error("Stack is full");
	_data.push_front(val); // Добавляем в начало для эффективности
}

template <class T>
void Stack<T>::pop() {
	if (is_empty()) throw std::logic_error("Stack is empty");
	_data.pop_front(); // Удаляем из начала
}

template <class T>
T Stack<T>::top() {
	if (is_empty()) throw std::logic_error("Stack is empty");

	// Получаем первый элемент (вершину стека)
	auto it = _data.begin();
	if (it != _data.end()) {
		return *it;
	}

	throw std::logic_error("Stack is empty");
}

template <class T>
inline bool Stack<T>::is_empty() noexcept {
	return _data.is_empty();
}

template <class T>
inline bool Stack<T>::is_full() noexcept {
	// List не имеет ограничения по размеру, поэтому стек никогда не будет полным
	// Если нужно ограничение, его можно добавить отдельно
	return false;
}

template <class T>
void Stack<T>::clear() noexcept {
	// Очищаем список, удаляя все элементы
	while (!_data.is_empty()) {
		_data.pop_front();
	}
}