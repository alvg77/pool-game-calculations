#include <valarray>
#include <ostream>
#include <istream>
#include <iostream>
#include "Vector.h"

Vector::Vector(double x, double y) : x(x), y(y) {}

Vector::Vector(const Point& p1, const Point& p2) {
    x = p1.x - p2.x;
    y = p1.y - p2.y;
}

Vector::~Vector() {}

Vector Vector::sum(const Vector& other) const {
    return Vector(this->x + other.x, this->y + other.y);
}

Vector Vector::times_num(int num) const {
    return Vector(this->x * num, this->y * num);
}

bool Vector::is_colinear(const Vector& other) const {
    return (this->x * other.y) == (this->y * other.x);
}

double Vector::length() const {
    return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

int Vector::dot_product(const Vector& other) const {
    return (this->x * other.x) + (this->y * other.y);
}

Vector Vector::multiply(double power) {
    return Vector(x * power, y * power);
}

double Vector::findAngleCosine(const Vector &other) {
    return ( this->dot_product(other) ) / ( this->length() * other.length() );
}

bool Vector::is_opposite(const Vector &other) const {
    // computers are stupid and cannot do math
    // when dealing with really small numbers such as -8.8817841970012523e-16
    return (std::signbit(this->x) != std::signbit(other.x)) &&
            (std::signbit(this->y)) != std::signbit(other.y);
}

bool Vector::is_null_vector() const {
    if (std::abs(x) < 0.0000001 && std::abs(y) < 0.0000001) {
        return true;
    }
    return false;
}

int area(const Vector &v1, const Vector &v2) {
    Vector v3 = v1.sum(v2);

    double l1 = v1.length();
    double l2 = v2.length();
    double l3 = v3.length();

    // от трите страни намираме полупериметъра, който ще е необходим при
    // намирането на лицето чрез хероновата формула
    double p = (l1 + l2 + l3) / 2;

    // използваме хероновата формула за да намерим лицето
    return sqrt(p * (p - l1) * (p - l2) * (p - l3));
}

double Vector::getX() const { return x; }

double Vector::getY() const { return y; }

inline std::ostream& operator<<(std::ostream& out, const Vector& v) {
    out << "(" << v.x << ", " << v.y << ")";
    return out;
}

inline std::istream& operator>>(std::istream& in, Vector& v) {
    in >> v.x;
    in >> v.y;
    return in;
}