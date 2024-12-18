#include "board.hpp"
#include "config.hpp"

int gridSize = 9;

Board::Board() : grid(gridSize, vector<char>(gridSize, '~')) {}

void Board::placeShip(Ship& ship){
    int x = ship.getX();
    int y = ship.getY();
    int length = ship.getLength();
    char orientation = ship.getOrientation();

    for(int i = 0; i < length; ++i){
        if(orientation == 'H'){
            grid[x][y + i] = 'S';
        } else {
            grid[x + i][y] = 'S';
        }
    }
}

void Board::display() {
    cout << "  ";
    for (int i = 0; i < gridSize; ++i) {
        cout << i + 1 << ' ';
    }
    cout << endl;

    for (int i = 0; i < gridSize; ++i) {
        cout << i + 1 << ' ';
        for (int j = 0; j < gridSize; ++j) {
            char cell = grid[i][j];
            if (cell == '~') {
                cout << "\033[34m" << cell << "\033[0m" << ' ';
            } else if (cell == 'S') {
                cout << "\033[30m" << cell << "\033[0m" << ' ';
            } else if (cell == 'X') {
                cout << "\033[31m" << cell << "\033[0m" << ' ';
            } else if (cell == 'O') {
                cout << "\033[93m" << cell << "\033[0m" << ' ';
            }
        }
        cout << endl;
    }
}

void Board::displayHidden() {
    cout << "  ";
    for (int i = 0; i < gridSize; ++i) {
        cout << i + 1 << ' ';
    }
    cout << endl;

    for (int i = 0; i < gridSize; ++i) {
        cout << i + 1 << ' ';
        for (int j = 0; j < gridSize; ++j) {
            char cell = grid[i][j];
            if (cell == 'S') {
                cout << "\033[34m" << "~ " << "\033[0m";
            } else {
                if (cell == '~') {
                    cout << "\033[34m" << cell << "\033[0m" << ' ';
                } else if (cell == 'X') {
                    cout << "\033[31m" << cell << "\033[0m" << ' ';
                } else if (cell == 'O') {
                    cout << "\033[93m" << cell << "\033[0m" << ' ';
                }
            }
        }
        cout << endl;
    }
}

Ship Board::generateRandomShip(int length){
    char orientation;
    int x, y;
    bool placed = false;

    while(!placed){
        orientation = (rand() % 2) == 0 ? 'H' : 'V';
        x = rand() % gridSize;
        y = rand() % gridSize;

        if(canPlaceShip(x, y, length, orientation)){
            placed = true;
        }
    }
    return Ship(x, y, length, orientation);
}

bool Board::canPlaceShip(int x, int y, int length, char orientation){
    if(orientation == 'H'){
        if(y + length > gridSize) return false;
        for(int i = 0; i < length; ++i){
            if(grid[x][y + i] != '~') return false;
        }
    } else {
        if(x + length > gridSize) return false;
        for(int i = 0; i < length; ++i){
            if(grid[x + i][y] != '~') return false;
        }
    }
    return true;
}

bool Board::attack(int x, int y){
    if(grid[x][y] == 'S'){
        grid[x][y] = 'X';
        return true;
    } else if(grid[x][y] == '~'){
        grid[x][y] = 'O';
        return false;
    }
    return false;
}

bool Board::allShipsSunk(){
    for(auto& row : grid){
        for(char cell : row){
            if(cell == 'S'){
                return false;
            }
        }
    }
    return true;
}