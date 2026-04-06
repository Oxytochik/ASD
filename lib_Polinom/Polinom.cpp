#include "polinom.h"
#include <sstream>
#include <cctype>
#include <algorithm>
#include <cmath>
#include <climits>

// ==================== Constructors ====================

Polynom::Polynom() : _polynom(), _name("") {}

Polynom::Polynom(const Monom& monom) : _polynom(), _name("") {
    if (!monom.is_zero())
        _polynom.push_back(monom);
}

Polynom::Polynom(const std::string& str) : _polynom(), _name("") {
    std::string s = str;
    s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
    if (s.empty()) return;

    size_t pos = 0;
    char sign = '+';
    while (pos < s.length()) {
        if (s[pos] == '+' || s[pos] == '-') {
            sign = s[pos];
            ++pos;
        }
        size_t start = pos;
        while (pos < s.length() && s[pos] != '+' && s[pos] != '-')
            ++pos;
        std::string term = s.substr(start, pos - start);
        if (!term.empty()) {
            std::istringstream iss(term);
            Monom m;
            iss >> m;
            if (sign == '-')
                m = Monom(-m.get_coeff(), m.get_powers());
            if (!m.is_zero())
                *this += m;          // сохраняет упорядоченность
        }
    }
}

Polynom::Polynom(const Polynom& other) = default;

// ==================== Name ====================

void Polynom::set_name(const std::string& name) {
    _name = name;
}

// ==================== Zero check ====================

bool Polynom::is_zero() const {
    if (_polynom.is_empty()) return true;
    for (auto it = _polynom.begin(); it != _polynom.end(); ++it) {
        if (!it->is_zero()) return false;
    }
    return true;
}

// ==================== Core arithmetic ====================

Polynom Polynom::add(const Polynom& other) const {
    Polynom result;
    auto it1 = _polynom.begin();
    auto it2 = other._polynom.begin();

    while (it1 != _polynom.end() && it2 != other._polynom.end()) {
        if (*it1 == *it2) {
            Monom sum = *it1 + *it2;
            if (!sum.is_zero())
                result._polynom.push_back(sum);
            ++it1;
            ++it2;
        }
        else if (*it1 < *it2) {
            result._polynom.push_back(*it1);
            ++it1;
        }
        else {
            result._polynom.push_back(*it2);
            ++it2;
        }
    }

    while (it1 != _polynom.end()) {
        result._polynom.push_back(*it1);
        ++it1;
    }
    while (it2 != other._polynom.end()) {
        result._polynom.push_back(*it2);
        ++it2;
    }

    return result;
}

Polynom Polynom::sub(const Polynom& other) const {
    Polynom result;
    auto it1 = _polynom.begin();
    auto it2 = other._polynom.begin();

    while (it1 != _polynom.end() && it2 != other._polynom.end()) {
        if (*it1 == *it2) {
            Monom diff = *it1 - *it2;
            if (!diff.is_zero())
                result._polynom.push_back(diff);
            ++it1;
            ++it2;
        }
        else if (*it1 < *it2) {
            result._polynom.push_back(*it1);
            ++it1;
        }
        else {
            result._polynom.push_back(Monom(-it2->get_coeff(), it2->get_powers()));
            ++it2;
        }
    }

    while (it1 != _polynom.end()) {
        result._polynom.push_back(*it1);
        ++it1;
    }
    while (it2 != other._polynom.end()) {
        result._polynom.push_back(Monom(-it2->get_coeff(), it2->get_powers()));
        ++it2;
    }

    return result;
}

Polynom Polynom::mult(const Polynom& other) const {
    Polynom result;
    for (auto it1 = _polynom.begin(); it1 != _polynom.end(); ++it1) {
        for (auto it2 = other._polynom.begin(); it2 != other._polynom.end(); ++it2) {
            Monom product = (*it1) * (*it2);
            if (!product.is_zero())
                result += product;
        }
    }
    return result;
}

Polynom Polynom::div(const Polynom& other) const {
    return divmod(other).first;
}

Polynom Polynom::mod(const Polynom& other) const {
    return divmod(other).second;
}

std::pair<Polynom, Polynom> Polynom::divmod(const Polynom& other) const {
    if (other.is_zero())
        throw std::logic_error("Division by zero polynomial");

    if (!check_powers(other))
        return { Polynom(), *this };

    Polynom quotient;
    Polynom remainder = *this;

    while (!remainder.is_zero()) {
        Monom leading_remainder = *remainder._polynom.begin();
        Monom leading_divisor = *other._polynom.begin();

        if (!can_divide(leading_remainder, leading_divisor))
            break;

        Monom term = leading_remainder / leading_divisor;
        quotient._polynom.push_back(term);

        Polynom subtrahend = other.mult_by_monom(term);
        remainder = remainder.sub(subtrahend);
    }

    return { quotient, remainder };
}

// ==================== Operations with monomials ====================

Polynom Polynom::add_a_monom(const Monom& other) const {
    return *this + Polynom(other);
}
Polynom Polynom::sub_a_monom(const Monom& other) const {
    return *this - Polynom(other);
}
Polynom Polynom::mult_by_monom(const Monom& other) const {
    return *this * Polynom(other);
}
Polynom Polynom::div_by_monom(const Monom& other) const {
    return *this / Polynom(other);
}
Polynom Polynom::mod_by_monom(const Monom& other) const {
    return *this % Polynom(other);
}
std::pair<Polynom, Polynom> Polynom::divmod_by_monom(const Monom& other) const {
    return divmod(Polynom(other));
}

// ==================== Operations with numbers ====================

Polynom Polynom::add_a_number(double other) const {
    return *this + Monom(other);
}
Polynom Polynom::sub_a_number(double other) const {
    return *this - Monom(other);
}
Polynom Polynom::mult_by_number(double other) const {
    return *this * Monom(other);
}
Polynom Polynom::div_by_number(double other) const {
    if (std::abs(other) < EPSILON)
        throw std::logic_error("Division by zero");
    return *this * Monom(1.0 / other);
}

// ==================== Evaluation ====================

double Polynom::value_at_the_point(double x, double y, double z) const {
    double result = 0.0;
    for (auto it = _polynom.begin(); it != _polynom.end(); ++it)
        result += it->value_at_the_point(x, y, z);
    return result;
}

// ==================== Operators (Polynom ? Polynom) ====================

Polynom Polynom::operator+(const Polynom& other) const { return add(other); }
Polynom Polynom::operator-(const Polynom& other) const { return sub(other); }
Polynom Polynom::operator*(const Polynom& other) const { return mult(other); }
Polynom Polynom::operator/(const Polynom& other) const { return div(other); }
Polynom Polynom::operator%(const Polynom& other) const { return mod(other); }

// ==================== Operators (Polynom ? Monom) ====================

Polynom Polynom::operator+(const Monom& other) const { return add_a_monom(other); }
Polynom Polynom::operator-(const Monom& other) const { return sub_a_monom(other); }
Polynom Polynom::operator*(const Monom& other) const { return mult_by_monom(other); }
Polynom Polynom::operator/(const Monom& other) const { return div_by_monom(other); }
Polynom Polynom::operator%(const Monom& other) const { return mod_by_monom(other); }

//Polynom operator+(const Monom& monom, const Polynom& polynom) { return polynom + monom; }
//Polynom operator-(const Monom& monom, const Polynom& polynom) { return Polynom(monom) - polynom; }
//Polynom operator*(const Monom& monom, const Polynom& polynom) { return polynom * monom; }
//Polynom operator/(const Monom& monom, const Polynom& polynom) { return Polynom(monom) / polynom; }
//Polynom operator%(const Monom& monom, const Polynom& polynom) { return Polynom(monom) % polynom; }

// ==================== Operators (Polynom ? double) ====================

Polynom Polynom::operator+(double other) const { return add_a_number(other); }
Polynom Polynom::operator-(double other) const { return sub_a_number(other); }
Polynom Polynom::operator*(double other) const { return mult_by_number(other); }
Polynom Polynom::operator/(double other) const { return div_by_number(other); }

//Polynom operator+(double number, const Polynom& polynom) { return polynom + number; }
//Polynom operator-(double number, const Polynom& polynom) { return Polynom(number) - polynom; }
//Polynom operator*(double number, const Polynom& polynom) { return polynom * number; }
//Polynom operator/(double number, const Polynom& polynom) { return Polynom(number) / polynom; }

// ==================== Compound assignment ====================

Polynom& Polynom::operator+=(const Polynom& other) { *this = *this + other; return *this; }
Polynom& Polynom::operator-=(const Polynom& other) { *this = *this - other; return *this; }
Polynom& Polynom::operator*=(const Polynom& other) { *this = *this * other; return *this; }
Polynom& Polynom::operator/=(const Polynom& other) { *this = *this / other; return *this; }

Polynom& Polynom::operator+=(const Monom& other) { *this = *this + other; return *this; }
Polynom& Polynom::operator-=(const Monom& other) { *this = *this - other; return *this; }
Polynom& Polynom::operator*=(const Monom& other) { *this = *this * other; return *this; }
Polynom& Polynom::operator/=(const Monom& other) { *this = *this / other; return *this; }

Polynom& Polynom::operator+=(double other) { *this = *this + other; return *this; }
Polynom& Polynom::operator-=(double other) { *this = *this - other; return *this; }
Polynom& Polynom::operator*=(double other) { *this = *this * other; return *this; }
Polynom& Polynom::operator/=(double other) { *this = *this / other; return *this; }

// ==================== Comparison ====================

bool Polynom::operator==(const Polynom& other) const {
    auto it1 = _polynom.begin();
    auto it2 = other._polynom.begin();
    while (it1 != _polynom.end() && it2 != other._polynom.end()) {
        if (*it1 != *it2) return false;
        ++it1;
        ++it2;
    }
    return (it1 == _polynom.end() && it2 == other._polynom.end());
}

bool Polynom::operator!=(const Polynom& other) const {
    return !(*this == other);
}

// ==================== Assignment ====================

Polynom& Polynom::operator=(const Polynom& other) = default;

// ==================== Output ====================

std::ostream& operator<<(std::ostream& out, const Polynom& polynom) {
    if (polynom.is_zero()) {
        out << "0";
        return out;
    }

    auto it = polynom._polynom.begin();
    out << *it;
    ++it;

    for (; it != polynom._polynom.end(); ++it) {
        if (it->get_coeff() < 0)
            out << " " << *it;
        else
            out << " + " << *it;
    }
    return out;
}

// ==================== Private helpers ====================

bool Polynom::check_powers(const Polynom& other) const {
    if (_polynom.is_empty()) return true;
    if (other._polynom.is_empty()) return false;

    int min_num[VARS_COUNTER];
    for (int i = 0; i < VARS_COUNTER; ++i) min_num[i] = INT_MAX;

    for (auto it = _polynom.begin(); it != _polynom.end(); ++it) {
        for (int i = 0; i < VARS_COUNTER; ++i) {
            int power = it->get_power(i);
            if (power < min_num[i]) min_num[i] = power;
        }
    }

    int max_den[VARS_COUNTER] = { 0 };
    for (auto it = other._polynom.begin(); it != other._polynom.end(); ++it) {
        for (int i = 0; i < VARS_COUNTER; ++i) {
            int power = it->get_power(i);
            if (power > max_den[i]) max_den[i] = power;
        }
    }

    for (int i = 0; i < VARS_COUNTER; ++i) {
        if (max_den[i] > min_num[i]) return false;
    }
    return true;
}

bool Polynom::can_divide(const Monom& dividend, const Monom& divisor) const {
    for (int i = 0; i < VARS_COUNTER; ++i) {
        if (dividend.get_power(i) < divisor.get_power(i))
            return false;
    }
    return true;
}