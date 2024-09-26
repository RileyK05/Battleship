#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> 
#include <ctime>
#include <limits>
#include <algorithm> 
#include <random>  

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

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
    int shipCount = 5;
};

class Board {
public:
    std::vector<std::vector<char>> grid;
    Player& player;

    Board(Player& p) : player(p) {
        grid.resize(10, std::vector<char>(10, '~'));
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
                if (grid[i][j] == 'S') {
                    std::cout << "S ";
                }
                else if (grid[i][j] == 'H') {
                    std::cout << "H ";
                }
                else if (grid[i][j] == 'M') {
                    std::cout << "M ";
                }
                else {
                    std::cout << "~ ";
                }
            }
            std::cout << std::endl;
        }
    }

    void writeDualBoards(Board& enemyBoard) {
        std::cout << "   ";
        for (char c = 'A'; c <= 'J'; c++) {
            std::cout << c << " ";
        }
        std::cout << "         ";
        for (char c = 'A'; c <= 'J'; c++) {
            std::cout << c << " ";
        }
        std::cout << std::endl;

        for (int i = 0; i < 10; i++) {
            std::cout << i + 1 << " ";
            if (i + 1 < 10) std::cout << " ";
            for (int j = 0; j < 10; j++) {
                if (enemyBoard.grid[i][j] == 'H') {
                    std::cout << "H ";
                }
                else if (enemyBoard.grid[i][j] == 'M') {
                    std::cout << "M ";
                }
                else {
                    std::cout << "~ ";
                }
            }

            std::cout << "       " << i + 1 << " ";
            if (i + 1 < 10) std::cout << " ";
            for (int j = 0; j < 10; j++) {
                if (grid[i][j] == 'S') {
                    std::cout << "S ";
                }
                else if (grid[i][j] == 'H') {
                    std::cout << "H ";
                }
                else if (grid[i][j] == 'M') {
                    std::cout << "M ";
                }
                else {
                    std::cout << "~ ";
                }
            }
            std::cout << std::endl;
        }
    }

    void markHitOrMiss(int row, int col, bool hit) {
        if (hit) {
            grid[row][col] = 'H';
        }
        else {
            grid[row][col] = 'M';
        }
    }
};

void getValidCoordinates(char& column, int& row) {
    bool validInput = false;
    while (!validInput) {
        std::cout << "Enter coordinates (column (A-J) and row (1-10)): ";
        std::cin >> column >> row;

        column = toupper(column);

        if (column >= 'A' && column <= 'J' && row >= 1 && row <= 10) {
            validInput = true;
        }
        else {
            std::cout << "Invalid input. Please enter a column from A-J and a row from 1-10.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

bool placeShip(Ship& ship, int x, int y, bool isHorizontal, std::vector<std::vector<char>>& grid) {
    if (isHorizontal) {
        for (int i = 0; i < ship.size; i++) {
            if (x + i >= 10 || grid[x + i][y] != '~') {
                std::cout << "Invalid placement: Out of range or overlap detected\n";
                return false;
            }
        }
    }
    else {
        for (int i = 0; i < ship.size; i++) {
            if (y + i >= 10 || grid[x][y + i] != '~') {
                std::cout << "Invalid placement: Out of range or overlap detected\n";
                return false;
            }
        }
    }

    if (isHorizontal) {
        for (int i = 0; i < ship.size; i++) {
            grid[x + i][y] = 'S';
            ship.positions.push_back(Position{ x + i, y });
        }
    }
    else {
        for (int i = 0; i < ship.size; i++) {
            grid[x][y + i] = 'S';
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

    std::vector<Position> hitPositions;
    std::vector<Position> targetQueue;

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
                }
            }
        }
    }

    Position getNextAttack() {
        if (!targetQueue.empty()) {
            Position nextTarget = targetQueue.back();
            targetQueue.pop_back();
            return nextTarget;
        }
        else {
            Position randomTarget;
            randomTarget.x = rand() % 10;
            randomTarget.y = rand() % 10;
            return randomTarget;
        }
    }

    void addAdjacentPositions(Position pos, std::vector<std::vector<char>>& grid) {
        std::vector<Position> potentialTargets;

        if (pos.x > 0 && grid[pos.x - 1][pos.y] == '~') {
            potentialTargets.push_back({ pos.x - 1, pos.y });
        }
        if (pos.x < 9 && grid[pos.x + 1][pos.y] == '~') {
            potentialTargets.push_back({ pos.x + 1, pos.y });
        }
        if (pos.y > 0 && grid[pos.x][pos.y - 1] == '~') {
            potentialTargets.push_back({ pos.x, pos.y - 1 });
        }
        if (pos.y < 9 && grid[pos.x][pos.y + 1] == '~') {
            potentialTargets.push_back({ pos.x, pos.y + 1 });
        }

        std::random_device rd;
        std::default_random_engine rng(rd());
        std::shuffle(potentialTargets.begin(), potentialTargets.end(), rng);

        for (Position adjPos : potentialTargets) {
            targetQueue.push_back(adjPos);
        }
    }
};

class BattleLogic {
public:
    Player& player;
    Player& bot;

    Board& playerBoard;
    Board& botBoard;
    Bot& botLogic;

    BattleLogic(Player& p, Player& b, Board& pb, Board& bb, Bot& botL)
        : player(p), bot(b), playerBoard(pb), botBoard(bb), botLogic(botL) {}

    void playerTurn() {
        char userX;
        int userY;

        getValidCoordinates(userX, userY);

        int columnIndex = userX - 'A';
        int rowIndex = userY - 1;

        if (botBoard.grid[rowIndex][columnIndex] == 'H' || botBoard.grid[rowIndex][columnIndex] == 'M') {
            std::cout << "You've already attacked this position. Try again.\n";
            playerTurn();
            return;
        }

        bool hit = false;

        for (Ship& ship : bot.ships) {
            for (Position& pos : ship.positions) {
                if (pos.x == rowIndex && pos.y == columnIndex) {
                    std::cout << "You hit the enemy's " << ship.name << "!\n";
                    hit = true;

                    ship.positions.erase(std::remove_if(ship.positions.begin(), ship.positions.end(),
                        [&](const Position& pos) {
                            return pos.x == rowIndex && pos.y == columnIndex;
                        }), ship.positions.end());

                    if (ship.positions.empty()) {
                        std::cout << "You sunk the enemy's " << ship.name << "!\n";
                        ship.sunk = true;
                        bot.shipCount--;
                    }

                    botBoard.markHitOrMiss(rowIndex, columnIndex, true);
                    break;
                }
            }
            if (hit) break;
        }

        if (!hit) {
            std::cout << "You missed.\n";
            botBoard.markHitOrMiss(rowIndex, columnIndex, false);
        }
    }

    void botTurn() {
        Position attackPos = botLogic.getNextAttack();

        while (playerBoard.grid[attackPos.x][attackPos.y] == 'H' || playerBoard.grid[attackPos.x][attackPos.y] == 'M') {
            attackPos = botLogic.getNextAttack();
        }

        bool hit = false;

        for (Ship& ship : player.ships) {
            for (Position& pos : ship.positions) {
                if (pos.x == attackPos.x && pos.y == attackPos.y) {
                    std::cout << "The enemy hit your " << ship.name << "!\n";
                    hit = true;

                    ship.positions.erase(std::remove_if(ship.positions.begin(), ship.positions.end(),
                        [&](const Position& pos) {
                            return pos.x == attackPos.x && pos.y == attackPos.y;
                        }), ship.positions.end());

                    if (ship.positions.empty()) {
                        std::cout << "The enemy sunk your " << ship.name << "!\n";
                        ship.sunk = true;
                        player.shipCount--;
                    }

                    playerBoard.markHitOrMiss(attackPos.x, attackPos.y, true);

                    botLogic.addAdjacentPositions(attackPos, playerBoard.grid);

                    break;
                }
            }
            if (hit) break;
        }

        if (!hit) {
            std::cout << "The enemy missed.\n";
            playerBoard.markHitOrMiss(attackPos.x, attackPos.y, false);
        }
    }

    bool isGameOver() {
        return player.shipCount == 0 || bot.shipCount == 0;
    }

    void startGame() {
        while (!isGameOver()) {
            system(CLEAR_COMMAND);
            playerBoard.writeDualBoards(botBoard);
            playerTurn();
            if (isGameOver()) break;
            botTurn();
        }

        system(CLEAR_COMMAND);
        playerBoard.writeDualBoards(botBoard);

        if (player.shipCount == 0) {
            std::cout << "\nYou lost the game. Better luck next time!\n";
        }
        else {
            std::cout << "\nCongratulations! You won the game!\n";
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

            std::cout << "Place your " << ship.name << " (size " << ship.size << "): ";

            getValidCoordinates(userX, userY);

            int columnIndex = userX - 'A';
            int rowIndex = userY - 1;

            bool isHorizontal;
            std::cout << "Is the ship horizontal (1 for yes, 0 for no)? ";
            std::cin >> isHorizontal;

            if (placeShip(ship, rowIndex, columnIndex, isHorizontal, board.grid)) {
                placed = true;
                system(CLEAR_COMMAND);
                board.writeBoard();
            }
        }
    }

    BattleLogic battle(player, botPlayer, board, botBoard, bot);
    battle.startGame();

    return 0;
}
