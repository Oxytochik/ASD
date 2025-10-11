//#pragma once
//
//#include <iostream>
//#include <utility>
//#include <random>
//#include <chrono>
//#include <initializer_list>
//#include <stdexcept>
//
//
//#include "..\lib_Matrix\Matrix.h"
//
//template<class T>
//class Matrix_Triangle : public Matrix<T> {
//public:
//    // Constructors
//    Matrix_Triangle();
//    explicit Matrix_Triangle(int);
//    Matrix_Triangle(const Math_Vector<Math_Vector<T>>&);
//    Matrix_Triangle(const Matrix_Triangle<T>&);
//
//    // Destructor
//    ~Matrix_Triangle();
//
//    Matrix_Triangle<T> add(const Matrix_Triangle<T>&);
//    Matrix_Triangle<T> sub(const Matrix_Triangle<T>&);
//    Matrix_Triangle<T> mult(const Matrix_Triangle<T>&);
//    Matrix_Triangle<T> transpose();
//
//    // Operators
//    Matrix_Triangle<T> operator+(const Matrix_Triangle<T>&) const;
//    Matrix_Triangle<T> operator-(const Matrix_Triangle<T>&) const;
//    Matrix_Triangle<T> operator*(const Matrix_Triangle<T>&) const;
//
//    Matrix_Triangle<T>& operator+=(const Matrix_Triangle<T>&);
//    Matrix_Triangle<T>& operator-=(const Matrix_Triangle<T>&);
//    Matrix_Triangle<T>& operator*=(const Matrix_Triangle<T>&);
//
//    bool operator==(const Matrix_Triangle<T>&) const;
//    bool operator!=(const Matrix_Triangle<T>&) const;
//
//    friend std::ostream& operator<<(std::ostream& out, const Matrix_Triangle<T>& matrix);
//    friend std::istream& operator>>(std::istream& in, Matrix_Triangle<T>& matrix);
//};
//
//// Constructors
//template<class T>
//Matrix_Triangle<T>::Matrix_Triangle() {}
//
//template<class T>
//Matrix_Triangle<T>::Matrix_Triangle(int M) {}
//
//template<class T>
//Matrix_Triangle<T>::Matrix_Triangle(const Math_Vector<Math_Vector<T>>&) {}
//
//template<class T>
//Matrix_Triangle<T>::Matrix_Triangle(const Matrix_Triangle<T>& other) {}
//
//// Destructor
//template<class T>
//Matrix_Triangle<T>::~Matrix_Triangle() {}
//
//template<class T>
//Matrix_Triangle<T> Matrix_Triangle<T>::add(const Matrix_Triangle<T>& other) {}
//template<class T>
//Matrix_Triangle<T> Matrix_Triangle<T>::sub(const Matrix_Triangle<T>& other) {}
//template<class T>
//Matrix_Triangle<T> Matrix_Triangle<T>::mult(const Matrix_Triangle<T>& other) {}
//template<class T>
//Matrix_Triangle<T> Matrix_Triangle<T>::transpose() {}
//
//// Operators
//template<class T>
//Matrix_Triangle<T> Matrix_Triangle<T>::operator+(const Matrix_Triangle<T>&) const {}
//
//template<class T>
//Matrix_Triangle<T> Matrix_Triangle<T>::operator-(const Matrix_Triangle<T>&) const {}
//
//template<class T>
//Matrix_Triangle<T> Matrix_Triangle<T>::operator*(const Matrix_Triangle<T>&) const {}
//
//template<class T>
//Matrix_Triangle<T>& Matrix_Triangle<T>::operator+=(const Matrix_Triangle<T>&) {}
//
//template<class T>
//Matrix_Triangle<T>& Matrix_Triangle<T>::operator-=(const Matrix_Triangle<T>&) {}
//
//template<class T>
//Matrix_Triangle<T>& Matrix_Triangle<T>::operator*=(const Matrix_Triangle<T>&) {}
//
//template<class T>
//bool Matrix_Triangle<T>::operator==(const Matrix_Triangle<T>&) const {}
//
//template<class T>
//bool Matrix_Triangle<T>::operator!=(const Matrix_Triangle<T>&) const {}
//
//template<class T>
//std::ostream& operator<<(std::ostream& out, const Matrix_Triangle<T>& matrix) {}
//
//template<class T>
//std::istream& operator>>(std::istream& in, Matrix_Triangle<T>& matrix) {}