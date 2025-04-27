# Memory Match Card Game

A C++ console implementation of a 2-player memory matching game with special cards.

## Game Rules
- Players alternate turns flipping two cards
- Match standard cards: +1 point and extra turn
- Bonus cards: 
  - Single bonus: +1 point
  - Double bonus: Choice of +2 points OR +1 point + extra turn
- Penalty cards:
  - Single penalty: -1 point
  - Double penalty: Choice of -2 points OR -1 point + skip next turn
- Game ends when all pairs are matched

## Project Files
- `main.cpp` - Main game file
- `ms1.cpp` - Game logic implementation
- `include/` - Header files
- `basket` - Game data file

## How to Play
1. Compile:
```bash
g++ main.cpp ms1.cpp -o MemoryMatchGame
