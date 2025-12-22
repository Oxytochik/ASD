#pragma once

#include <iostream>
#include <initializer_list>
#include "../lib_list/list.h"

#define STANDARD_SIZE 15

template<class T>
class Queue {
    List<T> _data;
    int _capacity;    // максимальная вместимость
    int _count;       // количество элементов

public:
    Queue();
    Queue(int capacity);
    Queue(std::initializer_list<T> init);
    Queue(Queue<T>& other);

    int get_capacity() const;
    int get_count() const;

    void push(T val);
    void pop();
    T tail() const;
    bool is_empty() const noexcept;
    bool is_full() const noexcept;
    void clear() noexcept;
    T head() const;
};

template <class T>
Queue<T>::Queue()
    : _capacity(STANDARD_SIZE),
    _count(0)
{
    // List не требует предварительного резервирования памяти
}

template <class T>
Queue<T>::Queue(int capacity)
    : _capacity(capacity > 0 ? capacity : STANDARD_SIZE),
    _count(0)
{
    if (capacity <= 0) {
        throw std::logic_error("Queue capacity must be positive");
    }
}

template <class T>
Queue<T>::Queue(std::initializer_list<T> init)
    : _capacity(init.size() + STANDARD_SIZE),  // Запас памяти: размер + STANDARD_SIZE
    _count(0)
{
    for (const auto& item : init) {
        push(item);
    }
}

template <class T>
Queue<T>::Queue(Queue<T>& other)
    : _capacity(other._capacity + STANDARD_SIZE),  // Добавляем запас памяти
    _count(0)
{
    // Копируем элементы из другой очереди
    // Проходим по всем элементам другой очереди
    auto it = other._data.begin();
    while (it != other._data.end()) {
        push(*it);
        ++it;
    }
}

template <class T>
int Queue<T>::get_capacity() const {
    return _capacity;
}

template <class T>
int Queue<T>::get_count() const {
    return _count;
}

template <class T>
void Queue<T>::push(T val) {
    if (is_full()) {
        throw std::logic_error("Queue is full");
    }

    _data.push_back(val);
    _count++;
}

template <class T>
void Queue<T>::pop() {
    if (is_empty()) {
        throw std::logic_error("Queue is empty");
    }

    _data.pop_front();
    _count--;
}

template <class T>
T Queue<T>::tail() const {
    if (is_empty()) {
        throw std::logic_error("Queue is empty");
    }

    // Находим последний элемент через итератор
    // Так как в List нет быстрого доступа к последнему элементу,
    // нам нужно пройтись по всему списку
    auto it = _data.begin();
    T last_value;

    while (it != _data.end()) {
        last_value = *it;
        ++it;
    }

    return last_value;
}

template <class T>
bool Queue<T>::is_empty() const noexcept {
    return _count == 0;
}

template <class T>
bool Queue<T>::is_full() const noexcept {
    return _count >= _capacity;
}

template <class T>
void Queue<T>::clear() noexcept {
    // Очищаем список
    while (!_data.is_empty()) {
        _data.pop_front();
    }
    _count = 0;
}

template <class T>
T Queue<T>::head() const {
    if (is_empty()) {
        throw std::logic_error("Queue is empty");
    }

    // Получаем первый элемент через итератор
    auto it = _data.begin();
    if (it != _data.end()) {
        return *it;
    }

    throw std::logic_error("Queue is empty");
}