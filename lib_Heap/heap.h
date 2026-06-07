#pragma once
#include <iostream>
#include <stdexcept>
#include "..\lib_TVector\TVector.h"

template <class T>
class Heap {
private:
    TVector<T> _data;

    int parent(int i) const noexcept;
    int left(int i) const noexcept;
    int right(int i) const noexcept;

    void sift_up(int i);
    void sift_down(int i);

public:
    Heap() = default;
    explicit Heap(int size);
    ~Heap() = default;

    const T& top() const;
    void insert(const T& value);
    T pop();

    bool is_empty() const noexcept;
    int size() const noexcept;
    void clear() noexcept;

    void print() const noexcept;

    TVector<T> sort(const TVector<T>);

};



template <class T>
int Heap<T>::parent(int i) const noexcept {
    return (i - 1) / 2;
}

template <class T>
int Heap<T>::left(int i) const noexcept {
    return 2 * i + 1;
}

template <class T>
int Heap<T>::right(int i) const noexcept {
    return 2 * i + 2;
}

template <class T>
Heap<T>::Heap(int size) : _data(size) {}

template <class T>
const T& Heap<T>::top() const {
    if (is_empty())
        throw std::logic_error("Heap::top: heap is empty");
    return _data[0];
}

template <class T>
void Heap<T>::insert(const T& value) {
    _data.push_back(value);
    if (size() > 1)
        sift_up(size() - 1);
}

template <class T>
T Heap<T>::pop() {
    if (is_empty())
        throw std::logic_error("Heap::pop: heap is empty");
    T root = _data[0];
    _data[0] = _data.back();
    _data.pop_back();
    if (!is_empty())
        sift_down(0);
    return root;
}

template <class T>
bool Heap<T>::is_empty() const noexcept {
    return _data.size() == 0;
}

template <class T>
int Heap<T>::size() const noexcept {
    return _data.size();
}

template <class T>
void Heap<T>::clear() noexcept {
    _data.clear();
}

template <class T>
void Heap<T>::print() const noexcept {
    if (is_empty()) return;
    for (int i = 0; i < size() - 1; ++i)
        std::cout << _data[i] << " ";
    std::cout << _data[size() - 1] << std::endl;
}

template <class T>
void Heap<T>::sift_up(int i) {
    while (i > 0 && _data[i] < _data[parent(i)]) {
        std::swap(_data[i], _data[parent(i)]);
        i = parent(i);
    }
}

template <class T>
void Heap<T>::sift_down(int i) {
    int n = size();
    while (true) {
        int l = left(i);
        int r = right(i);
        int smallest = i;
        if (l < n && _data[l] < _data[smallest])
            smallest = l;
        if (r < n && _data[r] < _data[smallest])
            smallest = r;
        if (smallest == i)
            break;
        std::swap(_data[i], _data[smallest]);
        i = smallest;
    }
}

template <class T>
TVector<T> sort(const TVector<T>& source) {
    Heap<T> heap;
    for (int i = 0; i < source.size(); ++i) {
        heap.insert(source[i]);
    }
    TVector<T> result;
    while (!heap.is_empty()) {
        result.push_back(heap.pop());
    }
    return result;
}