#include "../lib_Monom/Monom.h"
#include "../lib_List/List.h"

#define VARS_COUNTER 3

class Polynom {
    List<Monom> _polynom;
    std::string _name;

public:
    Polynom();
    explicit Polynom(const Monom& monom);
    explicit Polynom(const std::string& str);
    Polynom(const Polynom& other);
    ~Polynom() = default;

    void set_name(const std::string& name);

    bool is_zero() const;

    Polynom add(const Polynom& other) const;
    Polynom sub(const Polynom& other) const;
    Polynom mult(const Polynom& other) const;
    Polynom div(const Polynom& other) const;
    Polynom mod(const Polynom& other) const;
    std::pair<Polynom, Polynom> divmod(const Polynom& other) const;

    Polynom add_a_monom(const Monom& other) const;
    Polynom sub_a_monom(const Monom& other) const;
    Polynom mult_by_monom(const Monom& other) const;
    Polynom div_by_monom(const Monom& other) const;
    Polynom mod_by_monom(const Monom& other) const;
    std::pair<Polynom, Polynom> divmod_by_monom(const Monom& other) const;

    Polynom add_a_number(double other) const;
    Polynom sub_a_number(double other) const;
    Polynom mult_by_number(double other) const;
    Polynom div_by_number(double other) const;

    double value_at_the_point(double x, double y, double z) const;

    Polynom operator+(const Polynom& other) const;
    Polynom operator-(const Polynom& other) const;
    Polynom operator*(const Polynom& other) const;
    Polynom operator/(const Polynom& other) const;
    Polynom operator%(const Polynom& other) const;

    Polynom operator+(const Monom& other) const;
    Polynom operator-(const Monom& other) const;
    Polynom operator*(const Monom& other) const;
    Polynom operator/(const Monom& other) const;
    Polynom operator%(const Monom& other) const;

    //friend Polynom operator+(const Monom& monom, const Polynom& polynom);
    //friend Polynom operator-(const Monom& monom, const Polynom& polynom);
    //friend Polynom operator*(const Monom& monom, const Polynom& polynom);
    //friend Polynom operator/(const Monom& monom, const Polynom& polynom);
    //friend Polynom operator%(const Monom& monom, const Polynom& polynom);

    Polynom operator+(double other) const;
    Polynom operator-(double other) const;
    Polynom operator*(double other) const;
    Polynom operator/(double other) const;

    //friend Polynom operator+(double number, const Polynom& polynom);
    //friend Polynom operator-(double number, const Polynom& polynom);
    //friend Polynom operator*(double number, const Polynom& polynom);
    //friend Polynom operator/(double number, const Polynom& polynom);

    Polynom& operator+=(const Polynom& other);
    Polynom& operator-=(const Polynom& other);
    Polynom& operator*=(const Polynom& other);
    Polynom& operator/=(const Polynom& other);

    Polynom& operator+=(const Monom& other);
    Polynom& operator-=(const Monom& other);
    Polynom& operator*=(const Monom& other);
    Polynom& operator/=(const Monom& other);

    Polynom& operator+=(double other);
    Polynom& operator-=(double other);
    Polynom& operator*=(double other);
    Polynom& operator/=(double other);

    bool operator==(const Polynom& other) const;
    bool operator!=(const Polynom& other) const;

    Polynom& operator=(const Polynom& other);

    friend std::ostream& operator<<(std::ostream& out, const Polynom& polynom);

private:
    bool check_powers(const Polynom& other) const;   // вспомогательная для деления
    bool can_divide(const Monom& dividend, const Monom& divisor) const;
};