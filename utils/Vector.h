#ifndef Vector_H
#define Vector_H


#include "Point.h"

class Vector {
   private:
    double x;
    double y;

   public:
    Vector(double x, double y);
    Vector(const Point& p1, const Point& p2);
    ~Vector();
    Vector sum(const Vector& other) const;
    bool is_colinear(const Vector& other) const;
    bool is_null_vector() const;
    double length() const;
    int dot_product(const Vector& other) const;
    void multiply(double power);
    double findAngleCosine(const Vector& other);
    bool is_opposite(const Vector& other) const;
    double getX() const;
    double getY() const; 

    friend class Line;
    friend std::ostream& operator<<(std::ostream& os, const Vector& c);
    friend std::istream& operator>>(std::istream& in, Vector& v);
};

int area(const Vector &v1, const Vector &v2);

#endif