#include <valarray>
#include "Triangle.h"

Triangle::Triangle(Point p1, Point p2, Point p3) {
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
}

Triangle::~Triangle() {}

double Triangle::getSurface() {
    double side1 = distance(points[0], points[1]);
    double side2 = distance(points[1], points[2]);
    double side3 = distance(points[2], points[0]);
    double p = (side1 + side2 + side3) / 2;
    return sqrt(p * (p - side1) * (p - side2) * (p - side3));
}