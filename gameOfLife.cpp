#include "gameOfLife.h"
#include <iostream>

using std::cerr, std::cout, std::endl;

// Constructor
GameOfLife::GameOfLife()
    : mode(0),          
      grid(nullptr),           
      display(nullptr),
      file(nullptr),
      delay(500),
      generation(0),
      maxGenerations(1000)
{}

// Destructor
GameOfLife::~GameOfLife() {}

// Setters
void GameOfLife::setFile(const string& filename) {
    if (file == nullptr) file = new File();
    file->setInputFile(filename);
}

void GameOfLife::setDelay(int ms) { if (ms >= 0) delay = ms; } // Delay in milliseconds

void GameOfLife::setMaxGenerations(int max) { if (max > 0) maxGenerations = max; }

void GameOfLife::setGrid(Grid* g) { grid = g; } // Grid Setter

void GameOfLife::setMode(int m) { if (m == 0 || m == 1) mode = m; } // 0: console, 1: graphical

void GameOfLife::setToric(bool toric) { if (grid != nullptr) grid->setToric(toric); }

void GameOfLife::setDisplay(Display* d) { display = d; }

// Getters
Grid* GameOfLife::getGrid() { return grid; }
int GameOfLife::getGeneration() const { return generation; }

// Check if grid has stabilized
bool GameOfLife::checkStability() {
    string currentGrid = grid->textGrid();
    if (currentGrid == previousGrid) return true;   // Grid hasn't changed from last generation
    previousGrid = currentGrid;                     // Store current state for next iteration
    return false;
}
    
void GameOfLife::start() {
    if (grid == nullptr || display == nullptr) {
        cerr << "Error: Grid or Display not initialized" << endl;
        return;
    }

    generation = 0;
    previousGrid = "";

    // Main loop
    while (display->isOpen()) {
        // Check termination conditions
        if (generation >= maxGenerations) break;
        
        if (checkStability()) {
            cout << "Grid stabilized at generation " << generation << endl;
            break;
        }
        
        display->displayGrid(*grid);    // Display current generation
        display->handleEvents();        // Handle events (window close, keyboard input, etc.)
        
        
        if (mode == 0 && file != nullptr) file->writeFile(*grid, generation); // Console mode: write to file
        
        grid->update(); // Update grid to next generation
        
        generation++;   // Increment generation counter
    }
    
    cout << "Simulation ended at generation " << generation << endl;
}