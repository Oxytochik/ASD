#pragma once
#include <iostream>
#include <utility>
#include <random>
#include <chrono>
#include <initializer_list>
#include <stdexcept>
#include "../lib_TVector/TVector.h"



template <class T>
class MVector : public TVector<T> {
public:

	MVector();
	MVector(int);
	MVector(int, T*);
	MVector(std::initializer_list<T>);
	MVector(int, std::initializer_list<T>);
	MVector(TVector<T>&);
	MVector(MVector<T>&);

	~MVector();

	MVector<T>& add(MVector<T>&);
	MVector<T> sub(MVector<T>&);
	MVector<T> mult_with_numb(T&);
	MVector<T> div(T&);
	T mult(MVector<T>&);

	MVector<T> operator+(MVector<T>&);
	MVector<T> operator-(MVector<T>&);
	T operator*(MVector<T>&);
	MVector<T> operator*(T&);
	MVector<T> operator/(T&);

	MVector<T>& operator+=(MVector<T>&);
	MVector<T>& operator-=(MVector<T>&);
	MVector<T>& operator*=(T&);
	MVector<T>& operator/=(T&);

};



template<class T>
MVector<T>::MVector()
	: TVector<T>() {}

template<class T>
MVector<T>::MVector(int size)
	: TVector<T>(size) {}

template<class T>
MVector<T>::MVector(int size, T* data)
	: TVector<T>(size, data) {}

template<class T>
MVector<T>::MVector(std::initializer_list<T> init)
	: TVector<T>(init) {}

template<class T>
MVector<T>::MVector(int size, std::initializer_list<T> init)
	: TVector<T>(size, init) {}

template<class T>
MVector<T>::MVector(TVector<T>& other)
	: TVector<T>(other) {}

template<class T>
MVector<T>::MVector(MVector<T>& other)
	: TVector<T>(other) {}


template<class T> MVector<T>::~MVector() {}



template <class T>
MVector<T>& MVector<T>::add(MVector<T>& other) {
	if (this->size != other.size) {
		throw std::logic_error("Vectors dimensions is not match");
	}

	MVector<T> result(this->size());

	for (int i = 0; i < this->size(); i++) {
		result.data()[i] = this->data()[i] + other.data()[i];
	}
	return result;
}

template <class T>
MVector<T> MVector<T>::sub(MVector<T>& other) {
	if (this->size != other.size) {
		throw std::logic_error("Vectors dimensions is not match");
	}

	MVector<T> result(this->size());

	for (int i = 0; i < this->size(); i++) {
		result.data()[i] = this->data()[i] - other.data()[i];
	}
	return result;
}

template <class T>
MVector<T> MVector<T>::mult_with_numb(T& other) {

	MVector<T> result(this->size());

	for (int i = 0; i < this->size(); i++) {
		result.data()[i] = this->data()[i] * other;
	}
	return result;
}

template <class T>
MVector<T> MVector<T>::div(T& other) {
	MVector<T> result(this->size());
	if (value == T()) {
		throw std::logic_error("Division by zero");
	}

	for (int i = 0; i < this->size(); i++) {
		result.data()[i] = this->data()[i] / other;
	}

	return result;
}

template<class T>
T MVector<T>::mult(MVector<T>& other) {
	if (this->size() != other.size()) {
		throw std::logic_error("Vectors dimensions is not match");
	}

	T result = T();

	for (int i = 0; i < this->size(); i++) {
		result += this->data()[i] * other.data()[i];
	}
	return result;
}



template<class T>
MVector<T> MVector<T>::operator+(MVector<T>& other) {
	return this->add(other);
}

template<class T>
MVector<T> MVector<T>::operator-(MVector<T>& other) {
	return this->sub(other);
}
template<class T>
MVector<T> MVector<T>::operator*(T& other) {
	return this->mult_by_number(other);
}

template<class T>
MVector<T> MVector<T>::operator/(T& other) {
	return this->div_by_number(other);
}

template<class T>
T MVector<T>::operator*(MVector<T>& other) {
	return this->scalar_mult(other);
}

template<class T>
MVector<T>& MVector<T>::operator+=(MVector<T>& other) {
	*this = *this + other;
	return *this;
}

template<class T>
MVector<T>& MVector<T>::operator-=(MVector<T>& other) {
	*this = *this - other;
	return *this;
}

template<class T>
MVector<T>& MVector<T>::operator*=(T& other) {
	*this = *this * other;
	return *this;
}

template<class T>
MVector<T>& MVector<T>::operator/=(T& other) {
	*this = *this / other;
	return *this;
}
