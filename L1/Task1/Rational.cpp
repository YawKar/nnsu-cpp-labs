#include "Rational.hpp"
#include <stdexcept>

Rational::Rational() {}

Rational::Rational(long long _numerator, long long _denominator) : 
    numerator(_numerator), denominator(_denominator) {
    if (!denominator)
        throw std::invalid_argument("Received zeroed denominator");
    normalize();
}

Rational::Rational(long long integer) {
    numerator = integer;
    denominator = 1;
}

Rational::Rational(const Rational& other) {
    numerator = other.numerator;
    denominator = other.denominator;
}

Rational::~Rational() {}

long long Rational::get_numerator() const {
    return numerator;
}

long long Rational::get_denominator() const {
    return denominator;
}

long long Rational::gcd(long long a, long long b) const {
    if (a == 0 || b == 0)
        return a | b;
    return gcd(b % a, a);
}

long long Rational::lcm(long long a, long long b) const {
    return a / gcd(a, b) * b;
}

void Rational::normalize() {
    if (numerator == 0) {
        denominator = 1;
        return;
    }
    if (denominator < 0) {
        numerator *= -1;
        denominator *= -1;
    }
    long long common_divs = gcd(abs(numerator), denominator);
    numerator /= common_divs;
    denominator /= common_divs;
}

Rational& Rational::operator=(const Rational& other) {
    if (this == &other)
        return *this;
    numerator = other.numerator;
    denominator = other.denominator;
    return *this;
}

Rational Rational::operator+(const Rational& other) {
    if (numerator == 0)
        return other;
    if (other.numerator == 0)
        return *this;
    long long result_denominator = lcm(denominator, other.denominator);
    long long result_numerator = numerator * (result_denominator / denominator) +
        other.numerator * (result_denominator / other.denominator);
    return Rational(result_numerator, result_denominator);
}

Rational Rational::operator-(const Rational& other) {
    if (numerator == 0)
        return Rational(-other.numerator, other.denominator);
    if (other.numerator == 0)
        return *this;
    long long result_denominator = lcm(denominator, other.denominator);
    long long result_numerator = numerator * (result_denominator / denominator) -
        other.numerator * (result_denominator / other.denominator);
    return Rational(result_numerator, result_denominator);
}

Rational Rational::operator*(const Rational& other) {
    if (numerator == 0)
        return *this;
    if (other.numerator == 0)
        return other;
    return Rational(numerator * other.numerator, denominator * other.denominator);
}

Rational Rational::operator/(const Rational& other) {
    if (other.numerator == 0)
        throw std::logic_error("Divide by zero exception");
    if (numerator == 0)
        return *this;
    return Rational(numerator * other.denominator, denominator * other.numerator);
}

bool Rational::operator<(const Rational& other) {
    long long least_common_denominator = lcm(denominator, other.denominator);
    return numerator * (least_common_denominator / denominator) < other.numerator * (least_common_denominator / other.denominator);
}

bool Rational::operator==(const Rational& other) {
    return numerator == other.numerator && denominator == other.denominator;
}

bool Rational::operator>(const Rational& other) {
    return !(*this < other) && !(*this == other);
}

bool Rational::operator<=(const Rational& other) {
    return !(*this > other);
}

bool Rational::operator>=(const Rational& other) {
    return !(*this < other);
}

bool Rational::operator!=(const Rational& other) {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const Rational& r) {
    out << r.get_numerator() << '/' << r.get_denominator();
    return out;
}

std::istream& operator>>(std::istream& in, Rational& r) {
    in >> r.numerator >> r.denominator;
    if (!r.denominator) {
        throw std::invalid_argument("Received zeroed denominator");
    }
    r.normalize();
    return in;
}