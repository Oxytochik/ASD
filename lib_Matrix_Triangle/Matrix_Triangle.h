#pragma once

#include <iostream>
#include <initializer_list>
#include <stdexcept>


#include "..\lib_Matrix\Matrix.h"


enum Pos {high, low};
template <class T>

class Triangle_Matrix : public Matrix<T> {
	Pos _position;
public:
	Triangle_Matrix();
	Triangle_Matrix(int);
	Triangle_Matrix(int, Pos);
	Triangle_Matrix(std::initializer_list<std::initializer_list<T>> init, Pos);
	Triangle_Matrix(Triangle_Matrix<T>&);

	~Triangle_Matrix();

	Pos get_position();

	Triangle_Matrix<T> add(Triangle_Matrix<T>&);
	Triangle_Matrix<T> sub(Triangle_Matrix<T>&);
	Triangle_Matrix<T> mult(Triangle_Matrix<T>&);
	Triangle_Matrix<T> mult_with_numb(T&);
	Triangle_Matrix<T> div_with_numb(T&);
	Triangle_Matrix<T> transpose();
	
	Triangle_Matrix<T> operator+(Triangle_Matrix<T>&);
	Triangle_Matrix<T> operator-(Triangle_Matrix<T>&);
	Triangle_Matrix<T> operator*(Triangle_Matrix<T>&);
	Triangle_Matrix<T> operator*(T&);
	Triangle_Matrix<T> operator/(T&);
	
	//Triangle_Matrix<T>& operator+=(Triangle_Matrix<T>&);
	//Triangle_Matrix<T>& operator-=(Triangle_Matrix<T>&);
	//Triangle_Matrix<T>& operator*=(Triangle_Matrix<T>&);
	//Triangle_Matrix<T>& operator*=(T&);
	//Triangle_Matrix<T>& operator/=(T&);



};
template <class T>
Triangle_Matrix<T>::Triangle_Matrix()
	: Matrix<T>(),
	_position(high)
{}

template<class T>
Triangle_Matrix<T>::Triangle_Matrix(int size) 
	: Matrix<T>(size),
	_position(high)
{
	if (size < 0) {
		throw std::logic_error("Matrix size cant be negative");
	}
	for (int i = 0; i < size; i++) {
		this->push_back(MVector<T>(i+1));
	}
}

template<class T>
Triangle_Matrix<T>::Triangle_Matrix(int size, Pos type) 
	: Matrix<T>(size),
	_position(type)

{
	if (size < 0) {
		throw std::logic_error("Matrix size cant be negative");
	}
	if (_position == high) {
		for (int i = 0; i < size; i++) {
			this->push_back(MVector<T>(i+1));
		}
	}
	else {
		for (int i = 0; i < size; i++) {
			this->push_back(MVector<T>(size - i));
		}
	}
}

template<class T>
Triangle_Matrix<T>::Triangle_Matrix(std::initializer_list<std::initializer_list<T>> init, Pos type)
	: MVector<MVector<T>>(),
	_position(type)
{

	int size = static_cast<int>(init.size());
	if (size < 0) {
		throw std::logic_error("Matrix size cant be negative");
	}

	_row = size;
	_column = size;

	int i = 0;
	if (_position == high) {
		for (auto& row : init) {
			if (static_cast<int>(row.size()) != size - i) {
				throw std::logic_error("Uncorrect number in row");
			}
			MVector<T> temproary;
			//for (int z = 0; z < i;z++) {
			//	temproary.push_back(0);
			//}
			for (const auto& elements : row) {
				
				temproary.push_back(elements);
			}
			this->push_back(temproary);
			i++;
		}
	}
	else {
		for (auto& row : init) {
			if (static_cast<int>(row.size()) != i + 1) {
				throw std::logic_error("Uncorrect number in row");
			}
			MVector<T> temproary;
			for (const auto& elements : row) {
				temproary.push_back(elements);
			}
			//for (int z = 0; z < size-i-1;z++) {
			//	temproary.push_back(0);
			//}
			this->push_back(temproary);
			i++;
		}
	}
	
}

template<class T>
Triangle_Matrix<T>::Triangle_Matrix(Triangle_Matrix<T>& other)
	: Matrix<T>(other),
	_position(other._position)
{}

template<class T>
Pos Triangle_Matrix<T>::get_position() {
	return _position;
}

template<class T> Triangle_Matrix<T>::~Triangle_Matrix() {}


template<class T>
Triangle_Matrix<T> Triangle_Matrix<T>::add(Triangle_Matrix<T>& other) {
	if (this->_row != other._row || this->_type != other._type) throw std::logic_error("Triangle matrices are not compatible for addition!");

	Triangle_Matrix<T> result(this->_row, this->_type);

	for (int i = 0; i < this->_row; i++) {
		result[i] = (*this)[i] + other[i];
	}

	return result;
}

template<class T>
Triangle_Matrix<T> Triangle_Matrix<T>::sub(Triangle_Matrix<T>& other){
	if (this->_row != other._row || this->_type != other._type) throw std::logic_error("Triangle matrices are not compatible for subtraction!");

	Triangle_Matrix<T> result(this->_row, this->_type);

	for (int i = 0; i < this->_row; i++) {
		result[i] = (*this)[i] - other[i];
	}

	return result;
}

template<class T>
Triangle_Matrix<T> Triangle_Matrix<T>::mult(Triangle_Matrix<T>& other) {
	if (this->_column != other._row)
		throw std::logic_error("Triangle matrices dimensions do not match for multiplication!");
	if (this->_type != other._type)
		throw std::logic_error("Triangle matrices must have the same type for multiplication!");

	Triangle_Matrix<T> result(this->_row, this->_type);

	if (_type == _position::high) {
		for (int i = 0; i < this->_row; i++) {
			for (int j = i; j < this->_column; j++) {
				MathVector<T> row_part(j - i + 1);
				MathVector<T> col_vec(j - i + 1);

				for (int k = 0; k <= j - i; k++)
					row_part[k] = (*this)[i][k];

				for (int k = i; k <= j; k++)
					col_vec[k - i] = other[k][j - k];

				result[i][j - i] = row_part * col_vec;
			}
		}
	}

	else {
		for (int i = 0; i < this->_row; i++) {
			for (int j = 0; j <= i; j++) {
				MathVector<T> row_part(i - j + 1);
				MathVector<T> col_vec(i - j + 1);

				for (int k = 0; k <= i - j; k++)
					row_part[k] = (*this)[i][k + j];

				for (int k = j; k <= i; k++)
					col_vec[k - j] = other[k][j];

				result[i][j] = row_part * col_vec;
			}
		}
	}


	return result;
}

template<class T>
Triangle_Matrix<T> Triangle_Matrix<T>::mult_with_numb(T& number) {
	Triangle_Matrix<T> result(this->_row, this->_type);

	for (int i = 0; i < this->_row; i++) {
		result[i] = (*this)[i] * number;
	}

	return result;
}

template<class T>
Triangle_Matrix<T> Triangle_Matrix<T>::div_with_numb(T& number) {
	if (number == T()) throw std::logic_error("Division by zero!");

	Triangle_Matrix<T> result(this->_row, this->_type);

	for (int i = 0; i < this->_row; i++) {
		result[i] = (*this)[i] / number;
	}

	return result;
}

template<class T>
Triangle_Matrix<T> Triangle_Matrix<T>::transpose() {
	Triangle_Matrix<T> result(this->_row, this->_type == _position::high ? _position::low : _position::high);

	for (int i = 0; i < this->_row; ++i) {
		for (int j = 0; j < this->_row; ++j) {
			if (this->_type == _position::high && j >= i) {
				result(j, i) = (*this)(i, j);
			}
			else if (this->_type == _position::low && j <= i) {
				result(j, i) = (*this)(i, j);
			}
		}
	}

	return result;
}

// Operators //
template<class T>
Triangle_Matrix<T> Triangle_Matrix<T>::operator+(Triangle_Matrix<T>& other) {
	return this->add(other);
}

template<class T>
Triangle_Matrix<T> Triangle_Matrix<T>::operator-(Triangle_Matrix<T>& other) {
	return this->sub(other);
}

template<class T>
Triangle_Matrix<T> Triangle_Matrix<T>::operator*(Triangle_Matrix<T>& other) {
	return this->mult(other);
}

template<class T>
Triangle_Matrix<T> Triangle_Matrix<T>::operator*(T& other) {
	return this->mult_with_numb(other);
}

template<class T>
Triangle_Matrix<T> Triangle_Matrix<T>::operator/(T& other) {
	return this->div_with_numb(other);
}