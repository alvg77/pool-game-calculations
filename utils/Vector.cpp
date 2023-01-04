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

// TODO - returns the product of a vector and a number (which is also e vector)
Vector Vector::times_num(int num) const {
    return Vector(this->x * num, this->y * num);
}

// TODO - returns a boolean value, answering the question whether the current
// vector and another ("other") are collinear
bool Vector::is_colinear(const Vector& other) const {
    // 2 вектора са колинеарни, ако лежат на успоредни прави
    // при колинеарност на вектори, единият може да бъде представен като
    // произведение на другия с число this (x, y) е колинеарен на other = n*this
    // (n*x, n*y) оттук следва пропорцията this->x/this->y = other.x/other.y
    // => this->x * other.y = this->y * other.x
    return (this->x * other.y) == (this->y * other.x);
}

// TODO - returns the length of the current vector
double Vector::length() const {
    return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

// TODO - returns the dot(scalar) product of the current vector and another
int Vector::dot_product(const Vector& other) const {
    return (this->x * other.x) + (this->y * other.y);
}

Vector Vector::multiply(double power) {
    return Vector(x * power, y * power);
}

// TODO - finds the area of a triangle given two vectors denoting two of its
// sides
int area(const Vector &v1, const Vector &v2) {
    // намираме третия вектор от триъгълника, който е сума на предходните 2
    // v3 (v1.x + v2.x, v1.y + v2.y)
    // тази страна се явява хипотенуза
    Vector v3 = v1.sum(v2);

    // за да намерим дължините на страните на триъгълника, които са вектори,
    // използваме метода .length()
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