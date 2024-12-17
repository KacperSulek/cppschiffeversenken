#include "config.hpp"
#include "board.cpp"
#include "ship.cpp"

void playerTurn(Board& computerBoard);
void computerTurn(Board& playerBoard);



int main(){
    srand(time(0));

    int setGrid = 15;

    Board playerBoard;
    Board computerBoard;

    for(int i = 0; i < 3; ++i){
        for(int length = 1; length <= 3; ++length){
                playerBoard.placeShip(playerBoard.generateRandomShip(length));
                computerBoard.placeShip(computerBoard.generateRandomShip(length));
            }
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

void clearScreen(){
    for(int i = 0; i < 100; ++i){
        cout << endl;
    }
}

void playerTurn(Board& computerBoard){
    int x, y;
    cout << "Dein Zug! Gib die Koordinaten ein (x y): ";
    cin >> x >> y;
    if(computerBoard.attack(x-1, y-1)){
        clearScreen();
        cout << "Treffer!\n";
    } else {
        clearScreen();
        cout << "Daneben!\n";
    }
}

void computerTurn(Board& playerBoard){
    int x = rand() % setGrid;
    int y = rand() % setGrid;
    cout << "Computer greift an: (" << x+1 << ", " << y+1 << ")\n";
    if(playerBoard.attack(x, y)){
        cout << "Computer hat getroffen!\n";
    } else {
        cout << "Computer hat daneben geschossen!\n";
    }
}