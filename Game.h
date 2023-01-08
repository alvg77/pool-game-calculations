#ifndef GAME_H
#define GAME_H
#include "components/Table.h"

class Game {
   private:
    Table table;
    void setTableCoords();
    void setBallDiameter();
    void setStartingBallPosition();
    void printTable();
    void hitBall();
    void menu();
    void resetBall();
    void initTable();
    bool simple();
    bool complex();
   public:
    Game();
    ~Game();
    void start();
};

#endif