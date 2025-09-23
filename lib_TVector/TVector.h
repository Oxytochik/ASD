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
    T* _data = nullptr;
    int _size = 0;
    int _capacity = CAPACITY;

public:
    // Constructors
    TVector();
    explicit TVector(int);
    TVector(int, const T*);
    explicit TVector(std::initializer_list<T>);
    TVector(int, std::initializer_list<T>);
    explicit TVector(const TVector<T>&);

    // Destructor
    ~TVector();

    // Getters
    T* data() const noexcept;
    int size() const noexcept;
    int capacity() const noexcept;
    size_t deleted_count() const noexcept;
    T& front() const;
    T& back() const;
    T* begin() const;
    T* end() const;

    // Functions
    bool is_empty() const noexcept;
    bool is_full() const noexcept;
    T& at(int) const;
    void print() const noexcept;
    void service_print() const;
    void emplace(int, const T&);
    void assign(const TVector<T>&);

    // Insertion functions
    void push_front(const T&);
    void push_back(const T&);
    void insert(int, const T&);

    // Deletion functions
    void pop_front();
    void pop_back();
    void erase(int);

    // Memory management functions
    void clear() noexcept;
    void shrink_to_fit();
    void reserve(int);
    void resize(int, bool);

    // Operators overload
    void operator=(const TVector<T>&);
    bool operator==(const TVector<T>&) const;
    bool operator!=(const TVector<T>&) const;
    T& operator[](int) const;

private:
    size_t _deleted = 0;
    State* _states = nullptr;
    void effective_deletion();
    T& reverse_at(int) const;
};