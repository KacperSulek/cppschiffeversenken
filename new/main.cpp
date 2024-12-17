#include "config.hpp"
#include "board.cpp"
#include "ship.cpp"

void playerTurn(Board* computerBoard);
void computerTurn(Board& playerBoard);

struct Coordinate {
    int x;
    int y;
};

vector<Coordinate> hits;
vector<Coordinate> targets;
vector<Coordinate> attempted;

bool wasAttempted(int x, int y){
    for(auto& coord : attempted){
        if(coord.x == x && coord.y == y){
            return true;
        }
    }
    return false;
}

void addTargets(int x, int y) {
    if(x > 0 && !wasAttempted(x-1, y)) targets.push_back({x-1, y});
    if(x < 6 && !wasAttempted(x+1, y)) targets.push_back({x+1, y});
    if(y > 0 && !wasAttempted(x, y-1)) targets.push_back({x, y-1});
    if(y < 6 && !wasAttempted(x, y+1)) targets.push_back({x, y+1});
}

int main(){
    srand(time(0));

    int setGrid = 7;

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

        playerTurn(&computerBoard);
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

void playerTurn(Board* computerBoard){
    int x, y;
    // x = rand() % setGrid;
    // y = rand() % setGrid;
    cout << "Dein Zug! Gib die Koordinaten ein (x y): ";
    cin >> x >> y;
    if(x > setGrid || y > setGrid){
        cout << "Fehler";
        playerTurn(computerBoard);
    } else {
        if(computerBoard->attack(x-1, y-1)){
            clearScreen();
            cout << "Treffer!\n";
        } else {
            clearScreen();
            cout << "Daneben!\n";
        }
    }
}

void computerTurn(Board& playerBoard) {
    int x, y;
    if(!targets.empty()) {
        Coordinate target = targets.back();
        x = target.x;
        y = target.y;
        targets.pop_back();
    } else {
        do {
            x = rand() % setGrid;
            y = rand() % setGrid;
            do{
                x = rand() % setGrid;
                y = rand() % setGrid;
            }
            while(playerBoard.grid[x][y] == 'O' || playerBoard.grid[x][y] == 'X');
        } while(wasAttempted(x, y));
    }

    cout << "Computer greift an: (" << x+1 << ", " << y+1 << ")\n";
    attempted.push_back({x, y});
    if(playerBoard.attack(x, y)){
        cout << "Computer hat getroffen!\n";
        hits.push_back({x, y});
        addTargets(x, y);
    } else {
        cout << "Computer hat daneben geschossen!\n";
    }
}