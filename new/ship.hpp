#ifndef SHIP_H
#define SHIP_H

#include "config.hpp"

class Ship {
public:
    Ship(int x, int y, int length, char orientation);
    int getX();
    int getY();
    int getLength();
    char getOrientation();

private:
    int x, y, length;
    char orientation;
};

#endif