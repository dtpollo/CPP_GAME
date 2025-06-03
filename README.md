# Retro 2D Designed Game in C++  
## Puff Puff Planet  

Hello! I'm **Daniel Troya** (`chickenux`)  
Welcome to my GitHub!  
Check out [my GitHub profile](https://github.com/dtpollo) for more projects.

---

## 🛠️ Requirements

Before running or exploring the project, make sure you have the following tools installed:

- [C/C++ Compiler](https://gcc.gnu.org/)  
- [SFML Library](https://www.sfml-dev.org/)

---

## 🎮 Project Overview

This project focuses on designing and implementing a retro-style game using the **SFML** library.  
It covers essential programming concepts such as:

- **Game Engine Architecture**  
- **Pointers & References**  
- **Classes and Objects**  
- **Data Structures**  
- **Sprites and Textures**

Each topic is crucial for understanding the internal logic and behavior of the game objects.

---

## 📁 Repository Structure

Here’s what you’ll find in this repository:

- `Fonts/`  
  Contains the font used in the game. You can easily swap it with your preferred font to customize the game's visual style.

- `Sounds/`  
  Contains sound effects used in the game such as bullet sounds, game theme, and more.  
  > 🎵 The main song used is **"Aero Dynamik"** (2009) by **Kraftwerk** (copyrighted).

- `Textures/`  
  Includes both original and modified images used for gameplay (e.g., bullets, enemies, background).  
  You can cross-check these with filenames used in `Game.cpp`.

- `.h` files  
  Header files defining the classes for the main objects in the game: `Game`, `Player`, `Bullet`, and `Enemy`.

- `.cpp` files  
  Source files containing the implementation (functionality) of each class.  
  `main.cpp` is the entry point and starts the game by calling the `Game` class.

- `Report_Game.pdf`  
  This report includes more detailed information about the tools, structure, goals of each function, and development notes.  
  **Highly recommended** for understanding the full context of the project.

---

## 🧪 How to Compile

To compile the game, use the following command:

```bash
g++ Enemy.cpp Player.cpp Game.cpp Bullet.cpp main.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

