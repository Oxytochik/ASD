#pragma once
#include <initializer_list>
#include "MVector.h"
template <class T>
class Matrix : public MVector<T> {

	int _column, _row;

public:

	Matrix();
	Matrix(int, int);
	Matrix(std::initializer_list<std::initializer_list<T>>);
	Matrix(Matrix<T>&);

	~Matrix();

	int get_column();
	int get_row();

	Matrix<T> add(Matrix<T>&);
	Matrix<T> sub(Matrix<T>&);
	Matrix<T> mult(Matrix<T>&);
	Matrix<T> mult_by_number(T&);
	Matrix<T> div_by_number(T&);
	Matrix<T> transpose();

	Matrix<T> operator+(Matrix<T>&);
	Matrix<T> operator-(Matrix<T>&);
	Matrix<T> operator*(Matrix<T>&);
	Matrix<T> operator*(T&);
	Matrix<T> operator/(T&);

	Matrix<T>& operator=(Matrix<T>&);
	Matrix<T>& operator+=(Matrix<T>&);
	Matrix<T>& operator-=(Matrix<T>&);
	Matrix<T>& operator*=(Matrix<T>&);
	Matrix<T>& operator*=(T&);
	Matrix<T>& operator/=(T&);
};

template <class T>
Matrix<T>::Matrix()
	:MVector<MVector<T>>(), _row(0), _column(0)
{
}

template <class T>
Matrix<T>::Matrix(int rows, int columns)
	: MVector<MVector<T>>(),
	_row(rows),
	_column(columns)
{
	if (rows < 0 || columns < 0) {
		throw std::logic_error("Matrix size cant be negative");
	}
	for (int i = 0; i < rows; ++i) {
		this->push_back(MathVector<T>(columns));
	}
}

template<class T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> init)
	: MathVector<MathVector<T>>(),
	_rows(static_cast<int>(init.size())),
	_columns(0)
{

	if (_rows == 0) return;

	_columns = static_cast<int>(init.begin()->size());
	for (auto& row : init) {
		if (static_cast<int>(row.size()) != _columns)
			throw std::logic_error("All rows in initializer list must have the same length!");
		this->push_back(MathVector<T>(row));
	}
}


template<class T>
Matrix<T>::Matrix(Matrix<T>& other)
	: MVector<MVector<T>>(other),
	_row(other._row),
	_column(other._column)
{
}

template<class T>
Matrix<T>::~Matrix() {}



template<class T>
int Matrix<T>::get_row() {
	return _row;
}

template<class T>
int Matrix<T>::get_column() {
	return _column;
}



template<class T>
Matrix<T> Matrix<T>::add(Matrix<T>& other) {
	if (_row != other._row || _column != other._column) {
		throw std::logic_error("Matrix sizes is not equal");
	}
	Matrix<T> result(_row, _column);

	for (int i = 0; i < _row; i++) {
		result[i] = (*this)[i] + other[i];
	}
	return result;
}

template<class T>
Matrix<T> Matrix<T>::sub(Matrix<T>& other) {
	if (_row != other._row || _column != other._column) {
		throw std::logic_error("Matrix sizes is not equal");
	}
	Matrix<T> result(_row, _column);

	for (int i = 0; i < _row; i++) {
		result[i] = (*this)[i] - other[i];
	}
	return result;
}

template<class T>
Matrix<T> Matrix<T>::mult(Matrix<T>& other) {
	if (_column != other._row) {
		throw std::logic_error("Matrix columns and rows is not equal");
	}
	Matrix<T> result(_row, other._column);
	Matrix<T> otherT = other.transpose();

	for (int i = 0; i < _row; i++) {
		for (int j = 0; j < otherT._row; j++) {
			result[i][j] = (*this)[i].mult(otherT[j]);
		}
	}

	return result;
}

template<class T>
Matrix<T> Matrix<T>::mult_by_number(T& other) {
	Matrix<T> result(_row, _column);

	for (int i = 0; i < _row; i++) {
		for (int j = 0; j < _column; j++) {
			result[i][j] = (*this)[i][j] * other;
		}
	}
	return result;
}

template<class T>
Matrix<T> Matrix<T>::div_by_number(T& other) {
	if (other == T()) throw std::logic_error("Division by zero");

	Matrix<T> result(_row, _column);

	for (int i = 0; i < _row; i++) {
		for (int j = 0; j < _column; j++) {
			result[i][j] = (*this)[i][j] / other;
		}
	}
	return result;
}

template<class T>
Matrix<T> Matrix<T>::transpose() {
	if (_row == 0 || _column == 0) return Matrix<T>();

	Matrix<T> result(_column, _row);

	for (int i = 0; i < _row; i++) {
		for (int j = 0; j < _column; j++) {
			result[j][i] = (*this)[i][j];
		}
	}
	return result;
}



template<class T>
Matrix<T> Matrix<T>::operator+(Matrix<T>& other) {
	return this->add(other);
}

template<class T>
Matrix<T> Matrix<T>::operator-(Matrix<T>& other) {
	return this->sub(other);
}

template<class T>
Matrix<T> Matrix<T>::operator*(Matrix<T>& other) {
	return this->mult(other);
}

template<class T>
Matrix<T> Matrix<T>::operator*(T& other) {
	return this->mult_by_number(other);
}

template<class T>
Matrix<T> operator*(const T& number, Matrix<T>& matrix) {
	return matrix * number;
}

template<class T>
Matrix<T> Matrix<T>::operator/(T& other) {
	return this->div_by_number(other);
}


template<class T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>& other) {
	if (this != &other) {
		MVector<MVector<T>>::operator=(other);
		_row = other._row;
		_col = other._col;
	}
	return *this;
}
template<class T>
Matrix<T>& Matrix<T>::operator+=(Matrix<T>& other) {
	*this = *this + other;
	return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator-=(Matrix<T>& other) {
	*this = *this - other;
	return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator*=(Matrix<T>& other) {
	*this = *this * other;
	return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator*=(T& other) {
	*this = *this * other;
	return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator/=(T& other) {
	*this = *this / other;
	return *this;
}



