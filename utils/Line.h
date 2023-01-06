#ifndef LINE_H
#define LINE_H


#include <ostream>
#include "Vector.h"

class Line {
    double A, B, C;

   public:

    Line(double A = 0, double B = 0, double C = 0) : A(A), B(B), C(C) {}
    Line(const Point& p, const Vector& v);
    Line(const Point& p1, const Point& p2);
    Line(const Line& other);

    bool are_parallel(const Line& other) const;
    bool is_orthogonal(const Line& other) const;
    Point intersection(const Line& other) const;
    
    double getA() const;
    double getB() const;
    double getC() const;

    void setA(double A);
    void setB(double B);
    void setC(double C);

    Vector colinear() const;
    Vector orthogonal() const;

    Line parallel(const Point p) const;
    Line orthogonal(const Point p) const;

    double findAngle(const Line &other);

    friend std::ostream& operator<<(std::ostream& out, const Line& l);
    friend std::istream& operator>>(std::istream& in, Line& l);
};

#endif