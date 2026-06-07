#include <iostream>
#include <utility>
#include <random>
#include <chrono>
#include <initializer_list>
#pragma once
#define CAPACITY 15
#define DELETED_LIMIT 0.15

enum State { empty, busy, deleted };

template<class T> class TVector {
protected:
    T* _data = nullptr;
    int _size = 0;
    int _capacity = CAPACITY;
    size_t _deleted = 0;
    State* _states = nullptr;

public:
    TVector();
    explicit TVector(int);
    TVector(int, const T*);
    TVector(const TVector<T>&);
    explicit TVector(std::initializer_list<T>);
    TVector(int, std::initializer_list<T>);


    ~TVector();


    T* data() const noexcept;
    int size() const noexcept;
    int capacity() const noexcept;
    T& front() const;
    T& back() const;
    T* begin() const;
    T* end() const;
    size_t deleted_count() const noexcept;

    bool is_full() const noexcept;
    bool is_empty() const noexcept;
    void emplace(int, const T&);

    void assign(const TVector<T>&);


    T& at(int) const;
    void print() const noexcept;
    void service_print() const;

    bool is_available(int) const;

   




    void push_front(const T&);
    void push_back(const T&);
    void insert(int, const T&);


    void pop_front();
    void pop_back();
    void erase(int);


    void clear() noexcept;
    void shrink_to_fit();
    void reserve(int);
    void resize(int, bool);


    TVector<T>& operator=(const TVector<T>&);
    bool operator==(const TVector<T>&) const;
    bool operator!=(const TVector<T>&) const;
    T& operator[](int) const;

private:
    void effective_deletion();
    State get_state(int) const;
    int index_recalculation(int) const;
    void shifting_elements(int, int);
};



template<class T> TVector<T>::TVector() {
    _data = new T[_capacity];
    _states = new State[_capacity];
    for (int i = 0; i < _capacity; i++) _states[i] = empty;
}

template<class T> TVector<T>::TVector(int size) {
    if (_size < 0) throw std::logic_error("Size can't be negative!");
    _size = size;
    if (_size == 0) {
        _data = new T[_capacity];
        _states = new State[_capacity];
        for (int i = 0; i < _capacity; i++) _states[i] = empty;
    }
    else {
        _capacity = size + CAPACITY;
        _data = new T[_capacity];
        _states = new State[_capacity];
        for (int i = 0; i < _size; i++) _states[i] = busy;
        for (int i = _size; i < _capacity; i++) _states[i] = empty;
    }
}

template<class T> TVector<T>::TVector(int size, const T* data) {
    if (_size < 0) throw std::invalid_argument("Size can't be negative!");
    if (data == nullptr && size > 0) {
        throw std::invalid_argument("Data is nullptr!");
    }
    _size = size;
    _capacity = _size + CAPACITY;
    _data = new T[_capacity];
    _states = new State[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = data[i];
        _states[i] = busy;
    }
    for (int i = _size; i < _capacity; i++) {
        _states[i] = empty;
    }
}

template<class T> TVector<T>::TVector(std::initializer_list<T> init) {
    if (init.size() > 0) {
        _size = init.size();
        _capacity = _size + CAPACITY;
        _data = new T[_capacity];
        _states = new State[_capacity];
        const T* src = init.begin();
        for (int i = 0; i < _size; i++) {
            _data[i] = src[i];
            _states[i] = busy;
        }
        for (int i = _size; i < _capacity; i++) {
            _states[i] = empty;
        }
    }
}


template<class T> TVector<T>::TVector(int size, std::initializer_list<T> init) {
    if (_size < 0) throw std::invalid_argument("Size can't be negative!");
    if (size > 0) {
        _size = size;
        _capacity = _size + CAPACITY;
        _data = new T[_capacity];
        _states = new TVectorElemState[_capacity];
        const T* src = init.begin();
        for (int i = 0; i < _size; i++) {
            _data[i] = src[i];
            _states[i] = TVectorElemState::busy;
        }
        for (int i = _size; i < _capacity; i++) {
            _states[i] = TVectorElemState::empty;
        }
    }
}


template<class T> TVector<T>::TVector(const TVector<T>& other) {
    _size = other._size;
    _capacity = other._capacity;
    _data = new T[_capacity];
    _deleted = other._deleted;
    _states = new State[_capacity];
    for (int i = 0; i < _capacity; i++) {
        _data[i] = other._data[i];
        _states[i] = other._states[i];
    }
}


template<class T> TVector<T>::~TVector() {
    if (_data != nullptr) {
        delete[] _data;
        delete[] _states;
    }
}



template<class T> T* TVector<T>::data() const noexcept {
    return _data;
}

template<class T> int TVector<T>::size() const noexcept {
    return _size - _deleted;
}

template<class T> int TVector<T>::capacity() const noexcept {
    return _capacity;
}

template<class T> size_t TVector<T>::deleted_count() const noexcept {
    return _deleted;
}

template<class T> T& TVector<T>::front() const {
    return at(0);
}

template<class T> T& TVector<T>::back() const {
    return at(size() - 1);
}

template<class T> T* TVector<T>::begin() const {
    if (_data == nullptr) throw std::logic_error("Data does not exist!");
    return _data;
}

template<class T> T* TVector<T>::end() const {
    if (_data == nullptr) throw std::logic_error("Data does not exist!");
    return _data + _size;
}



template<class T> bool TVector<T>::is_empty() const noexcept {
    if (size() == 0) return true;
    for (int i = 0; i < _size; i++) {
        if (_states[i] == busy) return false;
    }
    return true;
}

template<class T> bool TVector<T>::is_full() const noexcept {
    return _size >= _capacity;
}

template<class T> bool TVector<T>::is_available(int index) const {
    if (index > size() || index < 0) {
        throw std::out_of_range("Index out of range");
    }
    if (is_empty()) throw std::logic_error("The size is 0!");
    if (get_state(index) == busy) return false;
    return true;
}

template<class T> T& TVector<T>::at(int index) const {
    if (is_empty()) throw std::logic_error("The size is 0!");
    return _data[index_recalculation(index)];
}

template<class T> void TVector<T>::print() const noexcept {
    std::cout << "{ ";
    for (int i = 0; i < _size - 1; i++) {
        if (_states[i] == busy) std::cout << _data[i] << ", ";
    }
    std::cout << _data[_size - 1] << "}" << std::endl;
}

template<class T> void TVector<T>::service_print() const {
    std::cout << "{ ";
    for (int i = 0; i < _size; i++) {
        if (_states[i] == busy) std::cout << "B_" << _data[i] << " ";
        if (_states[i] == deleted) std::cout << "D_" << _data[i] << " ";
        if (_states[i] == empty) std::cout << "E_" << _data[i] << " ";
    }
    std::cout << "}" << std::endl;
}

template<class T> void TVector<T>::emplace(int index, const T& value) {
    if (is_empty()) {
        throw std::logic_error
        ("Placement of the value is impossible! The size is 0!");
    }
    at(index) = value;
}

template<class T> void TVector<T>::assign(const TVector<T>& other) {
    if (size() < other.size()) {
        delete[] _states;
        delete[] _data;
    }
    _size = other._size;
    _capacity = other._capacity;
    _data = new T[_capacity];
    _states = new State[_capacity];
    _deleted = other._deleted;
    for (int i = 0; i < _capacity; i++) {
        _data[i] = other._data[i];
        _states[i] = other._states[i];
    }
}



template<class T> void TVector<T>::push_front(const T& value) {
    if (_size == 0) _size++;
    if (_states[0] == busy) {
        _size++;
        if (is_full()) reserve(_size + CAPACITY);
        shifting_elements(_size - 1, 0);
    }
    if (_states[0] == deleted) _deleted--;
    _data[0] = value;
    _states[0] = busy;
}

template<class T> void TVector<T>::push_back(const T& value) {
    if (_size == 0) _size++;
    if (_states[_size - 1] == busy) {
        _size++;
        if (is_full()) reserve(_size + CAPACITY);
    }
    if (_states[_size - 1] == deleted) _deleted--;
    _data[_size - 1] = value;
    _states[_size - 1] = busy;
}

template<class T> void TVector<T>::insert(int index, const T& value) {
    if (_size == 0) _size++;
    int real_index = index_recalculation(index);
    _size++;
    if (is_full()) reserve(_size + CAPACITY);
    shifting_elements(_size - 1, real_index);
    _data[real_index] = value;
    _states[real_index] = busy;
}



template<class T> void TVector<T>::pop_front() {
    if (is_empty()) {
        throw std::logic_error("Deletion is not possible! The size is 0!");
    }
    _states[index_recalculation(0)] = deleted;
    _deleted++;
    if (_deleted >= static_cast<int>(_size * DELETED_LIMIT)) {
        effective_deletion();
    }
}

template<class T> void TVector<T>::pop_back() {
    if (is_empty()) {
        throw std::logic_error("Deletion is not possible! The size is 0!");
    }
    int index = 0;
    for (int i = _size - 1; i >= 0; i--) {
        if (_states[i] == busy) {
            index = i;
            break;
        }
    }
    _states[index] = empty;
    _size--;
}

template<class T> void TVector<T>::erase(int index) {
    if (is_empty()) {
        throw std::logic_error("Deletion is not possible! The size is 0!");
    }
    int real_index = index_recalculation(index);
    if (real_index == size() - 1) {
        pop_back();
        return;
    }
    _states[real_index] = deleted;
    _deleted++;
    if (_deleted >= static_cast<int>(_size * DELETED_LIMIT)) {
        effective_deletion();
    }
}



template<class T> void TVector<T>::clear() noexcept {
    delete[] _data;
    delete[] _states;
    _size = 0;
    _capacity = CAPACITY;
    _deleted = 0;
    _data = new T[_capacity];
    _states = new State[_capacity];
    for (int i = 0; i < _capacity; i++) _states[i] = empty;
}

template<class T> void TVector<T>::shrink_to_fit() {
    effective_deletion();
    if (_size < _capacity) {
        T* new_data = new T[_size];
        State* new_states = new State[_size];
        for (int i = 0; i < _size; i++) {
            new_data[i] = _data[i];
            new_states[i] = _states[i];
        }
        delete[] _data;
        delete[] _states;
        _data = new_data;
        _states = new_states;
        _capacity = _size;
    }
}

template<class T> void TVector<T>::reserve(int new_capacity) {
    effective_deletion();
    if (new_capacity > _capacity) {
        T* new_data = new T[new_capacity];
        State* new_states = new State[new_capacity];
        for (int i = 0; i < _capacity; i++) {
            new_data[i] = _data[i];
            new_states[i] = _states[i];
        }
        for (int i = _capacity; i < new_capacity; i++) new_states[i] = empty;
        delete[] _data;
        delete[] _states;
        _data = new_data;
        _states = new_states;
        _capacity = new_capacity;
    }
}

template<class T> void TVector<T>::resize(int new_size, bool toFill) {
    if (new_size < 0) {
        throw std::invalid_argument("The size cannot be negative!");
    }
    effective_deletion();
    if (new_size < _size) {
        int cnt = 0;
        for (int i = new_size; i < _size; i++) _states[i] = empty;
        for (int i = 0; i < new_size; i++) {
            if (_states[i] == busy) cnt++;
        }
        _size = cnt;
    }
    else {
        if (new_size >= _capacity) reserve(new_size + CAPACITY);
        if (toFill == true) {
            for (int i = _size; i < new_size; i++) {
                _states[i] = busy;
                _data[i] = _data[_size - 1];
            }
        }
        else {
            for (int i = _size; i < new_size; i++) _states[i] = busy;
        }
        _size = new_size;
    }
}


template <class T>  TVector<T>& TVector<T>::operator=(const TVector<T>& other) {
    assign(other);
    return *this;
}

template <class T> bool TVector<T>::operator==(const TVector<T>& other) const {
    if (size() != other.size()) return false;
    if (is_empty()) return true;
    for (int i = 0; i < size(); i++) {
        if (at(i) != other.at(i)) return false;
    }
    return true;
}

template <class T> bool TVector<T>::operator!=(const TVector<T>& other) const {
    return !(*this == other);
}

template <class T> T& TVector<T>::operator[](int index) const {
    return at(index);
}

template<class T> void TVector<T>::effective_deletion() {
    if (deleted_count() != 0) {
        int new_size = size();
        int index = 0;
        for (int i = 0; i < _size; i++) {
            if (_states[i] == busy) {
                _data[index] = _data[i];
                _states[index] = busy;
                index++;
            }
        }
        for (int i = new_size; i < _capacity; i++) _states[i] = empty;
        _size = new_size;
        _deleted = 0;
    }
}



template<class T> State TVector<T>::get_state(int index) const {
    if (is_empty()) throw std::logic_error("The size is 0!");
    return _states[index_recalculation(index)];
}

template<class T> int TVector<T>::index_recalculation(int index) const {
    if (index > size() || index < 0) { //убрали равно (>=)
        throw std::out_of_range("Index out of range");
    }
    int busy_index = -1, real_index = index;
    for (int i = 0; i < _size; i++) {
        if (_states[i] == busy) busy_index++;
        if (busy_index == index) {
            real_index = i;
            break;
        }
    }
    return real_index;
}

template<class T> void TVector<T>::shifting_elements(int begin, int end) {
    for (int i = begin; i > end; i--) {
        _data[i] = _data[i - 1];
        _states[i] = _states[i - 1];
    }
}

template <class T> int find_first(const TVector<T>& vector, const T& value) {
    if (vector.is_empty()) throw std::logic_error("The size is 0!");
    for (int i = 0; i < vector.size(); i++) {
        if (vector.at(i) == value) return i;
    }
    return -1;
}

template <class T> int find_last(const TVector<T>& vector, const T& value) {
    if (vector.is_empty()) throw std::logic_error("The size is 0!");
    for (int i = vector.size() - 1; i >= 0; i--) {
        if (vector.at(i) == value) return i;
    }
    return -1;
}

template <class T> int* find_all(const TVector<T>& vector, const T& value) {
    if (vector.is_empty()) throw std::logic_error("The size is 0!");
    int* result = nullptr, size_res = 0;
    for (int i = 0; i < vector.size(); i++) {
        if (vector.at(i) == value) size_res++;
    }

    if (size_res == 0) {
        result = new int[1];
        result[0] = -1;
    }
    else {
        result = new int[size_res];
        for (int i = 0, j = 0; j < size_res; i++) {
            if (vector.at(i) == value) {
                result[j] = i;
                j++;
            }
        }
    }
    return result;
}

//one of this uneffective
template <class T> void hoara_sort(TVector<T>& mass, int start, int end) {
    if (start >= end) return;
    int l = start, r = end;
    T base_elem = mass[(l + r) / 2];
    while (l <= r) {
        while (mass[l] < base_elem) l++;
        while (mass[r] > base_elem) r--;
        if (l <= r) {
            T temp = mass[l];
            mass[l] = mass[r];
            mass[r] = temp;
            l++;
            r--;
        }
    }
    hoara_sort(mass, start, r);
    hoara_sort(mass, l, end);
}

template <class T> void fisherYatesShuffle(TVector<T>& mass) {
    if (mass.size() <= 1) return;
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i = mass.size() - 1; i > 0; i--) {
        std::uniform_int_distribution<> distr(0, i);
        int j = distr(gen);
        std::swap(mass[i], mass[j]);
    }
}
