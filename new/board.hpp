#ifndef BOARD_H
#define BOARD_H

#include "config.hpp"
#include "ship.hpp"

class Board {
public:
    vector<vector<char>> grid;
    Board(int gridSize);
    void placeShip(Ship& ship);
    void display(int gridSize);
    void displayHidden(int gridSize);
    Ship generateRandomShip(int length, int gridSize);
    bool attack(int x, int y);
    bool allShipsSunk();

private:
    bool canPlaceShip(int x, int y, int length, char orientation, int gridSize);
};

#endif