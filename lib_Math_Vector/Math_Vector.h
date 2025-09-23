#include <iostream>
#include <utility>
#include <random>
#include <chrono>
#include <initializer_list>
#include <stdexcept>
#include "../lib_TVector/TVector.h"
class Math_Vector : public TVector<T> {
private:
    size_t _size;
    TVector<T> data;
public:
    // Constructors
    Math_Vector();
    Math_Vector(size_t size);
    // Destructor
    ~MathVector();
    // Operators
    MathVector<T> operator+(const Math_Vector<T>&) const;
    MathVector<T> operator-(const Math_Vector<T>&) const;
    MathVector<T> operator*(const Math_Vector<T>&) const;

    MathVector<T>& operator+=(const Math_Vector<T>&);
    MathVector<T>& operator-=(const Math_Vector<T>&);
    MathVector<T>& operator*=(const Math_Vector<T>&);

    bool operator==(const Math_Vector<T>&) const;
    bool operator!=(const Math_Vector<T>&) const;
};
template <typename T>
Math_Vector<T>::Math_Vector() : TVector<T>() {}

template <typename T>
Math_Vector<T>::~Math_Vector() {}
template <typename T>
Math_Vector<T>::Math_Vector(size_t size) : _size(size) {}

template <typename T>
Math_Vector<T> Math_Vector<T>::operator*(T& val) {
    Math_Vector<T> result(size);
    return *this;
}
template <typename T>
T Math_Vector<T>::operator*(Math_Vector<T>& vec) {
    return T();
}