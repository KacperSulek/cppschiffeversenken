#ifndef BOARD_H
#define BOARD_H

#include "config.hpp"
#include "ship.hpp"

class Board {
public:
    Board();
    void placeShip(Ship& ship);
    void display();
    void displayHidden();
    Ship generateRandomShip(int length);
    bool attack(int x, int y);
    bool allShipsSunk();

private:
    vector<vector<char>> grid;
    bool canPlaceShip(int x, int y, int length, char orientation);
};

#endif