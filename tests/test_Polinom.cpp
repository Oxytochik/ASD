// PolynomTest.cpp
#include <gtest/gtest.h>
#include <sstream>
#include "../lib_Polinom/Polinom.h"

TEST(PolynomTest, DefaultConstructor_Empty) {
    Polynom p;
    EXPECT_TRUE(p.is_zero());
}

TEST(PolynomTest, CopyConstructor) {
    int pow1[] = { 2, 1, 0 };
    int pow2[] = { 0, 0, 3 };
    Polynom p1;
    p1 += Monom(3.0, pow1);
    p1 += Monom(5.0, pow2);

    Polynom p2(p1);
    EXPECT_TRUE(p2 == p1);
}

TEST(PolynomTest, StringConstructor) {
    Polynom p1("123.1x^2 + 34x^3y^4z^5");
    std::ostringstream oss;
    oss << p1;
    EXPECT_EQ(oss.str(), "34x^3y^4z^5 + 123.1x^2");
}

TEST(PolynomTest, OperatorPlusEqual_BasicOrder) {
    int powx[] = { 1, 0, 0 };
    int powx2[] = { 2, 0, 0 };
    int powy3[] = { 0, 3, 0 };

    Polynom p;
    p += Monom(4.0, powx);   // x
    p += Monom(2.0, powx2);  // x^2
    p += Monom(7.0, powy3);  // y^3

    Polynom expected;
    expected += Monom(2.0, powx2);
    expected += Monom(4.0, powx);
    expected += Monom(7.0, powy3);

    EXPECT_TRUE(p == expected);
}

TEST(PolynomTest, OperatorPlusEqual_ZeroCoefficientIgnored) {
    int pow_all[] = { 5, 5, 5 };
    int pow_x[] = { 1, 0, 0 };

    Polynom p;
    p += Monom(0.0, pow_all);   // нулевой моном не добавляется
    p += Monom(1.0, pow_x);

    Polynom expected;
    expected += Monom(1.0, pow_x);

    EXPECT_TRUE(p == expected);
}

TEST(PolynomTest, OperatorPlusEqual_MergeSameTerms) {
    int pow_xy[] = { 2, 1, 0 };

    Polynom p;
    p += Monom(3.0, pow_xy);
    p += Monom(5.0, pow_xy);
    p += Monom(-2.0, pow_xy);

    Polynom expected;
    expected += Monom(6.0, pow_xy);

    EXPECT_TRUE(p == expected);
}

TEST(PolynomTest, OperatorPlus_Monom) {
    int pow_x[] = { 1, 0, 0 };
    int pow_y2[] = { 0, 2, 0 };

    Polynom p;
    p += Monom(3.0, pow_x);   // 3x

    Polynom res = p + Monom(4.0, pow_y2); // +4y^2

    Polynom expected;
    expected += Monom(3.0, pow_x);
    expected += Monom(4.0, pow_y2);

    EXPECT_TRUE(res == expected);
}

TEST(PolynomTest, OperatorMinus_Monom) {
    int pow_x2[] = { 2, 0, 0 };

    Polynom p;
    p += Monom(5.0, pow_x2);   // 5x^2

    Polynom res = p - Monom(2.0, pow_x2); // -2x^2

    Polynom expected;
    expected += Monom(3.0, pow_x2);

    EXPECT_TRUE(res == expected);
}

TEST(PolynomTest, OperatorMultiply_Monom) {
    int pow_xy[] = { 1, 1, 0 };
    int pow_z2[] = { 0, 0, 2 };
    int pow_xz[] = { 1, 0, 1 };

    Polynom p;
    p += Monom(2.0, pow_xy);   // 2xy
    p += Monom(3.0, pow_z2);   // 3z^2

    Polynom res = p * Monom(4.0, pow_xz); // * 4xz

    int pow_x2yz[] = { 2, 1, 1 };
    int pow_xz3[] = { 1, 0, 3 };

    Polynom expected;
    expected += Monom(8.0, pow_x2yz);   // 8 x^2 y z
    expected += Monom(12.0, pow_xz3);   // 12 x z^3

    EXPECT_TRUE(res == expected);
}

TEST(PolynomTest, OperatorPlus_Polynom) {
    int pow_x2[] = { 2, 0, 0 };
    int pow_y[] = { 0, 1, 0 };
    int pow_x[] = { 1, 0, 0 };

    Polynom p1, p2;
    p1 += Monom(1.0, pow_x2);   // x^2
    p1 += Monom(4.0, pow_y);    // 4y

    p2 += Monom(5.0, pow_x);    // 5x
    p2 += Monom(-4.0, pow_y);   // -4y

    Polynom res = p1 + p2;

    Polynom expected;
    expected += Monom(1.0, pow_x2);
    expected += Monom(5.0, pow_x);

    EXPECT_TRUE(res == expected);
}

TEST(PolynomTest, OperatorMinus_Polynom) {
    int pow_xy[] = { 1, 1, 0 };

    Polynom p1, p2;
    p1 += Monom(7.0, pow_xy);   // 7xy
    p2 += Monom(3.0, pow_xy);   // 3xy

    Polynom res = p1 - p2;

    Polynom expected;
    expected += Monom(4.0, pow_xy);

    EXPECT_TRUE(res == expected);
}

TEST(PolynomTest, OperatorMultiply_Polynom_Simple) {
    // p1: 2x + 3y + 1
    int pow_x[] = { 1, 0, 0 };
    int pow_y[] = { 0, 1, 0 };
    int pow_0[] = { 0, 0, 0 };

    Polynom p1, p2;
    p1 += Monom(2.0, pow_x);
    p1 += Monom(3.0, pow_y);
    p1 += Monom(1.0, pow_0);

    // p2: x - y + 2
    p2 += Monom(1.0, pow_x);
    p2 += Monom(-1.0, pow_y);
    p2 += Monom(2.0, pow_0);

    Polynom res = p1 * p2;   // (2x+3y+1)*(x-y+2) = 2x^2 + xy - 3y^2 + 5x + 5y + 2

    int pow_x2[] = { 2, 0, 0 };
    int pow_xy[] = { 1, 1, 0 };
    int pow_y2[] = { 0, 2, 0 };

    Polynom expected;
    expected += Monom(2.0, pow_x2);   // 2x^2
    expected += Monom(1.0, pow_xy);   // xy
    expected += Monom(5.0, pow_x);    // 5x
    expected += Monom(-3.0, pow_y2);  // -3y^2
    expected += Monom(5.0, pow_y);    // 5y
    expected += Monom(2.0, pow_0);    // 2

    EXPECT_TRUE(res == expected);
}

TEST(PolynomTest, Output) {
    int pow1[] = { 3, 2, 1 };
    int pow2[] = { 5, 0, 0 };

    Polynom p;
    p += Monom(2.0, pow1);
    p += Monom(-4.0, pow2);

    std::ostringstream oss;
    oss << p;
    EXPECT_EQ(oss.str(), "-4x^5 + 2x^3y^2z");
}

TEST(PolynomTest, OperatorPlus_Double) {
    int pow_x[] = { 1, 0, 0 };
    Polynom p;
    p += Monom(2.0, pow_x); // 2x

    Polynom res = p + 5.0;   // 2x + 5

    int pow_0[] = { 0, 0, 0 };
    Polynom expected;
    expected += Monom(2.0, pow_x);
    expected += Monom(5.0, pow_0);

    EXPECT_TRUE(res == expected);
}

TEST(PolynomTest, OperatorMinus_Double) {
    int pow_x2[] = { 2, 0, 0 };
    Polynom p;
    p += Monom(3.0, pow_x2); // 3x^2

    Polynom res = p - 1.5;    // 3x^2 - 1.5

    int pow_0[] = { 0, 0, 0 };
    Polynom expected;
    expected += Monom(3.0, pow_x2);
    expected += Monom(-1.5, pow_0);

    EXPECT_TRUE(res == expected);
}

TEST(PolynomTest, OperatorMultiply_Double) {
    int pow_x[] = { 1, 0, 0 };
    int pow_y[] = { 0, 1, 0 };

    Polynom p;
    p += Monom(2.0, pow_x); // 2x
    p += Monom(3.0, pow_y); // 3y

    Polynom res = p * 2.0;   // 4x + 6y

    Polynom expected;
    expected += Monom(4.0, pow_x);
    expected += Monom(6.0, pow_y);

    EXPECT_TRUE(res == expected);
}

TEST(PolynomTest, OperatorDivide_Double) {
    int pow_x2[] = { 2, 0, 0 };
    int pow_y[] = { 0, 1, 0 };

    Polynom p;
    p += Monom(6.0, pow_x2); // 6x^2
    p += Monom(4.0, pow_y);  // 4y

    Polynom res = p / 2.0;    // 3x^2 + 2y

    Polynom expected;
    expected += Monom(3.0, pow_x2);
    expected += Monom(2.0, pow_y);

    EXPECT_TRUE(res == expected);
}

TEST(PolynomTest, DivisionByZeroThrows) {
    int pow_0[] = { 0, 0, 0 };
    Polynom p;
    p += Monom(1.0, pow_0);
    EXPECT_THROW(p / 0.0, std::logic_error);
}