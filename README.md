# C++ Battleship Game

## Overview
This is a C++ implementation of the classic Battleship game, where a player competes against a bot. The game features ship placement, board rendering, and battle logic for both the player and the bot. The bot has an enhanced strategy to sink ships once they are hit.

## Features
- **Player vs Bot**: Players compete against a bot to sink each other's ships.
- **Grid System**: The game takes place on a 10x10 grid where ships are placed and attacks are made.
- **Ship Placement**: Players manually place their ships on the board, while the bot places ships randomly.
- **Bot Strategy**: The bot uses an intelligent targeting system to focus on sinking ships once a hit is detected.
- **Dual Boards Display**: The game shows both the player's board and the enemy's board during gameplay.
- **Turn-based Game**: Players take turns to attack and receive feedback on hits or misses.

## Gameplay

1. **Player Ship Placement**: 
   - Players will be prompted to place each of their five ships by entering coordinates and deciding whether the ship is placed horizontally or vertically.
   
2. **Bot Ship Placement**: 
   - The bot places ships randomly on its board.
   
3. **Taking Turns**: 
   - Players take turns choosing a coordinate to attack on the enemy's board.
   - Hits and misses are marked on the grid, with 'H' indicating a hit and 'M' indicating a miss.
   
4. **Bot Logic**: 
   - The bot attacks randomly until it scores a hit, at which point it focuses on surrounding positions to try and sink the ship.

5. **Winning the Game**: 
   - The game ends when all of the ships for one player are sunk. If the player sinks all the bot's ships, they win. If the bot sinks all the player's ships, they lose.

## Ship Information
- **Carrier**: Size 5
- **Battleship**: Size 4
- **Cruiser**: Size 3
- **Submarine**: Size 3
- **Destroyer**: Size 2

## Installation

1. Clone the repository:
    ```bash
    git clone <repository-url>
    cd <project-directory>
    ```

2. Compile the program using your preferred C++ compiler:
    ```bash
    g++ battleship.cpp -o battleship
    ```

3. Run the game:
    ```bash
    ./battleship
    ```

## How to Play

1. **Place Ships**: 
   - When prompted, enter the coordinates (column A-J and row 1-10) for each ship.
   - Choose whether the ship is placed horizontally or vertically.

2. **Attack the Bot**: 
   - Enter coordinates to attack the bot's ships. The bot will also attack your ships.
   - Hits and misses will be shown on the grid. 

3. **Win or Lose**: 
   - The game ends when one player sinks all of the other player's ships.

## Example Gameplay

- You will place your ships by inputting coordinates like "A5" and specifying if the ship is horizontal or vertical.
- Once the game starts, you will alternate turns with the bot, attacking grid positions by specifying coordinates like "B6".
- The game will indicate whether the attack was a hit or miss and keep track of sunk ships.

## Customization

- **Bot Strategy**: The bot can be modified to change its strategy by adjusting the logic in the `Bot` class.
- **Board Size**: The grid size can be adjusted by modifying the grid initialization in the `Board` class.
- **Ship Types**: You can add or remove ships by changing the fleet initialization in the `initializeFleet()` function.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
