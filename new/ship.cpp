#include "ship.hpp"

Ship::Ship(int x, int y, int length, char orientation)
    : x(x), y(y), length(length), orientation(orientation) {}

int Ship::getX(){
    return x;
}

int Ship::getY(){
    return y;
}

int Ship::getLength(){
    return length;
}

char Ship::getOrientation(){
    return orientation;
}