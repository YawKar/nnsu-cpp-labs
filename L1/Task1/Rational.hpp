#pragma once
#include <iostream>

class Rational {
public:
    // default constructor
    Rational ();
    Rational (long long numerator, long long denominator);
    Rational (long long integer);
    // copy initialization
    Rational (const Rational& other);
    ~Rational ();

    // assignment overload
    Rational& operator=(const Rational& other);

    // arithmetic operations
    Rational operator+(const Rational& other);
    Rational operator-(const Rational& other);
    Rational operator*(const Rational& other);
    Rational operator/(const Rational& other);

    // base comparators
    bool operator<(const Rational& other);
    bool operator==(const Rational& other);
    // dependant comparators
    bool operator>(const Rational& other);
    bool operator<=(const Rational& other);
    bool operator>=(const Rational& other);
    bool operator!=(const Rational& other);
    
    // io overloads
    friend std::ostream& operator<<(std::ostream& out, const Rational& r);
    friend std::istream& operator>>(std::istream& in, Rational& r);

    // getters
    long long get_numerator() const;
    long long get_denominator() const;

private:
    long long numerator = 0;
    long long denominator = 1;
    
    void normalize();
    long long gcd(long long a, long long b) const;
    long long lcm(long long a, long long b) const;
};