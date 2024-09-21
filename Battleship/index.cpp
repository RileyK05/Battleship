#include <iostream>
#include <string> 
#include <vector>


class Player {
public:
	std::vector<Ship> ships;
};

struct Position {
	int x;
	int y;
};

class Ship {
public:
	std::string name;
	int parts;
	std::vector<Position> positions;
};

bool isShip = false;

class Board {
public:
    Player player;
    std::vector<Ship> ships = player.ships;
    std::vector<std::vector<bool>> grid;

    Board() {
        grid.resize(10, std::vector<bool>(10, false));
    }

    bool checkBoard() {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                for (const auto& ship : ships) {
                    for (const auto& pos : ship.positions) {
                        if (pos.x == i && pos.y == j) {
                            grid[i][j] = true;
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }


};





int main() {


	return 0;
} 