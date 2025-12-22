#pragma once

#include <iostream>
#include <initializer_list>

#define STANDARD_SIZE 15

template<class T>
class Queue {
    T* _data;
    int _capacity;    // вместимость (с запасом)
    int _head;
    int _tail;
    int _count;       // количество элементов

public:
    Queue();
    Queue(int capacity);
    Queue(std::initializer_list<T> init);
    Queue(Queue& other);
    ~Queue();

    int get_capacity() const;
    int get_count() const;

    void push(T);
    void pop();
    inline T tail() const;
    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;
    void clear() noexcept;
    T head() const;
};

template <class T>
Queue<T>::Queue()
    : _capacity(STANDARD_SIZE),
    _head(0),
    _tail(0),
    _count(0)
{
    _data = new T[_capacity];
}

template <class T>
Queue<T>::Queue(int capacity)
    : _capacity(capacity > 0 ? capacity + STANDARD_SIZE : STANDARD_SIZE),
    _head(0),
    _tail(0),
    _count(0)
{
    if (capacity <= 0) {
        throw std::logic_error("Queue capacity must be positive");
    }
    _data = new T[_capacity];
}

template <class T>
Queue<T>::Queue(std::initializer_list<T> init) {
    if (init.size() == 0) {
        throw std::invalid_argument(
            "Queue: Invalid argument - list must not be empty");
    }

    // Устанавливаем вместимость с запасом: размер списка + STANDARD_SIZE
    _capacity = init.size() + STANDARD_SIZE;
    _head = 0;
    _count = init.size();

    _data = new T[_capacity];

    // Копируем элементы из списка инициализации
    const T* src = init.begin();
    for (int i = 0; i < _count; i++) {
        _data[i] = src[i];
    }
    _tail = _count;  // _tail указывает на следующую свободную позицию
}

template <class T>
Queue<T>::Queue(Queue<T>& other)
    : _capacity(other._capacity + STANDARD_SIZE),  // Добавляем запас памяти
    _head(0),
    _tail(other._count),
    _count(other._count)
{
    _data = new T[_capacity];

    // Копируем элементы в правильном порядке
    for (int i = 0; i < _count; i++) {
        int src_index = (other._head + i) % other._capacity;
        _data[i] = other._data[src_index];
    }
}

template <class T>
Queue<T>::~Queue() {
    delete[] _data;
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

    _data[_tail] = val;
    _tail = (_tail + 1) % _capacity;
    _count++;
}

template <class T>
void Queue<T>::pop() {
    if (is_empty()) {
        throw std::logic_error("Queue is empty");
    }

    _head = (_head + 1) % _capacity;
    _count--;
}

template <class T>
inline T Queue<T>::tail() const {
    if (is_empty()) {
        throw std::logic_error("Queue is empty");
    }
    return _data[(_tail + _capacity - 1) % _capacity];
}

template <class T>
inline bool Queue<T>::is_empty() const noexcept {
    return _count == 0;
}

template <class T>
inline bool Queue<T>::is_full() const noexcept {
    return _count == _capacity;
}

template <class T>
void Queue<T>::clear() noexcept {
    _head = 0;
    _tail = 0;
    _count = 0;
}

template <class T>
T Queue<T>::head() const {
    if (is_empty()) {
        throw std::logic_error("Queue is empty");
    }
    return _data[_head];
}