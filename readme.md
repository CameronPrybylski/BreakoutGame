# 🧱 Breakout Game

A simple Breakout clone built in C++ using SDL2. Smash bricks, save the ball, and have fun!

---

## 📦 Features

- Classic arcade-style gameplay
- Built with SDL2
- Clean, modular C++ codebase
- Easily portable to macOS, Linux, and Windows

---

## 🛠️ Build Instructions

This project uses **CMake** to manage the build process.

### ✅ Dependencies

You’ll need the following installed on your system:

- [CMake](https://cmake.org/)
- [SDL2](https://www.libsdl.org/)
- [SDL2\_image](https://github.com/libsdl-org/SDL_image)

#### On macOS (with Homebrew):

```bash
brew install cmake sdl2 sdl2_image
```

#### On Ubuntu/Debian:

```bash
sudo apt update
sudo apt install cmake libsdl2-dev libsdl2-image-dev
```

#### On Windows:

- Install CMake from [cmake.org](https://cmake.org/download/)
- Use [vcpkg](https://github.com/microsoft/vcpkg) or [MSYS2](https://www.msys2.org/) to get SDL2 and SDL2\_image.

---

### 🔧 Build Steps

```bash
git clone https://github.com/yourusername/breakout-game.git
cd breakout-game

mkdir build
cd build

cmake ..
make
```

Run the game:

```bash
./Breakout
```

> 🔔 Make sure the `assets/` folder is in the same directory as the executable when you run it.

---

## 🎮 Controls

| Key   | Action          |
| ----- | --------------- |
| a / d | Move paddle     |
| Space | Launch the ball |
| X(icon)   | Quit the game   |

---

## 📁 Project Structure

```
breakout-game/
├── res/              # Textures, shaders
├── src/                 # All C++ source files
├── include/             # Headers 
├── CMakeLists.txt
└── README.md
```

---

## 🗓 License

MIT License. Feel free to use and modify!

---

## 🙌 Credits

- SDL2 and SDL2\_image
- Inspired by the classic arcade game *Breakout*

