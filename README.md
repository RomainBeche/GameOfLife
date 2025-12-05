# Game of Life - C++ Implementation

A robust, object-oriented implementation of John Conway's cellular automaton featuring both console and graphical visualization modes.

## Features

- ✨ **Dual visualization modes**: Console output and graphical interface (SFML)
- 🎮 **Configurable simulation**: Adjustable speed, cell size, and generation limits
- 📁 **Pattern loading**: Read initial configurations from text files
- 🧪 **Comprehensive testing**: Built-in grid testing suite
- 🏗️ **Clean architecture**: Designed following SOLID principles and OOP best practices

## Table of Contents

- [About Conway's Game of Life](#about-conways-game-of-life)
- [Design Principles](#design-principles)
- [Project Structure](#project-structure)
- [Installation](#installation)
  - [Prerequisites](#prerequisites)
  - [macOS Installation](#macos-installation)
  - [Windows Installation](#windows-installation)
  - [Linux Installation](#linux-installation)
- [Usage](#usage)
  - [Command-Line Arguments](#command-line-arguments)
  - [Examples](#examples)
- [Input File Format](#input-file-format)
- [Testing](#testing)
- [Troubleshooting](#troubleshooting)

## About Conway's Game of Life

Conway's Game of Life is a cellular automaton devised by mathematician John Conway. It consists of a grid of cells that evolve through discrete time steps according to simple rules:

1. **Survival**: A live cell with 2 or 3 live neighbors survives
2. **Death**: A live cell with fewer than 2 neighbors dies (underpopulation)
3. **Death**: A live cell with more than 3 neighbors dies (overpopulation)
4. **Birth**: A dead cell with exactly 3 live neighbors becomes alive (reproduction)

Despite these simple rules, the Game of Life exhibits complex emergent behavior and interesting patterns.

## Design Principles

This implementation follows:
- **SOLID Principles**: Single responsibility, open/closed, Liskov substitution, interface segregation, dependency inversion
- **Object-Oriented Design**: Encapsulation, inheritance, polymorphism
- **UML Modeling**: Use case, activity, class, and sequence diagrams
- **Clean Code**: Readable, maintainable, well-documented code

## Project Structure

```
GameOfLife/
├── CMakeLists.txt              # Build configuration
├── README.md                   # This file
│
├── src/                        # Source files
│   ├── main.cpp               # Entry point
│   │
│   ├── gameOfLife.cpp         # Main game controller
│   ├── file.cpp               # File I/O handler
│   │
│   ├── grid.cpp               # Grid management
│   ├── cell.cpp               # Individual cell logic
│   │
│   ├── display.cpp            # Abstract display base
│   ├── consoleDisplay.cpp     # Console visualization
│   ├── graphicalDisplay.cpp   # SFML graphical visualization
│   │
│   ├── cellState.cpp          # Abstract state base
│   ├── aliveState.cpp         # Alive cell state
│   ├── deadState.cpp          # Dead cell state
│   │
│   ├── ruleSet.cpp            # Abstract rule base
│   └── conwayRuleSet.cpp      # Conway's Game of Life rules
│
├── include/                    # Header files
│   ├── gameOfLife.h
│   ├── file.h
│   │
│   ├── grid.h
│   ├── cell.h
│   │
│   ├── display.h
│   ├── consoleDisplay.h
│   ├── graphicalDisplay.h
│   │
│   ├── cellState.h
│   ├── aliveState.h
│   ├── deadState.h
│   │
│   ├── ruleSet.h
│   └── conwayRuleSet.h
│
├── tests/                      # Test files
│   ├── gridTests.cpp          # Main test runner
│   ├── gridTester.cpp         # Grid testing implementation
│   └── gridTester.h           # Grid tester interface
│
├── patterns/                   # Example pattern files
│   ├── blinker.txt
│   ├── glider.txt
│   ├── toad.txt
│   ├── beacon.txt
│   ├── lwss.txt               # Lightweight spaceship
│   └── soup.txt               # Random soup
│
└── build/                      # Build directory (created during build)
    ├── GameOfLife             # Main executable
    ├── GridTests              # Test executable
    └── output/                # Generated output files (console mode)
```

## Installation

### Prerequisites

All platforms require:
- **CMake 3.16 or higher**: Check with `cmake --version`
- **C++ compiler**: 
  - macOS: Clang (included with Xcode Command Line Tools)
  - Windows: MSVC (Visual Studio)
  - Linux: GCC/G++
- **SFML 3.0**: Graphics library for visualization mode

### macOS Installation

#### 1. Install Dependencies

```bash
# Install Homebrew if you haven't already
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install CMake and SFML
brew install cmake sfml
```

#### 2. Configure VSCode (Optional but Recommended)

If using Visual Studio Code:
- Install the **Microsoft C/C++** extension
- Press `Cmd+Shift+P` → Select "C/C++: Edit Configurations (JSON)"
- Add to `includePath` array:
  - **Apple Silicon**: `"/opt/homebrew/opt/sfml/include"`
  - **Intel Mac**: `"/usr/local/opt/sfml/include"`
- Restart VSCode

#### 3. Build the Project

```bash
cd GameOfLife
mkdir build
cd build
cmake ..
make
```

### Windows Installation

#### 1. Install SFML

- Download **SFML 3.0** for Visual Studio from [sfml-dev.org](https://www.sfml-dev.org/download.php)
- Extract to a memorable location (e.g., `C:\SFML-3.0.0`)

#### 2. Install CMake

- Download CMake from [cmake.org](https://cmake.org/download/)
- Install and verify: `cmake --version`

#### 3. Build the Project

```bash
cd GameOfLife
mkdir build
cd build

# Configure with SFML path (adjust path to your installation)
cmake -DSFML_DIR="C:\SFML-3.0.0\lib\cmake\SFML" ..

# Build (Release configuration recommended)
cmake --build . --config Release
```

### Linux Installation

#### 1. Install Dependencies

**Debian/Ubuntu:**
```bash
sudo apt update
sudo apt install cmake g++ libsfml-dev
```

**Fedora:**
```bash
sudo dnf install cmake gcc-c++ SFML-devel
```

**Arch Linux:**
```bash
sudo pacman -S cmake gcc sfml
```

#### 2. Build the Project

```bash
cd GameOfLife
mkdir build
cd build
cmake ..
make
```

## Usage

### Command-Line Arguments

```
./GameOfLife <../patters/input_file> [options]
```

#### Required Arguments
- `input_file`: Path to the grid configuration file located in the build directory (e.g., `glider.txt`)

#### Optional Arguments
| Argument | Values | Default | Description |
|----------|--------|---------|-------------|
| `--mode` | `0` or `1` | `0` | Visualization mode: 0 = console, 1 = graphical |
| `--cell-size` | Integer (pixels) | `10` | Size of each cell in graphical mode |
| `--delay` | Integer (milliseconds) | `500` | Delay between generations |
| `--max-gen` | Integer | Unlimited | Maximum number of generations to simulate |

### Examples

#### Console Mode (Text Output)

```bash
# Basic console simulation
./GameOfLife ../patters/blinker.txt --mode 0

# Console mode with slower speed and generation limit
./GameOfLife ../patters/glider.txt --mode 0 --delay 1000 --max-gen 50
```

**Console Output Example:**
```
Generation 1:
00000
01110
00000

Generation 2:
00100
00100
00100
```

#### Graphical Mode (SFML Window)

```bash
# Basic graphical simulation
./GameOfLife ../patters/glider.txt --mode 1

# Graphical mode with custom cell size and speed
./GameOfLife ../patters/flicker.txt --mode 1 --cell-size 8 --delay 200

# Large grid with small cells
./GameOfLife ../patters/glider.txt --mode 1 --cell-size 5 --delay 50 --max-gen 1000
```

## Input File Format

Create text files with your initial grid configuration where:
- `1` = alive cell (displayed as filled/white)
- `0` = dead cell (displayed as empty/black)
- Each line represents a row
- All rows must have the same length

### Example Patterns

#### Blinker (Period-2 Oscillator)
Create `blinker.txt`:
```
00000
00000
01110
00000
00000
```

#### Glider (Moves Diagonally)
Create `glider.txt`:
```
000000000
001000000
000100000
011100000
000000000
000000000
```

#### Toad (Period-2 Oscillator)
Create `toad.txt`:
```
0000000
0000000
0011100
0111000
0000000
0000000
```

#### Beacon (Period-2 Oscillator)
Create `beacon.txt`:
```
000000
011000
011000
000110
000110
000000
```

### File Guidelines

- **Encoding**: UTF-8 (plain text)
- **Grid size**: For optimal performance, at least 10x10 and at most 1000x1000
- **Location**: Place pattern files in the `patters` directory or specify full path
- **Whitespace**: No spaces between digits; newline after each row

## Testing

This project includes a dedicated testing suite for the grid functionality.

### Building and Running Tests

```bash
cd build

# Build the test executable
cmake ..
make GridTests

# Run all grid tests
./GridTests
```

### Test Coverage

The GridTester class validates core Game of Life mechanics through comprehensive pattern testing:
Test Cases

- Blinker Oscillator (Period-2)
  - Tests basic oscillation behavior
  - Validates state after 1 iteration (vertical → horizontal)
  - Confirms return to original state after 2 iterations
  - Verifies survival and birth rules
- 2x2 Block (Still Life)
  - Tests stable pattern recognition
  - Validates that stable configurations remain unchanged
  - Confirms survival rule with 2-3 neighbors
- Lightweight Spaceship (LWSS) on Toric Grid
  - Tests complex pattern evolution over 16 iterations
  - Validates toric (wrap-around) grid topology
  - Confirms spaceship returns to original position/state
  - Tests edge wrapping behavior

## Troubleshooting

### CMake Version Too Old

**Error**: `CMake 3.16 or higher is required`

**Solution**:
```bash
# macOS
brew upgrade cmake

# Windows
# Download latest version from https://cmake.org/download/

# Linux (Debian/Ubuntu)
sudo apt update && sudo apt install cmake
```

### SFML Not Found

**Error**: `Could not find SFML` or `SFML_DIR not found`

**Solution**:

**macOS**:
```bash
# Verify SFML installation
brew list sfml
brew --prefix sfml

# Reinstall if necessary
brew reinstall sfml
```

**Windows**:
- Ensure `SFML_DIR` points to the correct installation:
  ```bash
  cmake -DSFML_DIR="C:\Path\To\SFML-3.0.0\lib\cmake\SFML" ..
  ```

**Linux**:
```bash
# Debian/Ubuntu
sudo apt install libsfml-dev

# Verify installation
ldconfig -p | grep sfml
```

### Missing Headers or Compilation Errors

**Solution**: Clean rebuild
```bash
cd build
rm -rf *
cmake ..
make  # or: cmake --build . --config Release (Windows)
```

**VSCode users (macOS)**: Restart VSCode after updating `includePath` in `c_cpp_properties.json`

### Window Not Appearing (Graphical Mode)

**Check**:
1. Verify SFML DLLs are accessible (Windows)
2. Ensure `--mode 1` is specified
3. Check that input file exists and is valid

### Simulation Runs Too Fast/Slow

**Solution**: Adjust the `--delay` parameter
```bash
# Slower (1 second between generations)
./GameOfLife pattern.txt --mode 1 --delay 1000

# Faster (50ms between generations)
./GameOfLife pattern.txt --mode 1 --delay 50
```

### Input File Not Found

**Error**: `Could not open file` or `File not found`

**Solution**:
- Ensure the file exists in the current directory or provide full path
- Check file name spelling and extension
- macOS/Linux: Use `ls` to verify file location
- Windows: Use `dir` to verify file location

## License

This project was created as part of an academic assignment for the OOP Project at CESI. All rights reserved by the authors.
