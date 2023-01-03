#ifndef BALL_H
#define BALL_H

#include "../utils/Point.h"

class Ball {
   private:
    Point position;
    const double radius;

   public:
    Ball();
    Ball(const Point& startingPosition, double radius);
    ~Ball();
    Point getPosition() const;
    void setPosition(const Point &position);
    double getRadius() const;
};

#endif