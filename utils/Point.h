#ifndef POINT_H
#define POINT_H

#include <iostream>

struct Point {
    double x;
    double y;
    
    Point();
    Point(double x, double y);
    Point(const Point& other);
    Point multiply(double power) const;
};

double distance(const Point &p1, const Point &p2);

#endif