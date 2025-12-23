//#pragma once
//
//#include <iostream>
//#include <stdexcept>
//#include <initializer_list>
//#include "../lib_list/list.h"
//
//#define STANDARD_SIZE 15
//
//template<class T>
//class Stack {
//    List<T> _data;
//    size_t _capacity;  // вместимость стека
//    size_t _count;     // текущее количество элементов
//
//public:
//    Stack();
//    Stack(size_t capacity);
//    explicit Stack(std::initializer_list<T> init);
//    Stack(const Stack& other);
//
//    // Деструктор (неявно определенный подойдет)
//
//    // Functions //
//    void push(const T& val);  // O(1)
//    void pop();               // O(1)
//    T top() const;
//    bool is_empty() const noexcept;
//    bool is_full() const noexcept;
//    size_t number_of_filled_items() const noexcept;
//    size_t size() const noexcept;  // вместимость
//    size_t count() const noexcept; // текущий размер
//    void clear() noexcept;
//
//    // Operators //
//    bool operator==(const Stack& other) const;
//    bool operator!=(const Stack& other) const;
//    Stack& operator=(const Stack& other);
//};
//
//template <class T>
//Stack<T>::Stack()
//    : _capacity(STANDARD_SIZE),
//    _count(0)
//{
//}
//
//template <class T>
//Stack<T>::Stack(size_t capacity)
//    : _capacity(capacity),
//    _count(0)
//{
//    if (capacity == 0) {
//        throw std::logic_error("Capacity must be positive");
//    }
//}
//
//template <class T>
//Stack<T>::Stack(std::initializer_list<T> init)
//    : _capacity(init.size()),
//    _count(0)
//{
//    for (const auto& item : init) {
//        push(item);
//    }
//}
//
//template <class T>
//Stack<T>::Stack(const Stack& other)
//    : _data(other._data),  // используем конструктор копирования List
//    _capacity(other._capacity),
//    _count(other._count)
//{
//}
//
//template <class T>
//void Stack<T>::push(const T& val) {
//    if (is_full()) {
//        throw std::logic_error("Cannot push to full stack");
//    }
//    _data.push_front(val);  // добавляем в начало для эффективности
//    _count++;
//}
//
//template <class T>
//void Stack<T>::pop() {
//    if (is_empty()) {
//        throw std::logic_error("Cannot pop from empty stack");
//    }
//    _data.pop_front();  // удаляем из начала
//    _count--;
//}
//
//template <class T>
//T Stack<T>::top() const {
//   	if (is_empty()) throw std::logic_error("Stack is empty");
//
//	// Получаем первый элемент (вершину стека)
//	auto it = _data.begin();
//	if (it != _data.end()) {
//		return *it;
//	}
//	throw std::logic_error("Stack is empty");
//}
//
//template <class T>
//bool Stack<T>::is_empty() const noexcept {
//    return _count == 0;
//}
//
//template <class T>
//bool Stack<T>::is_full() const noexcept {
//    return _count >= _capacity;
//}
//
//template <class T>
//size_t Stack<T>::number_of_filled_items() const noexcept {
//    return _count;
//}
//
//template <class T>
//size_t Stack<T>::size() const noexcept {
//    return _capacity;
//}
//
//template <class T>
//size_t Stack<T>::count() const noexcept {
//    return _count;
//}
//
//template <class T>
//void Stack<T>::clear() noexcept {
//   	while (!_data.is_empty()) {
//		_data.pop_front();
//	} 
//    _count = 0;
//}
//
//template <class T>
//bool Stack<T>::operator==(const Stack& other) const {
//    if (_capacity != other._capacity || _count != other._count) {
//        return false;
//    }
//
//    // Сравниваем элементы в двух стеках
//    auto it1 = _data.begin();
//    auto it2 = other._data.begin();
//
//    while (it1 != _data.end() && it2 != other._data.end()) {
//        if (*it1 != *it2) {
//            return false;
//        }
//        ++it1;
//        ++it2;
//    }
//
//    return (it1 == _data.end() && it2 == other._data.end());
//}
//
//template <class T>
//bool Stack<T>::operator!=(const Stack& other) const {
//    return !(*this == other);
//}
//
//template <class T>
//Stack<T>& Stack<T>::operator=(const Stack& other) {
//    if (this != &other) {
//        _data = other._data;  // оператор присваивания List
//        _capacity = other._capacity;
//        _count = other._count;
//    }
//    return *this;
//}
#pragma once

#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include "../lib_list/list.h"

#define STANDARD_CAPACITY 100

template<class T>
class Stack {
    List<T> _data;
    size_t _capacity;  // вместимость стека
    size_t _count;     // текущее количество элементов

public:
    Stack() : _capacity(STANDARD_CAPACITY), _count(0) {}

    explicit Stack(size_t capacity) : _capacity(capacity), _count(0) {
        if (capacity == 0) {
            throw std::logic_error("Capacity must be positive");
        }
    }

    Stack(std::initializer_list<T> init) : _capacity(STANDARD_CAPACITY), _count(0) {
        for (const auto& item : init) {
            push(item);
        }
    }

    Stack(const Stack& other)
        : _data(other._data),
        _capacity(other._capacity),
        _count(other._count)
    {
    }

    // Методы
    void push(const T& val) {
        if (is_full()) {
            throw std::logic_error("Cannot push to full stack");
        }
        _data.push_front(val);
        _count++;
    }

    void pop() {
        if (is_empty()) {
            throw std::logic_error("Cannot pop from empty stack");
        }
        _data.pop_front();
        _count--;
    }

    T top() const {
        if (is_empty()) {
            throw std::logic_error("Cannot get top from empty stack");
        }

        // Получаем первый элемент (вершину стека)
        auto it = _data.begin();
        return *it;
    }

    bool is_empty() const noexcept {
        return _count == 0;
    }

    bool is_full() const noexcept {
        return _count >= _capacity;
    }

    size_t capacity() const noexcept {
        return _capacity;
    }

    size_t count() const noexcept {
        return _count;
    }

    void clear() noexcept {
        // Очищаем список
        while (!_data.is_empty()) {
            _data.pop_front();
        }
        _count = 0;
    }

    Stack& operator=(const Stack& other) {
        if (this != &other) {
            _data = other._data;
            _capacity = other._capacity;
            _count = other._count;
        }
        return *this;
    }
};