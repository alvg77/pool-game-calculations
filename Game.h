#ifndef GAME_H
#define GAME_H
#include "components/Table.h"

class Game {
   private:
    Table *table;
    void setTableCoords();
    void setBallDiameter();
    void setStartingBallPosition();
    void hitBall();
    void displayTableParams();
    void menu();
   public:
    Game();
    ~Game();
    void start();
};

#endif