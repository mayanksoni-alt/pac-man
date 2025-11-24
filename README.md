# Terminal Pac-Man Game (C Language)

This project is a simple Pac-Man style game written in C, designed to run directly inside a Linux or macOS terminal. It uses real-time keyboard input, basic ghost movement logic, and a fixed 15x30 game board.

---

## Features

- Real-time Pac-Man movement using W, A, S, D keys  
- Four ghosts with restricted movement areas  
- Collectible dots (.) and power pellets (o)  
- Score increases as Pac-Man eats pellets  
- Win condition when all pellets are collected  
- Game over when a ghost collides with Pac-Man  
- Compatible with macOS Terminal, Linux Terminal, and VS Code

---

## Project Structure

pacman/
│── main.c // Main game logic
│── pacman.h // Header file with function declarations and constants
│── Makefile // Optional build file
└── README.md

## Controls

| Key | Action        |
|-----|----------------|
| W   | Move Up       |
| S   | Move Down     |
| A   | Move Left     |
| D   | Move Right    |
| Q   | Quit Game     |

---

## How to Compile

### Using GCC

### Run the Game


---

## Game Logic Summary

- The board is stored as a 2D character array.  
- Pac-Man moves every two cycles, while ghosts move every three cycles.  
- Ghosts are limited to staying within their assigned area of the map.  
- The terminal is switched to raw mode so keyboard input is detected instantly using:
- The `select()` function is used to check keypresses without blocking the program.

---

## Requirements

- macOS or Linux  
- GCC or Clang  
- A terminal or VS Code environment

---

## Example Board (Terminal Output)

##############################
#............##..............#
#.####.######..######.####...#
#o....#................#....o#
#.####.#.####.##.####.#.####.#
#......#......##......#......#
######.######.##.######.######
#............P...............#
######.######.##.######.######
#......#......##......#......#
#.#####.####..##..####.#####.#
#o....#................#....o#
#.####.######..######.####...#
#.............##.............#
##############################
Score: 120

---

## Author

Created by **Mayank Soni** as a learning project in the C programming language.

---



