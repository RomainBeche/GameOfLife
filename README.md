# GameOfLife

## Context
This object-oriented programming project consists of designing and then implementing in C++ an object-oriented version of John Conway's famous cellular automaton “Game of Life.” The goal is to model the different elements of the system—cells, states, evolution rules, grid, and game engine—according to OOP principles and SOLID rules. The program must be able to read an initial state from a file, simulate the evolution of the cell population over iterations, and offer two modes of operation: a console mode producing successive states, and a graphical mode based on the SFML library. We first focused on the modeling phase using Mermaid, including the creation of the main UML diagrams (use case, activity, class, and sequence) necessary for structuring the project.

# Launching Instructions

### Prerequisites (All Platforms)

- C/C++ compiler (clang on macOS, MSVC on Windows, g++ on Linux)
- CMake 3.16 or higher: `cmake --version`
    - macOS: `brew upgrade cmake` or `brew install cmake`
    - Windows: Download from [cmake.org](https://cmake.org/download/)
- SFML 3.0

### macOS (Apple Silicon & Intel)

1. **Install SFML**
    
    ```bash
    brew install sfml
    ```
    
2. **Configure VSCode (Optional but recommended)**
    - Install Microsoft C/C++ extension
    - Press `Cmd+Shift+P` → "C/C++: Edit Configurations (JSON)"
    - Add to `includePath`:
        - Apple Silicon: `"/opt/homebrew/opt/sfml/include"`
        - Intel Mac: `"/usr/local/opt/sfml/include"`
    - Restart VSCode
3. **Build and Run**
    
    ```bash
    cd GameOfLife
    mkdir build
    cd build
    cmake ..
    make
    
    # Copy or create input.txt in the build directory
    cp ../input.txt .
    
    # Run the simulation
    ./GameOfLife
    
    ```
    

### Windows (Visual Studio / MSVC)

1. **Install SFML**
    - Download SFML 3.0 for Visual Studio from [sfml-dev.org](https://www.sfml-dev.org/download.php)
    - Extract to a location (e.g., `C:\\SFML-3.0.0`)
2. **Configure CMake**
    - Install CMake from [cmake.org](https://cmake.org/download/)
    - Verify installation: `cmake --version`
3. **Build and Run**
    
    ```bash
    cd GameOfLife
    mkdir build && cd build
    cmake -DSFML_DIR="C:\\SFML-3.0.0\\lib\\cmake\\SFML" ..
    cmake --build . --config Release
    
    # Copy or create input.txt in the build\\Release directory
    copy ..\\input.txt Release\\
    
    # Run the simulation
    Release\\GameOfLife.exe
    
    ```
    

### Input File Format

Create an `input.txt` file with the initial grid state:

- 1 = alive cell
- 0 = dead cell

Example with a flicker:

```
00000
00000
01110
00000
00000
```

### Troubleshooting

**CMake version too old**

```bash
# macOS
brew upgrade cmake

# Windows: Download from cmake.org
```

**SFML not found**

- macOS: Verify SFML is installed: `brew --prefix sfml`
- Windows: Ensure `SFML_DIR` points to correct SFML installation directory

**Build fails with missing headers**

- macOS: Restart VSCode after updating `includePath`
- All platforms: Try clean rebuild:
```
cd build
rm -rf *
cmake ..
make  # or: cmake --build . --config Release (Windows)
```
