#ifndef GAME_H
#define GAME_H
#include "components/Table.h"

class Game {
   private:
    Table *table;
    void initTable();    
    void menu();
    // void reset();
   public:
    Game();
    ~Game();
    void start();
};

#endif