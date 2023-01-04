#include <iostream>
#include "components/Table.h"

int main() {
    Table t (
        Point(0, 0),
        Point(320, 0),
        Point(320, 160),
        Point(0, 160),
        Point(230, 50),
        5
    );

    Point p = t.impact(2, Point(200, 20));
    std::cout << p.x << " " << p.y << std::endl;
    return 0;
}