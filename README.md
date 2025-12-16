<div align="center">

<img src="assets/bomb.svg" width="200" alt="Minesweeper">

<br>

![C](https://img.shields.io/badge/language-gray?style=for-the-badge&logo=c)
![License](https://img.shields.io/badge/license-MIT-blue.svg?style=for-the-badge)
![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS%20%7C%20Windows-blue?style=for-the-badge)

A classic **Minesweeper** game implementation in C.

[features](#features) • [demo](#demo) • [installation](#installation) • [how to play](#how-to-play) • [details](#technical-details)

</div>


## Features

- **10x10 Grid**: Classic minesweeper board with 10 bombs randomly placed
- **Colorful Interface**: ANSI color codes for better visual experience
  - Red bombs
  - Yellow coordinates
  - Cyan numbers
- **Recursive Cell Opening**: Automatically opens adjacent cells when a cell with no surrounding bombs is clicked
- **Win/Loss Detection**: Automatic game state verification
- **Replay Option**: Play multiple rounds without restarting the program

### Customization

#### Board Size and Level Game

You can easily customize the game by modifying these constants:

```c
int boardSize = 10;           // Change board dimensions
drawBombs(10);                // Change number of bombs (level game)
```

#### Color Scheme

Modify the ANSI color codes at the top of the file:

```c
#define RED     "\033[31m"    // Bombs
#define YELLOW  "\033[33m"    // Coordinates
#define CYAN    "\033[36m"    // Numbers
```

## Demo

```
                  MINESWEEPER

          0   1   2   3   4   5   6   7   8   9
      -----------------------------------------
    0 |   |   |   |   |   |   |   |   |   |   |
      -----------------------------------------

    1 |   |   |   |   |   |   |   |   |   |   |
      -----------------------------------------

    2 |   |   | 1 | 1 | 1 |   |   |   |   |   |
      -----------------------------------------

    3 |   |   | 1 | * | 1 |   |   |   |   |   |
      -----------------------------------------

    4 |   |   | 1 | 1 | 1 |   |   |   |   |   |
      -----------------------------------------
```

## Installation

### Prerequisites

- GCC compiler
- Terminal with ANSI color support (most modern terminals)

### Compile and Run

```bash
# Clone the repository and run
git clone https://github.com/repoeduardo/minesweeper.git
cd minesweeper
./play

# Or you can Compile and Run

# Compile
gcc minesweeper.c -o game
# Run
./game
```

### Windows Users

For Windows 10+, the ANSI codes work in Command Prompt and PowerShell. For older versions, consider using Windows Terminal or WSL.

## How to Play

1. The game starts with a 10x10 hidden grid containing 10 randomly placed bombs
2. Enter coordinates in the format: `row column` (e.g., `5 7`)
3. The game reveals:
   - A **number** indicating how many bombs are adjacent (up, down, left, right)
   - A **bomb (\*)** if you hit one (game over!)
   - **Empty cells** that automatically expand to reveal safe areas
4. Win by revealing all non-bomb cells
5. Choose to play again or exit after each game

### Example Input

```
Enter the row and column coordinates in this format [y] [x]. Example: 5 7
> 3 4
```

## Technical Details

### Data Structure

```c
typedef struct{
  int isBomb;       // 0 = safe, 1 = bomb
  int isOpen;       // 0 = closed, 1 = open
  int bombsAround;  // count of adjacent bombs (0-4)
} Cell;
```

### Key Algorithms

- **Bomb Placement**: Random distribution ensuring no duplicates
- **Adjacent Bomb Counting**: Checks all 4 cardinal directions
- **Recursive Cell Opening**: Depth-first search for revealing connected safe cells
- **Win Condition**: Counts remaining closed non-bomb cells

### Functions Overview

| Function                 | Description                                          |
| ------------------------ | ---------------------------------------------------- |
| `initializeGame()`       | Sets up the game board                               |
| `drawBombs()`            | Randomly places bombs on the board                   |
| `calculateBombsAround()` | Counts adjacent bombs for a cell                     |
| `openCell()`             | Opens a cell and recursively opens neighbors if safe |
| `hasWon()`               | Checks if the player has won                         |
| `printBoard()`           | Displays the current game state                      |

## License

This project is licensed under the **MIT License**

## Author

Created by *Eduardo Araujo*

## Contributing

Contributions, issues, and feature requests are welcome! Feel free to check the [issues page](https://github.com/repoeduardo/minesweeper/issues).