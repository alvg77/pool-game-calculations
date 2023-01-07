#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Point.h"

class Triangle {
   private:
    Point points[3];
   public:
    Triangle(Point p1, Point p2, Point p3);
    ~Triangle();
    double getSurface();
};

#endif