#include "config.hpp"
#include "board.cpp"
#include "ship.cpp"

void playerTurn(Board* computerBoard, int gridSize);
void computerTurn(Board& playerBoard, int gridSize);

struct Coordinate {
    int x;
    int y;
};

vector<Coordinate> hits;
vector<Coordinate> targets;
vector<Coordinate> attempted;

int main(){
    srand(time(0));

    int gridSize = 9;

    Board playerBoard(gridSize);
    Board computerBoard(gridSize);    

    for(int i = 0; i < 2; ++i){
        for(int length = 2; length <= 3; ++length){
            playerBoard.placeShip(playerBoard.generateRandomShip(length, gridSize));
            computerBoard.placeShip(computerBoard.generateRandomShip(length, gridSize));
        }
    }

    bool gameOver = false;
    while(!gameOver){
        cout << "Dein Board:\n";
        playerBoard.display(gridSize);
        cout << "Computer's Board (verdeckt):\n";
        computerBoard.displayHidden(gridSize);

        playerTurn(&computerBoard, gridSize);
        if(computerBoard.allShipsSunk()){
            cout << "Du hast gewonnen!\n";
            gameOver = true;
            break;
        }

        computerTurn(playerBoard, gridSize);
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

void playerTurn(Board* computerBoard, int gridSize){
    int x, y;
    cout << "Dein Zug! Gib die Koordinaten ein (x y): ";
    cin >> x >> y;
    if(x > gridSize || y > gridSize || x < 0 || y < 0){
        cout << "Fehler!!!" << endl;
        playerTurn(computerBoard, gridSize);
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

bool wasAttempted(int x, int y){
    for(auto& coord : attempted){
        if(coord.x == x && coord.y == y){
            return true;
        }
    }
    return false;
}

void addTargets(int x, int y, int gridSize){
    if(x > 6 && !wasAttempted(x-1, y)) targets.push_back({x-1, y});
    if(x < gridSize-1 && !wasAttempted(x+1, y)) targets.push_back({x+1, y});
    if(y > 6 && !wasAttempted(x, y-1)) targets.push_back({x, y-1});
    if(y < gridSize-1 && !wasAttempted(x, y+1)) targets.push_back({x, y+1});
}

void computerTurn(Board& playerBoard, int gridSize){
    int x, y;
    if(!targets.empty()){
        Coordinate target = targets.back();
        x = target.x;
        y = target.y;
        targets.pop_back();
    } else {
        do{
            do{
                x = rand() % gridSize;
                y = rand() % gridSize;
            } while(playerBoard.grid[x][y] == 'O' || playerBoard.grid[x][y] == 'X');
        } while(wasAttempted(x, y));
    }

    cout << "Computer greift an: (" << x+1 << ", " << y+1 << ")\n";
    attempted.push_back({x, y});
    if(playerBoard.attack(x, y)){
        cout << "Computer hat getroffen!\n";
        hits.push_back({x, y});
        addTargets(x, y, gridSize);
    } else {
        cout << "Computer hat daneben geschossen!\n";
    }
}