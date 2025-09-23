#include <iostream>

#include "../lib_Math_Vector/Math_Vector.h"

template <typename T>
class Matrix : public mathVector<Math_Vector<T>> {
private:
    size_t _rows;
    size_t _cols;

public:
    Matrix();
    Matrix(size_t rows, size_t cols);
    ~Matrix();
    Matrix(const Math_Vector<Math_Vector<T>>&);
    Matrix(const Matrix&);

    Matrix<T> operator+(const Matrix& other);
    Matrix<T> operator-(const Matrix& other);

    Matrix<T> operator*(const T val);
    Math_Vector<T> operator*(const Math_Vector<T>& vec);

    friend Math_Vector<T> operator*(const Math_Vector<T>& vec,
        const Matrix<T>& Matrix) {
    }

    Matrix<T> operator*(const Matrix<T>& matr);

    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& data) {
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Matrix<T>& data) {
        return is;
    }
};

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols) : _rows(rows), _cols(cols) {}

template <typename T>
Matrix<T>::Matrix() : _rows(0), _cols(0) {}

template <typename T>
Matrix<T>::~Matrix() {}

template <typename T>
Matrix<T>::Matrix(const Math_Vector<Math_Vector<T>>&) {}

template <typename T>
Matrix<T>::Matrix(const Matrix&) {}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& other) {}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& other) {}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T val) {}

template <typename T>
Math_Vector<T> Matrix<T>::operator*(const Math_Vector<T>& vec) {}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& matr) {}