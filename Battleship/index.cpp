#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> 
#include <ctime>


class Player;
class Board;

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
        std::cout << "   ";
        for (char c = 'A'; c <= 'J'; c++) {
            std::cout << c << " ";
        }
        std::cout << std::endl;

        for (int i = 0; i < 10; i++) {
            std::cout << i + 1 << " ";
            if (i + 1 < 10) std::cout << " ";

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

bool placeShip(Ship& ship, int x, int y, bool isHorizontal, std::vector<std::vector<bool>>& grid) {
    if (isHorizontal) {
        for (int i = 0; i < ship.size; i++) {
            if (x + i >= 10 || grid[x + i][y]) {
                std::cout << "Invalid placement: Out of range or overlap detected\n";
                return false;
            }
        }
    }
    else {
        for (int i = 0; i < ship.size; i++) {
            if (y + i >= 10 || grid[x][y + i]) {
                std::cout << "Invalid placement: Out of range or overlap detected\n";
                return false;
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
    return true;
}

class Bot {
public:
    Player& bot;
    Board& botBoard;

    Bot(Player& p, Board& b) : bot(p), botBoard(b) {
        srand(static_cast<unsigned>(time(0)));
    }

    void placeShips() {
        for (Ship& ship : bot.ships) {
            bool shipPlaced = false;
            while (!shipPlaced) {
                int x = rand() % 10;
                int y = rand() % 10;
                bool isHorizontal = rand() % 2;

                if (placeShip(ship, x, y, isHorizontal, botBoard.grid)) {
                    shipPlaced = true;
                    botBoard.writeBoard();
                }
            }
        }
    }
};

class BattleLogic {
public:
    Player& player;
    Player& bot;
    Board& playerBoard;
    Board& botBoard;

    BattleLogic(Player& p, Player& b, Board& pb, Board& bb)
        : player(p), bot(b), playerBoard(pb), botBoard(bb) {}

    void playerTurn() {

    }

    void botTurn() {

    }

    bool isGameOver() {

    }

    void startGame() {
        while (!isGameOver()) {
            playerTurn();
            if (isGameOver()) break;
            botTurn();
        }
    }
};



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
    board.writeBoard();

    Player botPlayer;
    initializeFleet(botPlayer);
    Board botBoard(botPlayer);
    Bot bot(botPlayer, botBoard);

    std::cout << "\nBot is placing ships...\n";
    bot.placeShips();

    for (Ship& ship : player.ships) {
        bool placed = false;

        while (!placed) {
            char userX;
            int userY;

            std::cout << "Place your " << ship.name << " (size " << ship.size << "): Enter column (A-J) and row (1-10): ";
            std::cin >> userX >> userY;
            int columnIndex = userX - 'A';
            int rowIndex = userY - 1;

            bool isHorizontal;
            std::cout << "Is the ship horizontal (1 for yes, 0 for no)? ";
            std::cin >> isHorizontal;

            if (placeShip(ship, rowIndex, columnIndex, isHorizontal, board.grid)) {
                placed = true;
                board.writeBoard();
            }
        }
    }

    return 0;
}
