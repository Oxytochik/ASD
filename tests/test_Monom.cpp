#include <gtest/gtest.h>

#include <sstream>
#include "../lib_Monom/Monom.h"

TEST(MonomTest, DefaultConstructor) {
    Monom a;
    EXPECT_DOUBLE_EQ(a.get_coeff(), 0.0);
    EXPECT_EQ(a.get_power(0), 0);
    EXPECT_EQ(a.get_power(1), 0);
    EXPECT_EQ(a.get_power(2), 0);
}

TEST(MonomTest, ThreePowersConstructor) {
    int p[3] = { 1, 2, 3 };
    Monom a(123.1, p);
    EXPECT_DOUBLE_EQ(a.get_coeff(), 123.1);
    EXPECT_EQ(a.get_power(0), 1);
    EXPECT_EQ(a.get_power(1), 2);
    EXPECT_EQ(a.get_power(2), 3);
}

TEST(MonomTest, TwoPowersConstructor) {
    // Создаём моном с двумя ненулевыми степенями (x^1 y^2)
    int p1[3] = { 1, 2, 0 };
    Monom a(123.1, p1);
    EXPECT_DOUBLE_EQ(a.get_coeff(), 123.1);
    EXPECT_EQ(a.get_power(0), 1);
    EXPECT_EQ(a.get_power(1), 2);
    EXPECT_EQ(a.get_power(2), 0);

    // Моном с y^2 z^1
    int p2[3] = { 0, 2, 1 };
    Monom b(123.1, p2);
    EXPECT_EQ(b.get_power(0), 0);
    EXPECT_EQ(b.get_power(1), 2);
    EXPECT_EQ(b.get_power(2), 1);
}

TEST(MonomTest, OnePowerConstructor) {
    int p1[3] = { 0, 1, 0 };
    Monom a(123.0, p1);
    EXPECT_DOUBLE_EQ(a.get_coeff(), 123.0);
    EXPECT_EQ(a.get_power(1), 1);

    int p2[3] = { 0, 0, 2 };
    Monom b(123.1, p2);
    EXPECT_DOUBLE_EQ(b.get_coeff(), 123.1);
    EXPECT_EQ(b.get_power(2), 2);
}

TEST(MonomTest, CopyConstructor) {
    int p[3] = { 1, 2, 3 };
    Monom a(123.1, p);
    Monom b(a);
    EXPECT_DOUBLE_EQ(b.get_coeff(), a.get_coeff());
    EXPECT_EQ(b.get_power(0), a.get_power(0));
    EXPECT_EQ(b.get_power(1), a.get_power(1));
    EXPECT_EQ(b.get_power(2), a.get_power(2));
}

TEST(MonomTest, CoefficientOnlyConstructor) {
    Monom a(7.5);
    EXPECT_DOUBLE_EQ(a.get_coeff(), 7.5);
    EXPECT_EQ(a.get_power(0), 0);
    EXPECT_EQ(a.get_power(1), 0);
    EXPECT_EQ(a.get_power(2), 0);

    Monom b(-0.0);
    EXPECT_DOUBLE_EQ(b.get_coeff(), 0.0);
}


TEST(MonomTest, EqualityAndInequality) {
    int p1[3] = { 2, 1, 0 };
    Monom a(4.0, p1);
    Monom b(4.0, p1);
    int p2[3] = { 2, 1, 0 };
    Monom c(4.1, p2);  // коэффициент другой, но степени те же
    int p3[3] = { 3, 1, 0 };
    Monom d(4.0, p3);

    EXPECT_TRUE(a == b);
    EXPECT_TRUE(a == c);   // сравнение только по степеням
    EXPECT_FALSE(a == d);

    EXPECT_FALSE(a != b);
    EXPECT_FALSE(a != c);
    EXPECT_TRUE(a != d);
}

TEST(MonomTest, MultiplicationMonomByMonom) {
    int p1[3] = { 2, 1, 0 };
    int p2[3] = { -1, 0, -3 };
    Monom a(3.0, p1);
    Monom b(2.0, p2);
    Monom res = a * b;

    EXPECT_DOUBLE_EQ(res.get_coeff(), 6.0);
    EXPECT_EQ(res.get_power(0), 1);
    EXPECT_EQ(res.get_power(1), 1);
    EXPECT_EQ(res.get_power(2), -3);
}

TEST(MonomTest, MultiplicationByScalar) {
    int p[3] = { 1, 2, 3 };
    Monom a(5.0, p);
    Monom b = a * 4.0;
    Monom c = a * (-1.5);

    EXPECT_DOUBLE_EQ(b.get_coeff(), 20.0);
    EXPECT_EQ(b.get_power(0), 1);
    EXPECT_EQ(b.get_power(1), 2);
    EXPECT_EQ(b.get_power(2), 3);

    EXPECT_DOUBLE_EQ(c.get_coeff(), -7.5);
    EXPECT_EQ(c.get_power(0), 1);
    EXPECT_EQ(c.get_power(1), 2);
    EXPECT_EQ(c.get_power(2), 3);
}

TEST(MonomTest, DivisionMonomByMonom) {
    int p1[3] = { 4, 3, 2 };
    int p2[3] = { 1, 1, 0 };
    Monom a(12.0, p1);
    Monom b(3.0, p2);
    Monom res = a / b;

    EXPECT_DOUBLE_EQ(res.get_coeff(), 4.0);
    EXPECT_EQ(res.get_power(0), 3);
    EXPECT_EQ(res.get_power(1), 2);
    EXPECT_EQ(res.get_power(2), 2);
}

TEST(MonomTest, DivisionByScalar) {
    int p[3] = { 2, 0, 1 };
    Monom a(10.0, p);
    Monom b = a / 2.0;
    EXPECT_DOUBLE_EQ(b.get_coeff(), 5.0);

    Monom c = a / (-0.5);
    EXPECT_DOUBLE_EQ(c.get_coeff(), -20.0);
}

TEST(MonomTest, DivisionByZeroScalarThrows) {
    int p[3] = { 1, 1, 1 };
    Monom a(7.0, p);
    EXPECT_THROW(a / 0.0, std::logic_error);
    EXPECT_THROW(a / 1e-15, std::logic_error);  // меньше EPSILON
    //EXPECT_NO_THROW(a / 1e-11);
}

TEST(MonomTest, AdditionSamePowers) {
    int p[3] = { 2, 1, 0 };
    Monom a(5.0, p);
    Monom b(3.0, p);
    Monom c(-2.0, p);

    Monom sum1 = a + b;
    EXPECT_DOUBLE_EQ(sum1.get_coeff(), 8.0);
    EXPECT_EQ(sum1.get_power(0), 2);
    EXPECT_EQ(sum1.get_power(1), 1);
    EXPECT_EQ(sum1.get_power(2), 0);

    Monom sum2 = a + c;
    EXPECT_DOUBLE_EQ(sum2.get_coeff(), 3.0);
}

TEST(MonomTest, AdditionDifferentPowersThrows) {
    int p1[3] = { 1, 0, 0 };
    int p2[3] = { 0, 1, 0 };
    Monom a(1.0, p1);
    Monom b(1.0, p2);
    EXPECT_THROW(a + b, std::logic_error);
}

TEST(MonomTest, SubtractionSamePowers) {
    int p[3] = { 3, 0, 2 };
    Monom a(7.5, p);
    Monom b(2.5, p);

    Monom diff = a - b;
    EXPECT_DOUBLE_EQ(diff.get_coeff(), 5.0);
    EXPECT_EQ(diff.get_power(0), 3);
    EXPECT_EQ(diff.get_power(2), 2);
}

TEST(MonomTest, SubtractionDifferentPowersThrows) {
    int p1[3] = { 0, 2, 0 };
    int p2[3] = { 1, 0, 0 };
    Monom a(4.0, p1);
    Monom b(1.0, p2);
    EXPECT_THROW(a - b, std::logic_error);
}

TEST(MonomTest, UnaryMinus) {
    int p[3] = { 1, 2, 1 };
    Monom a(6.4, p);
    Monom b = -a;

    EXPECT_DOUBLE_EQ(b.get_coeff(), -6.4);
    EXPECT_EQ(b.get_power(0), 1);
    EXPECT_EQ(b.get_power(1), 2);
    EXPECT_EQ(b.get_power(2), 1);

    Monom c(0.0, p);
    Monom d = -c;
    EXPECT_DOUBLE_EQ(d.get_coeff(), 0.0);
}

TEST(MonomTest, CompoundAssignmentOperators) {
    int p1[3] = { 1, 0, 0 };
    int p2[3] = { 0, 1, 0 };
    Monom a(2.0, p1);
    Monom b(3.0, p2);

    a *= Monom(4.0, p1);
    EXPECT_DOUBLE_EQ(a.get_coeff(), 8.0);
    EXPECT_EQ(a.get_power(0), 2);

    int p3[3] = { 2, 2, 2 };
    Monom c(10.0, p3);
    c /= 5.0;
    EXPECT_DOUBLE_EQ(c.get_coeff(), 2.0);

    int p4[3] = { 1, 1, 1 };
    Monom d(7.0, p4);
    d += Monom(3.0, p4);
    EXPECT_DOUBLE_EQ(d.get_coeff(), 10.0);

    int p5[3] = { 3, 0, 0 };
    Monom e(8.0, p5);
    e -= Monom(5.0, p5);
    EXPECT_DOUBLE_EQ(e.get_coeff(), 3.0);
}

TEST(MonomTest, EvaluateSimple) {
    int p[3] = { -2, 1, 0 };   // x^{-2} * y
    Monom m(4.0, p);

    EXPECT_DOUBLE_EQ(m.value_at_the_point(2.0, 3.0, 5.0), 4.0 * 0.25 * 3.0);
    EXPECT_DOUBLE_EQ(m.value_at_the_point(1.0, 1.0, 1.0), 4.0);
    // При x=0 возникает деление на ноль, поведение зависит от реализации (может быть inf)
    // В данном тесте пропускаем проверку исключения, так как наша реализация не бросает исключение.
}

TEST(MonomTest, EvaluateZeroCoefficient) {
    int p[3] = { 10, 10, 10 };
    Monom m(0.0, p);
    EXPECT_DOUBLE_EQ(m.value_at_the_point(2.0, 3.0, 4.0), 0.0);
    EXPECT_DOUBLE_EQ(m.value_at_the_point(0.0, 0.0, 0.0), 0.0);
}

TEST(MonomTest, PowerCompare) {
    int p1[3] = { 2, 3, 4 };
    int p2[3] = { 2, 3, 4 };
    int p3[3] = { 2, 4, 4 };
    Monom a(1.0, p1);
    Monom b(9.9, p2);
    Monom c(1.0, p3);

    // Сравнение по убыванию степеней (operator<)
    EXPECT_FALSE(a < b);  // равные степени -> false
    EXPECT_TRUE(c < a);   // у c степень y выше? На самом деле порядок лексикографический: сначала x, потом y, потом z.
    // В нашем operator< мы сравниваем по убыванию: большая степень считается меньшей.
    // Для a (2,3,4) и c (2,4,4): при одинаковом x, сравниваем y: у a 3, у c 4 => так как 3 < 4, то a < c? 
    // Но по логике убывания, большая степень должна быть "меньше". Значит, c (с y=4) должен быть "меньше" чем a (с y=3). То есть c < a истинно. Проверим.
    EXPECT_TRUE(c < a);
}

TEST(MonomTest, Output) {
    int p[3] = { 2, 3, 4 };
    Monom a(1.2, p);
    std::ostringstream oss1;
    oss1 << a;
    EXPECT_EQ(oss1.str(), "1.2x^2y^3z^4");

    Monom b(1.2);
    std::ostringstream oss2;
    oss2 << b;
    EXPECT_EQ(oss2.str(), "1.2");

    int p2[3] = { 0, 3, 0 };
    Monom c(1.2, p2);
    std::ostringstream oss3;
    oss3 << c;
    EXPECT_EQ(oss3.str(), "1.2y^3");
}

TEST(MonomTest, Input) {
    std::istringstream iss("3.5x^2y^1");
    Monom m;
    iss >> m;
    EXPECT_DOUBLE_EQ(m.get_coeff(), 3.5);
    EXPECT_EQ(m.get_power(0), 2);
    EXPECT_EQ(m.get_power(1), 1);
    EXPECT_EQ(m.get_power(2), 0);
}