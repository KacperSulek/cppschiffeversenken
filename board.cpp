#include "board.hpp"

Board::Board()
{
    for (int i = 0; i < gridSize; ++i)
    {
        for (int j = 0; j < gridSize; ++j)
        {
            grid[i][j] = '~';
        }
    }
}

void Board::display() const
{
    for (int i = 0; i < gridSize; ++i)
    {
        for (int j = 0; j < gridSize; ++j)
        {
            cout << grid[i][j] << ' ';
        }
        cout << endl;
    }
}


void Board::placeShip(int numShips)
{
    srand(time(0));
    int shipPlaced = 0;
    while (shipPlaced < numShips)
    {
        int x = rand() % gridSize;
        int y = rand() % gridSize;
        if (grid[x][y] == '~')
        {
            grid[x][y] = 'S';
            ++shipPlaced;
        }
    }
}

bool Board::attack(int x, int y)
{
    if (grid[x-1][y-1] == 'S')
    {
        grid[x-1][y-1] = 'X';
        return true;
    }
    else if (grid[x-1][y-1] == '~')
    {
        grid[x-1][y-1] = 'O';
        return false;
    }
    else
    {
        return false;
    }
}
bool Board::allShipSunk()
{
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (grid[i][j] == 'S') {
                return false;
            }
        }
    }
    return true;
}