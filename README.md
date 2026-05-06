# 🐍 Classic Snake: Terminal Edition

A high-performance, retro-inspired Snake game built from scratch in C. Experience the nostalgia of the classic Nokia game right in your Windows command line, complete with dynamic difficulty and smooth console rendering.

## ✨ Features

- **Dynamic Speed**: The game gets progressively harder as your score increases—keep up if you can!
- **Zero Flicker**: Uses Windows Console API for smooth rendering without the "blinking" effect of standard `cls` loops.
- **Wraparound Logic**: Navigate through walls and appear on the opposite side for advanced maneuvers.
- **Minimalist Controls**: Intuitive single-key inputs for precise movement.
- **High Performance**: Optimized C code for zero-latency gameplay.

## 🛠️ Tech Stack

- **Language**: C (C99)
- **API**: Windows Console API (`windows.h`)
- **Input**: `conio.h` (Non-blocking keyboard hits)

## 🚀 Getting Started

### Prerequisites
- GCC Compiler (MinGW for Windows)

### Installation & Build

1. **Clone the repository:**
   ```bash
   git clone https://github.com/SynthoNX/snake-game.git
   cd snake-game
   ```

2. **Compile the game:**
   ```bash
   gcc snake.c -o snake.exe
   ```

### How to Play

Run the executable:
```bash
./snake.exe
```

**Controls:**
- `u`: Move Up
- `d`: Move Down
- `l`: Move Left
- `r`: Move Right
- `x`: Exit Game

## 📁 Project Structure

```text
.
├── snake.c         # Main game logic and rendering
├── snake.exe       # Compiled binary
└── .gitignore      # Git exclusion rules
```

## 🗺️ Roadmap

- [ ] Add ANSI colors for the snake and food.
- [ ] Implement a high-score system with persistent storage.
- [ ] Cross-platform support for Linux/macOS.

## 📄 License

This project is open-source and free to use.
