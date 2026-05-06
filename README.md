# Snake Game (C)

A simple implementation of the classic Snake game for the Windows console, written in C. This project focuses on using Windows APIs for terminal control and non-blocking keyboard input.

## Features

- **Progressive Difficulty**: Game speed increases as the score grows.
- **Console Optimization**: Uses Windows Console API for smooth rendering and cursor control.
- **Wraparound Logic**: Snake can pass through walls and reappear on the opposite side.
- **Lightweight**: Pure C implementation with no external library dependencies.

## Tech Stack

- **Language**: C
- **API**: Windows Console API (`windows.h`)
- **Input Handling**: `conio.h`

## Getting Started

### Prerequisites
- GCC Compiler (MinGW for Windows)

### Installation & Build

1. **Clone the repository:**
   ```bash
   git clone https://github.com/SynthoNX/snake-game.git
   cd snake-game
   ```

2. **Compile the program:**
   ```bash
   gcc snake.c -o snake.exe
   ```

### How to Play

To start the game, run the compiled executable:
```bash
./snake.exe
```

**Controls:**
- `u`: Move Up
- `d`: Move Down
- `l`: Move Left
- `r`: Move Right
- `x`: Exit Game

## Project Structure

```text
.
├── snake.c         # Source code and logic
├── README.md       # Project documentation
└── .gitignore      # Git exclusion rules
```
