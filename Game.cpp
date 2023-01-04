#include "Game.h"
#include <iostream>

Game::Game() : table(nullptr) {}

Game::~Game() {
    delete table;
}

void Game::start() {
    while (true) {
        menu();
    }
}

void Game::initTable() {
    // Point points[4];

    // std::cout << "Enter playing table angle points' coordinates: " << std::endl;
    // for (int i = 0; i < 4; i++) {
    //     std::cout << "Enter point " << std::to_string(i + 1) << ":"
    //               << std::endl;
    //     std::cin >> points[i];
    // }

    // double diameter;
    // std::cout << "Enter ball diameter: " << std::endl;
    // std::cin >> diameter;

    // Point startingBallPosition;
    // std::cout << "Enter starting ball position: " << std::endl;
    // std::cin >> startingBallPosition;

    // table = new Table(points[0], points[1], points[2], points[3], startingBallPosition, diameter / 2);
}

void Game::menu() { 
    std::cout << "---Menu---" << std::endl; 
    
}
