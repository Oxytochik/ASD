#pragma once

#include <iostream>
#include <stdexcept>
#include "..\lib_Heap\heap.h"          // ваш класс Heap, путь может отличаться

template <class T>
struct PriorityNode {
    T data;
    int priority;
    int order;

    PriorityNode();
    PriorityNode(const T& data, int priority, int order);
    PriorityNode(const PriorityNode& other);

    bool operator<(const PriorityNode& other) const;
    bool operator>(const PriorityNode& other) const;
    bool operator<=(const PriorityNode& other) const;
    bool operator>=(const PriorityNode& other) const;
};

template <class T>
PriorityNode<T>::PriorityNode() : data(), priority(0), order(0) {}

template <class T>
PriorityNode<T>::PriorityNode(const T& data, int priority, int order)
    : data(data), priority(priority), order(order) {
}

template <class T>
PriorityNode<T>::PriorityNode(const PriorityNode& other)
    : data(other.data), priority(other.priority), order(other.order) {
}

template <class T>
bool PriorityNode<T>::operator<(const PriorityNode& other) const {
    if (priority != other.priority) return priority < other.priority;
    return order < other.order;
}

template <class T>
bool PriorityNode<T>::operator>(const PriorityNode& other) const {
    if (priority != other.priority) return priority > other.priority;
    return order > other.order;
}

template <class T>
bool PriorityNode<T>::operator<=(const PriorityNode& other) const {
    return !(*this > other);
}

template <class T>
bool PriorityNode<T>::operator>=(const PriorityNode& other) const {
    return !(*this < other);
}

template <class T>
class PriorityQueue {
private:
    Heap<PriorityNode<T>> _heap;
    int _next_order;

public:
    PriorityQueue();
    PriorityQueue(const TVector<std::pair<T, int>>& data);

    void push(const T& data, int priority);
    T top() const;
    int top_priority() const;
    void pop();
    bool is_empty() const;
    int size() const;
    void clear();
};

template <class T>
PriorityQueue<T>::PriorityQueue() : _next_order(0) {}

template <class T>
PriorityQueue<T>::PriorityQueue(const TVector<std::pair<T, int>>& data) : _next_order(data.size()) {
    for (int i = 0; i < data.size(); ++i) {
        _heap.insert(PriorityNode<T>(data[i].first, data[i].second, i));
    }
}

template <class T>
void PriorityQueue<T>::push(const T& data, int priority) {
    _heap.insert(PriorityNode<T>(data, priority, _next_order));
    ++_next_order;
}

template <class T>
T PriorityQueue<T>::top() const {
    if (_heap.is_empty()) throw std::logic_error("Priority queue is empty!");
    return _heap.top().data;
}

template <class T>
int PriorityQueue<T>::top_priority() const {
    if (_heap.is_empty()) throw std::logic_error("Priority queue is empty!");
    return _heap.top().priority;
}

template <class T>
void PriorityQueue<T>::pop() {
    _heap.pop();   // возвращаемое значение не используется
}

template <class T>
bool PriorityQueue<T>::is_empty() const {
    return _heap.is_empty();
}

template <class T>
int PriorityQueue<T>::size() const {
    return _heap.size();
}

template <class T>
void PriorityQueue<T>::clear() {
    _heap.clear();
    _next_order = 0;
}

// Функции для извлечения K наиболее важных элементов
template <class T>
TVector<T> find_most_important_k(const TVector<std::pair<T, int>>& data, int k) {
    PriorityQueue<T> pq(data);
    TVector<T> result;
    for (int i = 0; i < k && !pq.is_empty(); ++i) {
        result.push_back(pq.top());
        pq.pop();
    }
    return result;
}

template <class T>
void print_most_important_k(const TVector<std::pair<T, int>>& data, int k) {
    PriorityQueue<T> pq(data);
    for (int i = 0; i < k && !pq.is_empty(); ++i) {
        std::cout << pq.top() << "(" << pq.top_priority() << ") ";
        pq.pop();
    }
    std::cout << std::endl;
}