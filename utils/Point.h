#ifndef POINT_H
#define POINT_H

#include <ostream>
#include <istream>

struct Point {
    double x;
    double y;
    
    Point();
    Point(double x, double y);
    Point(const Point& other);
};

double distance(const Point &p1, const Point &p2);

std::ostream &operator<<(std::ostream &os, const Point &p);
std::istream &operator>>(std::istream &is, Point &p);

#endif