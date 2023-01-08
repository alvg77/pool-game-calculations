#include "Game.h"
#include "utils/Point.h"
#include <iostream>

Game::Game() {}

Game::~Game() {}

void Game::start() {
    initTable();
    while (true) {
        char input;
        menu();
        std::cin >> input;
        std::cin.ignore();
        system("clear");
        try {
            switch (input) {
                case 'c':
                    setTableCoords();
                    break;
                case 'd':
                    setBallDiameter();
                    break;
                case 'p':
                    printTable();
                    std::cout << "Press enter to continue...";
                    std::cin.ignore();
                    break;
                case 's':
                    setStartingBallPosition();
                    break;
                case 'h':
                    hitBall();
                    std::cout << "Press enter to continue...";
                    std::cin.get();
                    break;
                case 'i':
                    initTable();
                    break;
                case 'r':
                    resetBall();
                    break;
                case 'q':
                    return;
                default:
                    std::cout << "Invalid input" << std::endl;
            }
        } catch (const std::exception &e) {
            std::cout << e.what() << std::endl;
            std::cin.ignore();
        }
        system("clear");
    }
}

void Game::initTable() {
    bool completed = false;
    do {
        char input;
        std::cout << "s - simple" << std::endl;
        std::cout << "c - complex" << std::endl;
        std::cin >> input;
        switch (input) {
            case 's':
                completed = simple();
                break;
            case 'c':
                completed = complex();
                break;
            default:
                std::cout << "Invalid input" << std::endl;
                break;
        }
    } while (completed == false);
}

bool Game::simple() {
    try {
        Point first, ballStartingPosition;
        double bigger, smaller, ballDiameter;
        std::cout << "Enter table parameters in the following order: " << std::endl;
        std::cout << "First angle point (x, y) of the rectangle" << std::endl;
        std::cout << "Size of bigger side" << std::endl;
        std::cout << "Size of smaller side" << std::endl;
        std::cout << "Ball starting position (x, y)" << std::endl;
        std::cout << "Ball diameter" << std::endl;
        std::cin >> first;
        std::cin >> bigger;
        std::cin >> smaller;
        std::cin >> ballStartingPosition;
        std::cin >> ballDiameter;

        std::vector<Point> points;
        points.push_back(first);
        points.push_back(Point(first.x + bigger, first.y));
        points.push_back(Point(first.x + bigger, first.y + smaller));
        points.push_back(Point(first.x, first.y + smaller));

        table = Table(points, ballStartingPosition, ballDiameter / 2);
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        std::cout << "Enter any key to continue" << std::endl;
        std::cin.get();
        system("clear");

        return false;
    }

    return true;
}

bool Game::complex() {
    try {
        std::cout << "Enter table parameters in the following order: " << std::endl;
        std::cout << "First angle point (x, y)" << std::endl;
        std::cout << "Second angle point (x, y)" << std::endl;
        std::cout << "Third angle point (x, y)" << std::endl;
        std::cout << "Fourth angle point (x, y)" << std::endl;
        std::cout << "Ball starting position (x, y)" << std::endl;
        std::cout << "Ball diameter" << std::endl;
        std::cin >> table;
        system("clear");
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        std::cout << "Press enter to continue" << std::endl;
        std::cin.get();
        system("clear");
        return false;
    }

    return true;
}

void Game::setTableCoords() {
    std::cout << "Enter the coordinates of the table corners: " << std::endl;
    std::vector<Point> points;
    Point startingPosition;
    double diameter;
    for (int i = 0; i < 4; i++) {
        Point p;
        std::cin >> p;
        points.push_back(p);
    }

    table.setCoordinates(points);
}

void Game::setBallDiameter() {
    std::cout << "Enter the ball diameter: " << std::endl;
    double diameter;
    std::cin >> diameter;
    table.setBallRadius(diameter / 2);
}

void Game::setStartingBallPosition() {
    char input;
    std::cout << "Enter an option: " << std::endl;
    std::cout << "1 - current position as starting" << std::endl;
    std::cout << "2 - custom position" << std::endl;
    std::cin >> input;

    switch (input) {
        case '1':
            table.setCurrentAsStarting();
            break;
        case '2': {
            std::cout << "Enter the starting ball position: " << std::endl;
            Point p;
            std::cin >> p;
            table.setStartingPosition(p);
            break;
        }
        default:
            std::cout << "Invalid input" << std::endl;
            std::cout << "Press enter to continue" << std::endl;
            std::cin.get();
            break;
    }
}

void Game::resetBall() {
    table.resetBallPosition();
}

void Game::printTable() {
    std::cout << table << std::endl;
}

void Game::hitBall() {
    double power;
    Point direction;
    std::cout << "Enter the power of the hit: " << std::endl;
    std::cin >> power;
    std::cout << "Enter the direction point of the hit: " << std::endl;
    std::cin >> direction;
    std::cin.ignore();

    table.hitBall(power, direction);
}

void Game::menu() {
    std::cout << "---Menu---" << std::endl;
    std::cout << "c - Set table coordinates" << std::endl;
    std::cout << "d - Set ball diameter" << std::endl;
    std::cout << "s - Set starting ball position" << std::endl;
    std::cout << "p - Print table" << std::endl;
    std::cout << "h - Hit ball" << std::endl;
    std::cout << "i - Reinitialize table" << std::endl;
    std::cout << "r - Reset ball position" << std::endl;
    std::cout << "q - Quit" << std::endl;
    std::cout << "Enter your choice: " << std::endl;
}
