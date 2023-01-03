#include "Table.h"

#include <cmath>
#include <iostream>

#include "../utils/Triangle.h"

Table::Table(const Point &p1, const Point &p2, const Point &p3, const Point &p4,
             const Point &startingPosition, double radius)
    : startingPosition(startingPosition), ball(startingPosition, radius) {
    
    double dif = (ball.getRadius() * sqrt(2));

    points[0].x = p1.x + dif;
    points[0].y = p1.y + dif;

    points[1].x = p2.x - dif;
    points[1].y = p2.y + dif;

    points[2].x = p3.x - dif; 
    points[2].y = p3.y - dif;

    points[3].x = p4.x + dif;
    points[3].y = p4.y - dif;

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
    
    double dif = (ball.getRadius() * sqrt(2));

    points[0].x = p1.x + dif;
    points[0].y = p1.y + dif;

    points[1].x = p2.x - dif;
    points[1].y = p2.y + dif;

    points[2].x = p3.x - dif; 
    points[2].y = p3.y - dif;

    points[3].x = p4.x + dif;
    points[3].y = p4.y - dif;

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

Point Table::impact(double power, const Point &direction) {
    
    if (power < 1 || power > 10) {
        throw std::invalid_argument("Invalid value for power provided");
    }

    Vector directionVector(direction, ball.getPosition());
    // finish this
    std::cout << "Direction vector: " << directionVector.getX() << " " << directionVector.getY() << std::endl;

    Point newPosition = ball.getPosition();
    newPosition.x += directionVector.getX() * power;
    newPosition.y += directionVector.getY() * power;


    if (isInTable(newPosition)) {
        ball.setPosition(newPosition);
        std::cout << "Ball is in table" << std::endl;
    } else {
        while (!isInTable(newPosition)) {
            // if (isBallInHole()) {
            //     ball.setPosition(startingPosition);
            //     newPosition = startingPosition;
            //     break;
            // }
            
            uint8_t sideIndex = findSideOfImpactIndex(newPosition);
            Line cross(newPosition, directionVector);
            Point impactPoint = cross.intersection(sides[sideIndex]);
            std::cout << "Ball bounces off at: " << impactPoint.x << " " << impactPoint.y << std::endl;        
            newPosition = symmetric(impactPoint, sides[sideIndex]);
            getchar();    
        }
    }

    if (isBallInHole()) {
        ball.setPosition(startingPosition);
        newPosition = startingPosition;
    }

    return newPosition;
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

uint8_t Table::findSideOfImpactIndex(const Point &direction) {
    if (direction.x < points[0].x && direction.x < points[3].x) {
        return 3;
    } else if (direction.x > points[1].x && direction.x > points[2].x) {
        return 1;
    } else if (direction.y < points[0].y && direction.y < points[1].y) {
        return 0;
    } else if (direction.y > points[2].y && direction.y > points[3].y) {
        return 2;
    }

    return -1;
}

// finish the function
bool Table::compareDoubles(double a, double b) {
    return std::abs(a - b) < 0.0000001;
}