
#include <stdexcept>
#include <valarray>
#include <iostream>
#include "Table.h"
#include "../utils/Triangle.h"

#include "Ball.h"

void Table::findAngleWithOX(const Point &p1, const Point &p2) {
    Line ox(Point(0, 0), Point(1, 0));
    Line side(p1, p2);

    // we find the angle between one of the sides of the table and the OX axis
    // we use the intersection of the two lines, as a point around which we will rotate all the points of the rectangle, making it parallel to the OX and OY axes
    // by using the first and the second point, like we do in the constructor we rotate one of the sides of the rectangle to OX
    rotationPoint = side.intersection(ox);

    // in the case where the tho lines are parallel, there are either endless intersections between them (they are the same line) or none
    // in that case the rotationPoint will be with coords (nan, nan)

    // we find the angle between the side and the OX axis
    // we do this by getting the collinear vectors of both lines and via their dot product we find the cosine of the angle between them
    cosA = side.findAngleCosine(ox);
    // we find the sine from the cosine
    sinA = sqrt(1 - cosA * cosA);
}

Point Table::rotatePoint(const Point &p) const {
    Point rotated(
            cosA * (p.x - rotationPoint.x) + sinA * (p.y - rotationPoint.y) + rotationPoint.x, /* x */
            -sinA * (p.x - rotationPoint.x) + cosA * (p.y - rotationPoint.y) + rotationPoint.y /* y */
    );

    // because some lines may be parallel and we might get nan values for the rotation point,cosine and sine
    // we check if the values are nan and if they are, we return the original point
    // we do this because when this happens the sides of the rectangle are already parallel to the OX and OY axes
    return std::isnan(rotated.x) && std::isnan(rotated.y) ? p : rotated;
}

Point Table::retrievePoint(const Point &p) const {
    Point retrieved(
            cosA * (p.x - rotationPoint.x) - sinA * (p.y - rotationPoint.y) + rotationPoint.x, /* x */
            sinA * (p.x - rotationPoint.x) + cosA * (p.y - rotationPoint.y) + rotationPoint.y  /* y */
    );

    // we retrieve the original point by rotating it back
    return std::isnan(retrieved.x) && std::isnan(retrieved.y) ? p : retrieved;
}

void Table::findSides() {
    // when we have already found the points of the rectangle, we can find the sides
    for (auto pointIt = this->points.begin(); pointIt != this->points.end(); pointIt++) {
        sides.push_back(Line(*pointIt, *(pointIt + 1 == this->points.end() ? this->points.begin() : pointIt + 1)));
    }
}

void Table::findRotatedCoordinates(std::vector<Point> points) {
    double radius = ball.getRadius();

    if (points.size() != 4) {
        throw std::invalid_argument("Table must have 4 points");
    }

    // here we rotate the points so they become parallel to the OX and OY axes
    // we do this so we can shrink the field more easily
    // and why do we shrink the field in the first place?
    // because we want to make sure that the ball will bounce off the walls of the table with its radius, rather than it's center
    // when we shrink the field we wont have to worry which point of the circle is going to hit the wall
    // using this method we are sure that the ball will bounce off the walls with its center

    this->points.push_back(rotatePoint(points[0]));
    this->points[0].x += radius;
    this->points[0].y += radius;

    this->points.push_back(rotatePoint(points[1]));
    this->points[1].x -= radius;
    this->points[1].y += radius;

    this->points.push_back(rotatePoint(points[2]));
    this->points[2].x -= radius;
    this->points[2].y -= radius;

    this->points.push_back(rotatePoint(points[3]));
    this->points[3].x += radius;
    this->points[3].y -= radius;
}

Table::Table()
        : startingPosition(Point(0, 0)), ball(Point(0, 0), 0), surface(0), sinA(0), cosA(0), rotationPoint(0, 0) {}

Table::Table(std::vector<Point> points, const Point &startingPosition, double radius) {
    if (!isRectangle(points)) {
        throw std::invalid_argument("Table is not a valid rectangle");
    }
    // we find the sine, cosine and intersection point, needed for the rotation of the rectangle points
    findAngleWithOX(points[0], points[1]);
    // we rotate the starting position of the ball
    this->startingPosition = rotatePoint(startingPosition);
    this->ball = Ball(this->startingPosition, radius);
    // we find what the points of the shrinked rotated rectangle
    findRotatedCoordinates(points);
    // we find the sides of the rectangle
    this->surface = distance(this->points[0], this->points[1]) * distance(this->points[1], this->points[2]);
    // check if the ball is in the table
    if (!isInTable(this->startingPosition)) {
        throw std::invalid_argument("Ball is not in table");
    }
    // we find the sides of the rectangle (the sides are lines)
    findSides();
}

Table::~Table() {}

bool Table::isUninitialized() const {
    // if surface is 0, then the table is uninitialized
    return surface == 0;
}

bool Table::isInTable(const Point &currentPosition) const {
    double sum = 0;
    // in order to find whether the ball is in the table we need to find the sum of the triangles formed by the ball's center and the sides of the table
    // then we compare the sum of the triangle areas to the area of the table
    for (int i = 0; i < 4; i++) {
        sum += Triangle(points[i], points[(i + 1) % 4], currentPosition).getSurface();
    }
    return compareDoubles(surface, sum);
}

bool Table::isRectangle(const std::vector<Point> points) const {
    if (points.size() != 4) {
        return false;
    }

    // we find the lengths of the sides of the rectangle
    // rectangle sides
    double AB = distance(points[0], points[1]);
    double BC = distance(points[1], points[2]);
    double CD = distance(points[2], points[3]);
    double DA = distance(points[3], points[0]);

    // we validate the ratio
    if (BC / AB != 0.5 || DA / CD != 0.5) {
        return false;
    }

    // diagonals
    double AC = distance(points[0], points[2]);
    double BD = distance(points[1], points[3]);

    // a polygon is a rectangle if the smaller sides are equal, the bigger sides
    // are equal and the diagonals are equal
    return AB == CD && BC == DA && AC == BD;
}

void Table::hitBall(double power, const Point &direction) {

    if (power < 1 || power > 10) {
        throw std::invalid_argument("Invalid value for power provided");
    }
    // we rotate the direction of the hit
    Point rotatedDirection = rotatePoint(direction);
    // we construct a vector with the rotated direction
    Vector directionVector(rotatedDirection, ball.getPosition());
    // we multiply the vector by the power -> it describes the movement of the ball
    directionVector.multiply(power);

    // we get the next position of the ball
    Point newPosition = ball.getPosition();
    newPosition.x += directionVector.getX();
    newPosition.y += directionVector.getY();

    while (!isInTable(newPosition)) {
        // if the next position is not in the table we find where it collides
        std::pair<Vector, Line> collision = findCollision(directionVector);
        // this vector describes the movement of the ball from its current position to the point collision
        Vector collisionVector = collision.first;
        // this is the side of the table where the ball will have collided with
        Line collisionSide = collision.second;
        // we calculate the new position of the ball
        Point collisionPoint = Point(collisionVector.getX() + ball.getPosition().x,
                                     collisionVector.getY() + ball.getPosition().y);

        ball.setPosition(collisionPoint);
        // when a ball collides it might be colliding with two sides -> it is in a corner
        if (isBallInHole()) {
            // if the ball is in a hole we reset it to the starting position
            resetBallPosition();
            std::cout << "Ball is in hole" << std::endl;
            return;
        }

        std::cout << "Ball bounces off at: " << retrievePoint(ball.getPosition()) << std::endl;
        // we calculate the new direction of the ball after the collision
        newPosition = symmetric(newPosition, collisionSide);
        directionVector = Vector(newPosition, ball.getPosition());
    }
    ball.setPosition(newPosition);
}

// if the ball is colliding with two sides, then it is in a corner
bool Table::isBallInHole() const {
    uint8_t count = 0;
    for (int i = 0; i < 4; i++) {
        if (compareDoubles(
                sides[i].getA() * ball.getPosition().x + sides[i].getB() * ball.getPosition().y + sides[i].getC(), 0)) {
            count++;
        }
    }

    return count == 2;
}

// we find the collision point
std::pair<Vector, Line> Table::findCollision(const Vector &directionVector) const {
    // we create a line from the ball's position and the direction of the hit
    Line crossLine(ball.getPosition(), directionVector);
    std::vector<std::pair<Vector, Line> > pairs;

    for (auto side: sides) {
        // we find the intersection of this line with the sides (lines) of the table
        Point intersection = crossLine.intersection(side);
        // we find the vector to every intersection point
        Vector v(intersection, ball.getPosition());
        // if the vector is in the opposite direction of the direction of the hit, then we ignore it
        // the crossLine might be parallel to some of the rectangle lines
        // meaning that we are going to receive a nan value
        // we ignore this case too
        if (!directionVector.is_opposite(v) && !std::isnan(intersection.x) && !std::isnan(intersection.y) &&
            !v.is_null_vector()) {
            pairs.push_back(std::make_pair(v, side));
        }
    }
    std::pair<Vector, Line> min = pairs[0];
    for (auto p = pairs.begin() + 1; p != pairs.end(); p++) {
        // we find the vector with the smallest length
        // this is the vector that describes the movement of the ball from its current position to the point of collision
        if (p->first.length() < min.first.length()) {
            min = *p;
        }
    }

    return min;
}

// computers cannot do floating point operations perfectly
bool Table::compareDoubles(double a, double b) const {
    return std::abs(a - b) < 0.0000001;
}

// we find the symmetric point
Point symmetric(const Point &p1, const Line &l) {
    Vector orthogonal = l.orthogonal();
    Line orthLine(p1, orthogonal);
    Point intersection = l.intersection(orthLine);

    return Point(2 * intersection.x - p1.x, 2 * intersection.y - p1.y);
}

// we set new coordinates
void Table::setCoordinates(std::vector<Point> points) {
    // save the previous ones in case the new ones are invalid
    std::vector<Point> prevPoints(this->points);
    std::vector<Line> prevSides(this->sides);
    // change the coordinates and the sides
    this->points.clear();
    findRotatedCoordinates(points);
    this->sides.clear();
    findSides();
    surface = distance(this->points[0], this->points[1]) * distance(this->points[1], this->points[2]);

    // if the new coordinates are invalid, we reset the old ones
    if (!isInTable(ball.getPosition())) {
        this->points = prevPoints;
        this->sides = prevSides;
        throw std::invalid_argument("Cannot change coordinates! Ball is not in table");
    }
}

void Table::setStartingPosition(const Point &startingPosition) {
    if (isInTable(rotatePoint(startingPosition))) {
        this->startingPosition = rotatePoint(startingPosition);
    } else {
        throw std::invalid_argument("Starting position is not in table");
    }
}

void Table::setBallRadius(double radius) {
    if (radius < 0) {
        throw std::invalid_argument("Ball diameter cannot be negative");
    }
    // save prev coords
    std::vector<Point> prevPoints(this->points);
    std::vector<Line> prevSides(this->sides);
    double prevRadius = ball.getRadius();
    double difference = radius - prevRadius;

    ball.setRadius(radius);

    // resize the field according to the new radius

    points[0].x += difference;
    points[0].y += difference;
    points[1].x -= difference;
    points[1].y += difference;
    points[2].x -= difference;
    points[2].y -= difference;
    points[3].x += difference;
    points[3].y -= difference;

    findSides();

    // if the resized field is invalid, we reset the old one
    if (!isRectangle(points)) {
        this->points = prevPoints;
        this->sides = prevSides;
        ball.setRadius(prevRadius);
        throw std::invalid_argument("Cannot change ball radius! Table is not a rectangle");
    }
}

Point Table::getBallPosition() const {
    return retrievePoint(ball.getPosition());
}

double Table::getSurface() const {
    return surface;
}

double Table::getBallRadius() const {
    return ball.getRadius();
}

Point Table::getStartingPosition() const {
    return retrievePoint(startingPosition);
}

void Table::resetBallPosition() {
    ball.setPosition(startingPosition);
}