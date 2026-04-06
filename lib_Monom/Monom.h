#include <iostream>
#include <stdexcept>
#include <cmath>
#include <regex>
#include <string>
#include <algorithm>
#include <cctype>

#define VARS_COUNTER 3
#define EPSILON 1e-10

class Monom {
    double _coeff;
    int _powers[VARS_COUNTER];

public:
    Monom() : _coeff(0.0) {
        for (int i = 0; i < VARS_COUNTER; ++i)
            _powers[i] = 0;
    }

    explicit Monom(double coeff) : _coeff(coeff) {
        for (int i = 0; i < VARS_COUNTER; ++i)
            _powers[i] = 0;
    }

    Monom(double coeff, const int powers[VARS_COUNTER]) : _coeff(coeff) {
        for (int i = 0; i < VARS_COUNTER; ++i)
            _powers[i] = powers[i];
    }

    Monom(const Monom& other) : _coeff(other._coeff) {
        for (int i = 0; i < VARS_COUNTER; ++i)
            _powers[i] = other._powers[i];
    }

    ~Monom() = default;

    double get_coeff() const { 
        return _coeff; 
    }
    const int* get_powers() const { 
        return _powers; 
    }
    int get_power(int index) const {
        if (index < 0 || index >= VARS_COUNTER)
            throw std::out_of_range("Index out of range");
        return _powers[index];
    }

    bool is_zero() const {
        return std::abs(_coeff) < EPSILON; 
    }

    double value_at_the_point(double x, double y, double z) const {
        return _coeff * std::pow(x, _powers[0]) * std::pow(y, _powers[1]) * std::pow(z, _powers[2]);
    }

    Monom& operator=(const Monom& other) {
        if (this != &other) {
            _coeff = other._coeff;
            for (int i = 0; i < VARS_COUNTER; ++i)
                _powers[i] = other._powers[i];
        }
        return *this;
    }

    bool operator==(const Monom& other) const {
        for (int i = 0; i < VARS_COUNTER; ++i)
            if (_powers[i] != other._powers[i])
                return false;
        return true;
    }

    bool operator!=(const Monom& other) const {
        return !(*this == other);
    }

    // ѕор€док дл€ сортировки (лексикографически по убыванию степеней)
    bool operator<(const Monom& other) const {
        for (int i = 0; i < VARS_COUNTER; ++i) {
            if (_powers[i] != other._powers[i])
                return _powers[i] > other._powers[i];  // больша€ степень -> "меньший" моном
        }
        return false; // равны
    }

    bool operator>(const Monom& other) const {
        return other < *this;
    }

    bool operator<=(const Monom& other) const {
        return !(other < *this);
    }

    bool operator>=(const Monom& other) const {
        return !(*this < other);
    }

    Monom operator+(const Monom& other) const {
        if (*this != other)
            throw std::logic_error("Cannot add monomials with different powers!");
        return Monom(_coeff + other._coeff, _powers);
    }

    Monom operator-(const Monom& other) const {
        if (*this != other)
            throw std::logic_error("Cannot subtract monomials with different powers!");
        return Monom(_coeff - other._coeff, _powers);
    }

    Monom operator*(const Monom& other) const {
        Monom res;
        res._coeff = _coeff * other._coeff;
        for (int i = 0; i < VARS_COUNTER; ++i)
            res._powers[i] = _powers[i] + other._powers[i];
        return res;
    }

    Monom operator/(const Monom& other) const {
        if (std::abs(other._coeff) < EPSILON)
            throw std::logic_error("Division by zero!");
        for (int i = 0; i < VARS_COUNTER; ++i)
            if (_powers[i] < other._powers[i])
                throw std::logic_error("Division would result in negative powers!");
        Monom res;
        res._coeff = _coeff / other._coeff;
        for (int i = 0; i < VARS_COUNTER; ++i)
            res._powers[i] = _powers[i] - other._powers[i];
        return res;
    }

    Monom operator*(double scalar) const {
        return Monom(_coeff * scalar, _powers);
    }

    Monom operator/(double scalar) const {
        if (std::abs(scalar) < EPSILON)
            throw std::logic_error("Division by zero!");
        return Monom(_coeff / scalar, _powers);
    }

    // ”нарный минус
    Monom operator-() const {
        return Monom(-_coeff, _powers);
    }

    Monom& operator+=(const Monom& other) {
        if (*this != other)
            throw std::logic_error("Cannot add monomials with different powers!");
        //_coeff += other._coeff;
        *this = *this + other;
        return *this;
    }

    Monom& operator-=(const Monom& other) {
        if (*this != other)
            throw std::logic_error("Cannot subtract monomials with different powers!");
        /*_coeff -= other._coeff;*/
        *this = *this - other;
        return *this;
    }

    Monom& operator*=(const Monom& other) {
        //_coeff *= other._coeff;
        //for (int i = 0; i < VARS_COUNTER; ++i)
        //    _powers[i] += other._powers[i];
        *this = *this * other;
        return *this;
    }

    Monom& operator/=(const Monom& other) {
        if (std::abs(other._coeff) < EPSILON)
            throw std::logic_error("Division by zero!");
        for (int i = 0; i < VARS_COUNTER; ++i)
            if (_powers[i] < other._powers[i])
                throw std::logic_error("Division would result in negative powers!");
        _coeff /= other._coeff;
        for (int i = 0; i < VARS_COUNTER; ++i)
            _powers[i] -= other._powers[i];
        return *this;
    }

    Monom& operator*=(double scalar) {
        _coeff *= scalar;
        return *this;
    }

    Monom& operator/=(double scalar) {
        if (std::abs(scalar) < EPSILON)
            throw std::logic_error("Division by zero!");
        _coeff /= scalar;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Monom& monom) {
        if (monom.is_zero()) {
            out << "0";
            return out;
        }

        if (std::abs(monom._coeff - 1.0) > EPSILON &&
            std::abs(monom._coeff + 1.0) > EPSILON) {
            out << monom._coeff;
        }
        else if (std::abs(monom._coeff + 1.0) < EPSILON) {
            out << "-";
        }

        bool hasVars = false;
        char vars[] = { 'x', 'y', 'z' };

        for (int i = 0; i < VARS_COUNTER; ++i) {
            if (monom._powers[i] > 0) {
                hasVars = true;
                out << vars[i];
                if (monom._powers[i] > 1)
                    out << "^" << monom._powers[i];
            }
        }

        if (!hasVars) {
            if (std::abs(monom._coeff - 1.0) < EPSILON)
                out << "1";
            else if (std::abs(monom._coeff + 1.0) < EPSILON)
                out << "-1";
        }

        return out;
    }

    friend std::istream& operator>>(std::istream& in, Monom& monom) {
        std::string line;
        std::getline(in >> std::ws, line); 
        if (line.empty()) {
            monom = Monom(); 
            return in;
        }


        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());


        std::regex coeff_regex(R"(^([+-]?\d*\.?\d+))");
        std::smatch match;
        double coeff = 1.0;
        std::string rest;

        if (std::regex_search(line, match, coeff_regex) && match.position() == 0) {
            coeff = std::stod(match[1].str());
            rest = line.substr(match[0].length());
        }
        else {
            if (!line.empty() && line[0] == '-') {
                coeff = -1.0;
                rest = line.substr(1);
            }
            else if (!line.empty() && line[0] == '+') {
                coeff = 1.0;
                rest = line.substr(1);
            }
            else {
                coeff = 1.0;
                rest = line;
            }
        }

        std::regex var_regex(R"([xyz](?:\^(\d+))?)");
        auto var_begin = std::sregex_iterator(rest.begin(), rest.end(), var_regex);
        auto var_end = std::sregex_iterator();

        int powers[3] = { 0, 0, 0 }; 
        for (auto it = var_begin; it != var_end; ++it) {
            std::smatch mch = *it;
            std::string var = mch.str();
            char var_char = var[0];
            int exp = 1; 
            if (mch[1].matched)
                exp = std::stoi(mch[1].str());
            int idx = (var_char == 'x' ? 0 : (var_char == 'y' ? 1 : 2));
            powers[idx] += exp; 
        }


        monom._coeff = coeff;
        for (int i = 0; i < VARS_COUNTER; ++i)
            monom._powers[i] = powers[i];

        return in;
    }
};