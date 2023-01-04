#include "Point.h"

#include "Line.h"
#include <cmath>

Point::Point() : x(0), y(0) {}

Point::Point(double x, double y) : x(x), y(y) {}

Point::Point(const Point &other) : x(other.x), y(other.y) {}

double distance(const Point &p1, const Point &p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

Point symmetric(const Point &p1, const Line &l) {
    Vector orthogonal = l.orthogonal();
    Line perpendicular(p1, orthogonal);
    Point intersection = l.intersection(perpendicular);

    return Point(2 * intersection.x - p1.x, 2 * intersection.y - p1.y);
}