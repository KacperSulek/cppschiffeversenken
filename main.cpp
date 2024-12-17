#include "board.cpp"

#include <iostream>
using namespace std;
//#include "ship.cpp"

int main() {
    Board playerboard;
    Board cpuboard;
    Board fake;

    cpuboard.placeShip(10);
    playerboard.placeShip(10);

    while(true){
        int x, y;
        playerboard.display();
        cout << "" << endl;
        fake.display();
        cout << "Enter Coordinates to shoot! (x | y)";
        cin >> x >> y;
        if(cpuboard.attack(x, y)){
            cout << "Hit!" << endl;
            fake.grid[x-1][y-1] = 'X';
        } else {
            cout << "Miss!" << endl;
            fake.grid[x-1][y-1] = 'O';
        }

        if(cpuboard.allShipSunk()){
            cout << "You Win!" << endl;
            break;
        }

        x = rand() % gridSize+1;
        y = rand() % gridSize+1;

        if(playerboard.attack(x, y)){
            cout << "CPU Hit!" << endl;
        } else {
            cout << "CPU Miss!" << endl;
        }

        if(playerboard.allShipSunk()){
            cout << "CPU Win!" << endl;
            cpuboard.display();
            break;  
        }
    }
    return 0;
}
