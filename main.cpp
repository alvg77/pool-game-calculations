#include <iostream>
#include "components/Table.h"

int main() {
    Table t (
        Point(60, -80),
        Point(220, 40),
        Point(160, 120),
        Point(0, 0),
        Point(90, -10),
        10
    );
    t.impact(1, Point(65, -45));
    t.impact(1, Point(40, -220));
    std::cout << t.retrievePoint(t.getBallPosition()) << std::endl;

    return 0;
}