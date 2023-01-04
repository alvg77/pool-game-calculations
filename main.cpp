#include <iostream>
#include "components/Table.h"

int main() {
    Table t (
        Point(0, 0),
        Point(320, 0),
        Point(320, 160),
        Point(0, 160),
        Point(300, 60),
        0
    );

    Point p = t.impact(3, Point(250, 30));
    std::cout << p.x << " " << p.y << std::endl;
    return 0;
}