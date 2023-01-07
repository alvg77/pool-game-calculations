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

    std::vector<Point> points;
    std::vector<Line> sides;

    double surface;

    double sinA, cosA;
    Point rotationPoint;

    void findAngleWithOX(const Point &p1, const Point &p2);
    void findSides();
    void findRotatedCoordinates(std::vector<Point> points);
    Point rotatePoint(const Point &p) const;
    Point retrievePoint(const Point &p) const;

    bool isInTable(const Point &currentPosition) const;
    bool compareDoubles(double a, double b) const; // computers cannot do math
    bool isRectangle(const std::vector<Point> points) const;
    bool isBallInHole() const;

    std::pair<Vector, Line> findCollision(const Vector &directionVector) const;
public:
    Table();
    Table(const std::vector<Point> points, const Point &startingPosition, double radius);
    ~Table();

    void hitBall(double power, const Point &direction);

    void setCoordinates(std::vector<Point> points);
    void setStartingPosition(const Point &startingPosition);
    void setBallRadius(double radius);

    bool isUninitialized() const;

    Point getBallPosition() const;
    double getSurface() const;
    double getBallRadius() const;
    Point getStartingPosition() const;

    void resetBallPosition();

    inline friend std::ostream& operator<<(std::ostream& os, const Table& table) {
        os << "Table points: " << std::endl;

        double radius = table.ball.getRadius();
        Point points[4] = {
                Point(table.points[0].x - radius, table.points[0].y - radius),
                Point(table.points[1].x + radius, table.points[1].y - radius),
                Point(table.points[2].x + radius, table.points[2].y + radius),
                Point(table.points[3].x - radius, table.points[3].y + radius)
        };

        for (auto point: points) {
            os << table.retrievePoint(point) << std::endl;
        }

        os << "Ball centre: " << table.retrievePoint(table.ball.getPosition()) << std::endl;
        os << "Ball diameter: " << table.ball.getRadius() * 2 << std::endl;

        return os;
    }

    inline friend std::istream& operator>>(std::istream& in, Table& table) {
        std::vector<Point> points;
        Point point;
        double diameter;

        for (int i = 0; i < 4; i++) {
            in >> point;
            in.ignore();
            points.push_back(point);
        }

        in >> point;
        in.ignore();
        in >> diameter;
        in.ignore();
        table = Table(points, point, diameter / 2);

        return in;
    }

    inline friend std::istream& operator>>(std::istream& in, Table& table);
};

Point symmetric(const Point &p1, const Line &l);

#endif