# 🐍 Snake Game in C++

A classic Snake game implemented in C++ using Windows console functions like `gotoxy()`, `Sleep()`, and `getch()` to create a terminal-based real-time experience.

## 🎮 Game Features

- Classic snake movement using `W`, `A`, `S`, `D`
- Real-time keyboard input using `getch()` and `kbhit()`
- Snake grows on eating food 🍎
- Score tracking displayed live on screen
- Game over on wall collision or self-collision
- Fully terminal-based using `windows.h` and `conio.h`

## 📸 Demo Screenshot

![Snake Game Demo](https://media.geeksforgeeks.org/wp-content/uploads/20230701123219/tail-bite.png)

## 🚀 How to Run

### 🧱 Prerequisites

- **Windows OS** (required due to `windows.h`)
- **C++ compiler** (such as `g++` or MSVC)
- **Command-line terminal** (CMD or PowerShell)

### ⚙️ Compilation

Open your terminal and run:

```bash
g++ snake_game.cpp -o snake_game
