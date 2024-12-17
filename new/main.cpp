#include <iostream>
#include <ctime>
#include "board.cpp"
#include "ship.cpp"

using namespace std;

void playerTurn(Board& computerBoard);
void computerTurn(Board& playerBoard);

int main(){
    srand(time(0));

    Board playerBoard;
    Board computerBoard;

    for(int length = 1; length <= 3; ++length){
        playerBoard.placeShip(playerBoard.generateRandomShip(length));
        computerBoard.placeShip(computerBoard.generateRandomShip(length));
    }

    bool gameOver = false;
    while(!gameOver){
        cout << "Dein Board:\n";
        playerBoard.display();
        cout << "Computer's Board (verdeckt):\n";
        computerBoard.displayHidden();

        playerTurn(computerBoard);
        if(computerBoard.allShipsSunk()){
            cout << "Du hast gewonnen!\n";
            gameOver = true;
            break;
        }

        computerTurn(playerBoard);
        if(playerBoard.allShipsSunk()){
            cout << "Der Computer hat gewonnen!\n";
            gameOver = true;
            break;
        }
    }

    return 0;
}

void playerTurn(Board& computerBoard){
    int x, y;
    cout << "Dein Zug! Gib die Koordinaten ein (x y): ";
    cin >> x >> y;
    if(computerBoard.attack(x-1, y-11)){
        cout << "Treffer!\n";
    } else {
        cout << "Daneben!\n";
    }
}

void computerTurn(Board& playerBoard){
    int x = rand() % 10;
    int y = rand() % 10;
    cout << "Computer greift an: (" << x << ", " << y << ")\n";
    if(playerBoard.attack(x, y)){
        cout << "Computer hat getroffen!\n";
    } else {
        cout << "Computer hat daneben geschossen!\n";
    }
}