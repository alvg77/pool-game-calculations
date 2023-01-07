#include <iostream>
#include "Line.h"
#include "Point.h"
#include "Vector.h"

Line::Line(const Point& p, const Vector& v) {
    this->A = v.y;
    this->B = -v.x;
    this->C = p.y * v.x - p.x * v.y;
}

Line::Line(const Point& p1, const Point& p2) {
    Vector v(p1, p2);

    this->A = v.y;
    this->B = -v.x;
    this->C = p1.y * v.x - p1.x * v.y;
}

Line::Line(const Line &other)
    : A(other.A), B(other.B), C(other.C)
{}

bool Line::are_parallel(const Line& other) const {
    Vector v1(-this->B, this->A);
    Vector v2(-other.B, other.A);
    return v1.is_colinear(v2);
}

bool Line::is_orthogonal(const Line& other) const {
    return ((-this->B) * this->A + other.A * (-other.B)) == 0;
}

double Line::findAngleCosine(const Line &other) {
    Vector v1(-this->B, this->A);
    Vector v2(-other.B, other.A);
    return v1.findAngleCosine(v2);
}

Vector Line::colinear() const { return Vector(-this->B, this->A); }

Vector Line::orthogonal() const { return Vector(this->A, this->B); }

Line Line::parallel(const Point p) const { return Line(p, this->colinear()); }

Line Line::orthogonal(const Point p) const {
    std::cout << this->A << " " << this->B << std::endl;
    return Line(p, this->orthogonal());
}

Point Line::intersection(const Line& other) const {
    double x = (this->B * other.C - other.B * this->C) / (this->A * other.B - other.A * this->B);
    double y = (this->C * other.A - other.C * this->A) / (this->A * other.B - other.A * this->B);

    if (x == -0) {
        x = 0;
    } else if (y == -0) {
        y = 0;
    } 

    return Point(x, y);
}

double Line::getA() const {
    return A;
}

double Line::getB() const {
    return B;
}

double Line::getC() const {
    return C;
}

void Line::setA(double A) {
    this->A = A;
}

void Line::setB(double B) {
    this->B = B;
}

void Line::setC(double C) {
    this->C = C;
}