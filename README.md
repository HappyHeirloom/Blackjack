# Blackjack
<sub>The README may or may not have been created in cooperation with ChatGPT.</sub>

## Table of Contents

- [Description](#description)  
- [Features](#features)  
- [Getting Started](#getting-started)  
  - [Prerequisites](#prerequisites)  
  - [Building from Source](#building-from-source)  
- [Project Structure](#project-structure)  
- [Usage](#usage)  
- [Future Improvements](#future-improvements)  
- [Contributing](#contributing)  
- [License](#license)

---

## Description

This project is a C++ implementation of a Blackjack game. My first attempt at creating a game in C++. It uses CMake for build configuration and Vcpkg for dependency management (if any dependencies are added in the future).

---

## Features

- Console-based gameplay  
- Basic rules of Blackjack  
- Organized into modules (Core, App) for clarity  
- Build system ready (CMake)  

---

## Prerequisites

To build this project, you’ll need:

- A C++23 compiler  
- CMake (version 3.XX or higher)  
- (Optional) vcpkg if external libraries are introduced  

---

## Building from Source

```bash
# Clone the repository
git clone https://github.com/HappyHeirloom/Blackjack.git
cd Blackjack

# Create a build directory
cmake -S . -B build

# If using vcpkg, configure it (optional)
# git clone https://github.com/microsoft/vcpkg.git

# Build
cmake --build build --config Release
```

---

## Project Structure

```
Blackjack/
├── App/               # Application entry point, user interface
├── Core/              # Game logic, rules, deck, player logic, etc.
├── CMakeLists.txt     # Build configuration
├── vcpkg.json         # Dependency manifest (currently minimal / placeholder)
├── .gitignore
└── README.md          # This file
```

---

## Usage

Once built, the executable (in the `build/` folder) can be run from the terminal.  
Example (from build directory):

```bash
./BlackjackApp   # or whatever the output binary is named
```

Follow prompts to play. Because this is an early version, expect things like manual input, limited validation, etc.

---

## Future Improvements

- Support for splitting, double-down, insurance, etc.  
- Graphical or GUI front-end
- Unit tests  

---

## Contributing

Contributions are welcome! If you find bugs or have ideas, feel free to:

1. Fork the repo  
2. Create a new branch  
3. Make your changes  
4. Submit a pull request  

Please include clear commit messages and document any new functionality.

---
