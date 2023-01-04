#include <valarray>
#include "Point.h"
#include "Line.h"

Point::Point() : x(0), y(0) {}

Point::Point(double x, double y) : x(x), y(y) {}

Point::Point(const Point &other) : x(other.x), y(other.y) {}

double distance(const Point &p1, const Point &p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

Line Test() {
    Point p1 (10, 10);
    Point p2 (20, 20);

    return Line(p1, p2);
}