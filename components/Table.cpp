
#include <stdexcept>
#include <valarray>
#include <iostream>
#include "Table.h"
#include "../utils/Triangle.h"
#include "../utils/Vector.h"
//h
//void Table::findAngleWithOX(const Point &p1, const Point &p2) {
//    Line ox (Point(0, 0), Point(1, 0));
//    Line side (p1, p2);
//    double angle = side.findAngle(ox);
//
//    sinA = sin(angle);
//    cosA = cos(angle);
//}
//
//Point Table::rotatePoint(const Point &p) {
//    double x = p.x * cosA - p.y * sinA;
//    double y = p.x * sinA + p.y * cosA;
//    return Point(x, y)
//}

Table::Table(const Point &p1, const Point &p2, const Point &p3, const Point &p4,
             const Point &startingPosition, double radius)
    : startingPosition(startingPosition), ball(startingPosition, radius) {

    points[0].x = p1.x + radius;
    points[0].y = p1.y + radius;

    points[1].x = p2.x - radius;
    points[1].y = p2.y + radius;

    points[2].x = p3.x - radius;
    points[2].y = p3.y - radius;

    points[3].x = p4.x + radius;
    points[3].y = p4.y - radius;

    sides[0] = Line(points[0], points[1]);
    sides[1] = Line(points[1], points[2]);
    sides[2] = Line(points[2], points[3]);
    sides[3] = Line(points[3], points[0]);

    surface = distance(points[0], points[1]) * distance(points[1], points[2]);

    if (!validateRectangle(p1, p2, p3, p4)) {
        throw std::invalid_argument("Table is not a rectangle with ratio 1:2");
    } else if (!isInTable(ball.getPosition())) {
        throw std::invalid_argument("Ball is not in table");
    }
}

Table::Table(const Point &p1, const Point &p2, const Point &p3, const Point &p4,
             const Ball &ball)
    : startingPosition(ball.getPosition()), ball(ball) {
    
    double radius = ball.getRadius();

    points[0].x = p1.x + radius;
    points[0].y = p1.y + radius;

    points[1].x = p2.x - radius;
    points[1].y = p2.y + radius;

    points[2].x = p3.x - radius;
    points[2].y = p3.y - radius;

    points[3].x = p4.x + radius;
    points[3].y = p4.y - radius;

    sides[0] = Line(points[0], points[1]);
    sides[1] = Line(points[1], points[2]);
    sides[2] = Line(points[2], points[3]);
    sides[3] = Line(points[3], points[0]);

    surface = floor(distance(points[0], points[1]) * distance(points[1], points[2]));
    
    if (!validateRectangle(p1, p2, p3, p4)) {
        throw std::invalid_argument("Table is not a rectangle with ratio 2:1");
    } else if (!isInTable(ball.getPosition())) {
        throw std::invalid_argument("Ball is not in table");
    }
}

Table::Table(const Table &other)
    : surface(other.surface),
      startingPosition(other.startingPosition),
      ball(other.ball) {
    for (int i = 0; i < 4; i++) {
        points[i] = other.points[i];
    }

    for (int i = 0; i < 4; i++) {
        sides[i] = other.sides[i];
    }
}

Table::~Table() {}

bool Table::isInTable(const Point &point) {
    double sum = 0;

    for (int i = 0; i < 4; i++) {
        sum += Triangle(points[i], points[(i + 1) % 4], point)
                   .getSurface();
    }
    return compareDoubles(surface, sum);
}

bool Table::validateRectangle(const Point &p1, const Point &p2, const Point &p3, const Point &p4) {
    // rectangle sides
    double AB = distance(p1, p2);
    double BC = distance(p2, p3);
    double CD = distance(p3, p4);
    double DA = distance(p4, p1);

    if (BC / AB != 0.5 || DA / CD != 0.5) {
        return false;
    }

    // diagonals
    double AC = distance(p1, p3);
    double BD = distance(p2, p4);

    // a polygon is a rectangle if the smaller sides are equal, the bigger sides
    // are equal and the diagonals are equal
    return AB == CD && BC == DA && AC == BD;
}

void Table::impact(double power, const Point &direction) {
    
    if (power < 1 || power > 10) {
        throw std::invalid_argument("Invalid value for power provided");
    }

    Vector directionVector(direction, ball.getPosition());
    directionVector = directionVector.multiply(power);
    // finish this
    std::cout << "Direction vector: " << directionVector.getX() << " " << directionVector.getY() << std::endl;

    Point newPosition = ball.getPosition();

    newPosition.x += directionVector.getX();
    newPosition.y += directionVector.getY();

    while (!isInTable(newPosition)) {
        std::pair<Vector, Line> collision = findCollision(directionVector);
        Vector collisionVector = collision.first;
        Line collisionSide = collision.second;
        Point collisionPoint = Point(collisionVector.getX(), collisionVector.getY());

        std::cout << "Collision vector: " << collisionVector.getX() << " " << collisionVector.getY() << std::endl;

        ball.setPosition(collisionPoint);

        if (isBallInHole()) {
            ball.setPosition(startingPosition);
            return;
        }

        std::cout << "Ball bounces off at: " << ball.getPosition() << " " << ball.getPosition() << std::endl;
        newPosition = symmetric(newPosition, collisionSide);
        directionVector = Vector(newPosition, ball.getPosition());
    }
    ball.setPosition(newPosition);
}

Point Table::getBallPosition() const {
    return ball.getPosition();
}

bool Table::isBallInHole() {
    uint8_t count = 0;
    for (int i = 0; i < 4; i++) {
        if (sides[i].getA() * ball.getPosition().x +
            sides[i].getB() * ball.getPosition().y + sides[i].getC()) {
            count++;
        }
    }

    return count == 2;
}

std::pair<Vector, Line> Table::findCollision(const Vector &directionVector) {
    Line crossLine(ball.getPosition(), directionVector);
    std::vector< std::pair<Vector, Line> > pairs;

    for (auto side: sides) {
        Point intersection = crossLine.intersection(side);
        Vector v(intersection, ball.getPosition());
        if (!directionVector.is_opposite(v) && !std::isnan(intersection.x) && !std::isnan(intersection.y)) {
            pairs.push_back(std::make_pair(v, side));
        }
    }
    std::pair<Vector, Line> min = pairs[0];
    for (auto p = pairs.begin() +1; p != pairs.end(); p++) {
        if (p->first.length() < min.first.length()) {
            min = *p;
        }
    }

    return min;
}

// finish the function
bool Table::compareDoubles(double a, double b) {
    return std::abs(a - b) < 0.0000001;
}

Point symmetric(const Point &p1, const Line &l) {
    Vector orthogonal = l.orthogonal();
    Line orthLine (p1, orthogonal);
    Point intersection = l.intersection(orthLine);

    std::cout << "Intersection: " << intersection.x << " " << intersection.y << std::endl;

    return Point(2 * intersection.x - p1.x, 2 * intersection.y - p1.y);
}