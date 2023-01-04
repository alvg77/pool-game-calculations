#ifndef POINT_H
#define POINT_H

#include <iostream>
#include "Line.h"

struct Point {
    double x;
    double y;
    
    Point();
    Point(double x, double y);
    Point(const Point& other);
};

double distance(const Point &p1, const Point &p2);
Point symmetric(const Point &p1, const Line &l);

#endif