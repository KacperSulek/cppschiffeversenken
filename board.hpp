#ifndef INC_BOARD_HPP //or #pragma once
#define INC_BOARD_HPP

// #include "board.cpp"

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int gridSize = 10;

class Board{
    public:
        char grid[gridSize][gridSize];
        Board();
        void display() const;
        void placeShip(int numShips);
        bool attack(int x, int y);
        bool allShipSunk();
};

#endif