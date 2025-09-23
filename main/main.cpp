// Copyright 2024 Marina Usova

#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "../lib_easy_example/easy_example.h"

#include "../lib_TVector/TVector.h"
#include "../lib_Math_Vector/Math_Vector.h"
#include "../lib_Matrix/Matrix.h"
#include "../lib_Matrix_Triangle/Matrix_Triangle.h"

int main() {
  int a, b;
  float result;

  a = 1; b = 4;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  a = 1; b = 0;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  return 0;
}

#endif  // EASY_EXAMPLE
