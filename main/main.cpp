// Copyright 2024 Marina Usova
//
//#define EASY_EXAMPLE
//#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "../lib_easy_example/easy_example.h"

#include "../lib_TVector/TVector.h"
#include "../lib_Math_Vector/Math_Vector.h"
#include "../lib_Matrix/Matrix.h"
#include "../lib_Matrix_Triangle/Matrix_Triangle.h"

#include <iostream>
#include <vector>



template<typename T>
bool find_smaller_neighbor(Matrix<T>& matrix, int current_i, int current_j,
    int& min_i, int& min_j, T& min_val) {
    T current_value = matrix[current_i][current_j];
    min_val = current_value;
    min_i = current_i;
    min_j = current_j;
    bool found_smaller = false;

    if (current_i > 0 && matrix[current_i - 1][current_j] < min_val) {
        min_val = matrix[current_i - 1][current_j];
        min_i = current_i - 1;
        min_j = current_j;
        found_smaller = true;
    }

    if (current_j < matrix.get_column() - 1 &&
        matrix[current_i][current_j + 1] < min_val) {
        min_val = matrix[current_i][current_j + 1];
        min_i = current_i;
        min_j = current_j + 1;
        found_smaller = true;
    }

    if (current_i < matrix.get_row() - 1 &&
        matrix[current_i + 1][current_j] < min_val) {
        min_val = matrix[current_i + 1][current_j];
        min_i = current_i + 1;
        min_j = current_j;
        found_smaller = true;
    }

    if (current_j > 0 && matrix[current_i][current_j - 1] < min_val) {
        min_val = matrix[current_i][current_j - 1];
        min_i = current_i;
        min_j = current_j - 1;
        found_smaller = true;
    }

    return found_smaller;
}

template<typename T>
T matrix_get_local_min(Matrix<T>& matrix) {
    if (matrix.get_row() == 0 || matrix.get_column() == 0) {
        throw std::invalid_argument("Matrix cannot be empty");
    }

    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        seeded = true;
    }

    int current_i = std::rand() % matrix.get_row();
    int current_j = std::rand() % matrix.get_column();

    bool continue_flag = true;

    while (continue_flag) {
        int min_i, min_j;
        T min_val;
        if (find_smaller_neighbor(matrix, current_i, current_j, min_i, min_j, min_val)) {
            current_i = min_i;
            current_j = min_j;
        }
        else {
            continue_flag = false;
        }
    }

    return matrix[current_i][current_j];
}


int main() {
    Matrix<int> vector = {
        {3,1,2},
        {5,8,4},
        {7,6,9}
    };
    int min;
    min = matrix_get_local_min(vector);
    std::cout << min;
    return 0;
}




//int main() {
//  int a, b;
//  float result;
//
//  a = 1; b = 4;
//
//  try {
//      result = division(a, b);
//      std::cout << a << " / " << b << " = "
//          << std::setprecision(2) << result << std::endl;
//  } catch (std::exception err) {
//      std::cerr << err.what() << std::endl;
//  }
//
//  a = 1; b = 0;
//
//  try {
//      result = division(a, b);
//      std::cout << a << " / " << b << " = "
//          << std::setprecision(2) << result << std::endl;
//  } catch (std::exception err) {
//      std::cerr << err.what() << std::endl;
//  }
//
//  return 0;
//}
//
//#endif  // EASY_EXAMPLE
//#define MATRIX
//#ifdef MATRIX
//template <typename T>
//Matrix<T> matrix_user_input() {
//    int m, n;
//
//    std::cout << "Please enter the size of matrix (m n): ";
//    std::cin >> m;
//    std::cin >> n;
//    try {
//        Matrix<T> matrix(m, n);
//        std::cout << "Input matrix: " << std::endl;
//        std::cin >> matrix;
//        return matrix;
//    }
//    catch (const std::exception& e) {
//        std::cout << e.what() << std::endl;
//    }
//}
//
//template <typename T>
//TriangleMatrix<T> trianglematrix_user_input() {
//    int m, n;
//
//    std::cout << "Please enter the size of matrix (m n): ";
//    std::cin >> m;
//    std::cin >> n;
//    try {
//        TriangleMatrix<T> tr_matrix(m, n);
//        std::cout << "Input matrix: " << std::endl;
//        std::cin >> tr_matrix;
//        return tr_matrix;
//    }
//    catch (const std::exception& e) {
//        std::cout << e.what() << std::endl;
//    }
//}
//
//template <typename T>
//MathVector<T> mathvector_user_input() {
//    int m;
//
//    std::cout << "Please enter the size of mathvector (m): ";
//    std::cin >> m;
//    try {
//        MathVector<T> vector(m);
//        std::cout << "Input vector: " << std::endl;
//        std::cin >> vector;
//        return vector;
//    }
//    catch (const std::exception& e) {
//        std::cout << e.what() << std::endl;
//    }
//}
//
//void main() {
//    while (true) {
//        system("cls");
//        std::cout << "1. Matrix*Matrix;\n"
//            << "2. Matrix*Vector;\n"
//            << "3. Vector*Matrix;\n"
//            << "4. Vector*Vector;\n"
//            << "5. Matrix+Matrix;\n"
//            << "6. Matrix-Matrix;\n"
//            << "7. TriangleMatrix+TriangleMatrix;\n"
//            << "8. TriangleMatrix-TriangleMatrix;\n"
//            << "9. TriangleMatrix*TriangleMatrix;\n"
//            << "0. Exit." << std::endl;
//        std::cout << "Please choose an action: ";
//        int user_choice;
//        std::cin >> user_choice;
//
//        if (user_choice == 0) {
//            break;
//        }
//
//        Matrix<int> matrix_1;
//        Matrix<int> matrix_2;
//        Matrix<int> matrix_3;
//        TriangleMatrix<int> tr_matrix_1;
//        TriangleMatrix<int> tr_matrix_2;
//        TriangleMatrix<int> tr_matrix_3;
//        MathVector<int> mathvector_1;
//        MathVector<int> mathvector_2;
//
//        switch (user_choice) {
//        case 1:
//            system("cls");
//            try {
//                matrix_1 = matrix_user_input<int>();
//                matrix_2 = matrix_user_input<int>();
//                matrix_3 = matrix_1 * matrix_2;
//                std::cout << "Answer:\n" << matrix_3;
//                system("pause");
//            }
//            catch (const std::exception& e) {
//                std::cout << e.what() << std::endl;
//            }
//            break;
//        case 2:
//            system("cls");
//            try {
//                matrix_1 = matrix_user_input<int>();
//                mathvector_1 = mathvector_user_input<int>();
//                mathvector_2 = matrix_1 * mathvector_1;
//                std::cout << "Answer:\n" << mathvector_2;
//                system("pause");
//            }
//            catch (const std::exception& e) {
//                std::cout << e.what() << std::endl;
//            }
//            break;
//        case 3:
//            system("cls");
//            try {
//                matrix_1 = matrix_user_input<int>();
//                mathvector_1 = mathvector_user_input<int>();
//                mathvector_2 = mathvector_1 * matrix_1;
//                std::cout << "Answer:\n" << mathvector_2;
//                system("pause");
//            }
//            catch (const std::exception& e) {
//                std::cout << e.what() << std::endl;
//            }
//            break;
//        case 4:
//            system("cls");
//            try {
//                mathvector_1 = mathvector_user_input<int>();
//                mathvector_2 = mathvector_user_input<int>();
//                int number = mathvector_1 * mathvector_2;
//                std::cout << "Answer:\n" << number;
//                system("pause");
//            }
//            catch (const std::exception& e) {
//                std::cout << e.what() << std::endl;
//            }
//            break;
//        case 5:
//            system("cls");
//            try {
//                matrix_1 = matrix_user_input<int>();
//                matrix_2 = matrix_user_input<int>();
//                matrix_3 = matrix_1 + matrix_2;
//                std::cout << "Answer:\n" << matrix_3;
//                system("pause");
//            }
//            catch (const std::exception& e) {
//                std::cout << e.what() << std::endl;
//            }
//            break;
//        case 6:
//            system("cls");
//            try {
//                matrix_1 = matrix_user_input<int>();
//                matrix_2 = matrix_user_input<int>();
//                matrix_3 = matrix_1 - matrix_2;
//                std::cout << "Answer:\n" << matrix_3;
//                system("pause");
//            }
//            catch (const std::exception& e) {
//                std::cout << e.what() << std::endl;
//            }
//            break;
//        case 7:
//            system("cls");
//            try {
//                tr_matrix_1 = trianglematrix_user_input<int>();
//                tr_matrix_2 = trianglematrix_user_input<int>();
//                tr_matrix_3 = tr_matrix_1 + tr_matrix_2;
//                std::cout << "Answer:\n" << tr_matrix_3;
//                system("pause");
//            }
//            catch (const std::exception& e) {
//                std::cout << e.what() << std::endl;
//            }
//            break;
//        case 8:
//            system("cls");
//            try {
//                tr_matrix_1 = trianglematrix_user_input<int>();
//                tr_matrix_2 = trianglematrix_user_input<int>();
//                tr_matrix_3 = tr_matrix_1 - tr_matrix_2;
//                std::cout << "Answer:\n" << tr_matrix_3;
//                system("pause");
//            }
//            catch (const std::exception& e) {
//                std::cout << e.what() << std::endl;
//            }
//            break;
//        case 9:
//            system("cls");
//            try {
//                tr_matrix_1 = trianglematrix_user_input<int>();
//                tr_matrix_2 = trianglematrix_user_input<int>();
//                tr_matrix_3 = tr_matrix_1 * tr_matrix_2;
//                std::cout << "Answer:\n" << tr_matrix_3;
//                system("pause");
//            }
//            catch (const std::exception& e) {
//                std::cout << e.what() << std::endl;
//            }
//            break;
//        default:
//            std::cout << "Wrong Input. Try again!" << std::endl;
//            break;
//        }
//    }
//}
//#endif // MATRIX
