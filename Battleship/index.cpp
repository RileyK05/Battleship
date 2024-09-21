#include <iostream>
#include <string>
#include <vector>

struct Position {
    int x;
    int y;
};

class Ship {
public:
    std::string name;
    int size;
    std::vector<Position> positions;
    bool sunk = false;
};

class Player {
public:
    std::vector<Ship> ships;
};

class Board {
public:
    std::vector<std::vector<bool>> grid;
    Player& player;

    Board(Player& p) : player(p) {
        grid.resize(10, std::vector<bool>(10, false));
    }

    void writeBoard() {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (grid[i][j]) {
                    std::cout << "S ";
                }
                else {
                    std::cout << "~ ";
                }
            }
            std::cout << std::endl;
        }
    }
};

void placeShip(Ship& ship, int x, int y, bool isHorizontal, std::vector<std::vector<bool>>& grid) {
    if (isHorizontal) {
        for (int i = 0; i < ship.size; i++) {
            if (x + i >= 10 || grid[x + i][y]) {
                std::cout << "Invalid placement: Out of range or overlap detected\n";
                return;
            }
        }
    }
    else {
        for (int i = 0; i < ship.size; i++) {
            if (y + i >= 10 || grid[x][y + i]) {
                std::cout << "Invalid placement: Out of range or overlap detected\n";
                return;
            }
        }
    }

    if (isHorizontal) {
        for (int i = 0; i < ship.size; i++) {
            grid[x + i][y] = true;
            ship.positions.push_back(Position{ x + i, y });
        }
    }
    else {
        for (int i = 0; i < ship.size; i++) {
            grid[x][y + i] = true;
            ship.positions.push_back(Position{ x, y + i });
        }
    }

    std::cout << ship.name << " placed successfully.\n";
}

void initializeFleet(Player& player) {
    player.ships.push_back(Ship{ "Carrier", 5 });
    player.ships.push_back(Ship{ "Battleship", 4 });
    player.ships.push_back(Ship{ "Cruiser", 3 });
    player.ships.push_back(Ship{ "Submarine", 3 });
    player.ships.push_back(Ship{ "Destroyer", 2 });
}

int main() {
    Player player;
    initializeFleet(player);

    Board board(player);

    for (Ship& ship : player.ships) {
        int x = rand() % 10;
        int y = rand() % 10;
        bool isHorizontal = rand() % 2;

        placeShip(ship, x, y, isHorizontal, board.grid); 
    }

    board.writeBoard(); 

    return 0;
}
