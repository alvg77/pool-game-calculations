#ifndef TABLE_H
#define TABLE_H

#include <cstdint>
#include <vector>
#include "Ball.h"
#include "../utils/Point.h"
#include "../utils/Line.h"

class Table {
   private:
    Ball ball;
    Point startingPosition;
    Point points[4];
    Line sides[4];
    double surface;

    double sinA, cosA;
    Point rotationPoint;

    void findAngleWithOX(const Point &p1, const Point &p2);
    Point rotatePoint(const Point &p);
    bool isInTable(const Point& point);
    bool compareDoubles(double a, double b); // computers cannot do math
    bool validateRectangle(const Point &p1, const Point &p2, const Point &p3, const Point &p4);
    bool isBallInHole();

    std::pair<Vector, Line> findCollision(const Vector &directionVector);
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
    void impact(double power, const Point& direction);
    Point getBallPosition() const;
    Point retrievePoint(const Point &p);
};

Point symmetric(const Point &p1, const Line &l);

#endif