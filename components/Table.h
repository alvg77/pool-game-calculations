#ifndef TABLE_H
#define TABLE_H

#include <cstdint>
#include "Ball.h"
#include "../utils/Point.h"
#include "../utils/Line.h"

class Table {
   private:
    Ball ball;
    Point startingPosition;
    Point points[4];
    double surface;
    Line sides[4];

    bool isInTable(const Point& point);
    bool compareDoubles(double a, double b); // computers cannot do math
    bool validateRectangle(const Point &p1, const Point &p2, const Point &p3, const Point &p4);
    bool isBallInHole();
    uint8_t findSideOfImpactIndex(const Point &direction);
    Point findPointOfImpact(const Point &curr_position, const Point &direction, uint8_t sideIndex);
    Point findSymmetric(const Point &direction, uint8_t sideIndex);
   public:

    friend class Line;

    Table(const Point& p1, const Point& p2, const Point& p3, const Point& p4,
          const Point& startingPosition, double radius);
    Table(const Point& p1, const Point& p2, const Point& p3, const Point& p4,
          const Ball& ball);
    Table(const Table& other);
    ~Table();
    Point impact(double power, const Point& direction);
};

Point symmetric(const Point &p1, const Line &l);

#endif