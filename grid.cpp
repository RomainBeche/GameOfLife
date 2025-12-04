#include "grid.h"
#include "conwayRuleSet.h"
#include "aliveState.h"
#include "deadState.h"
#include <stdexcept>
#include <iostream>

// Constructors
Grid::Grid() : width(0), height(0), toric(false), ruleSet(nullptr) {}

Grid::Grid(size_t width, size_t height, RuleSet* rules) : toric(false), ruleSet(rules) { 
    if (width != 0) {
        if (height != 0) {
            this->width = width;
            this->height = height;
            cells.resize(width*height);
            for (size_t y = 0; y < height; y++) {
                for (size_t x = 0; x < width; x++) {
                    size_t index = y*width+x;
                    cells[index].initialize(x,y); // init cell position
                }
            }
        } else { throw invalid_argument("Grid height can't be 0"); } // error if grid height set to 0
    } else { throw invalid_argument("Grid width can't be 0"); } // error if grid width set to 0
}

// Copy Constructor (needed for the gridTester class)
Grid::Grid(const Grid& other) 
    : width(other.width), height(other.height), toric(other.toric), ruleSet(other.ruleSet) {
    
    cells.resize(width * height);
    
    for (size_t i = 0; i < cells.size(); ++i) {
        const Cell& otherCell = other.cells[i];
        
        cells[i].initialize(otherCell.getX(), otherCell.getY());
        
        if (otherCell.getState() != nullptr) {
            cells[i].setState(otherCell.getState()->clone());
        }
        
        cells[i].setFixed(otherCell.isFixed());
    }
}

// Copy Assignment Operator (needed for the gridTester class)
Grid& Grid::operator=(const Grid& other) {
    if (this != &other) {
        width = other.width;
        height = other.height;
        toric = other.toric;
        ruleSet = other.ruleSet;
        
        cells.clear();
        cells.resize(width * height);
        
        for (size_t i = 0; i < cells.size(); ++i) {
            const Cell& otherCell = other.cells[i];
            
            cells[i].initialize(otherCell.getX(), otherCell.getY());
            
            if (otherCell.getState() != nullptr) {
                cells[i].setState(otherCell.getState()->clone());
            }
            
            cells[i].setFixed(otherCell.isFixed());
        }
    }
    return *this;
}

// Destructor
Grid::~Grid() {}

// Size setter
void Grid::setSize(size_t width, size_t height) {
    if (width != 0) {
        if (height != 0) {
            this->width = width;
            this->height = height;
            cells.resize(width*height);
        } else { throw invalid_argument("Grid height can't be 0"); } // error if grid height set to 0
    } else { throw invalid_argument("Grid width can't be 0"); } // error if grid width set to 0
}

// Update grid
void Grid::update() {
    for (Cell& cell : cells) { // prepare nextState on all cells
        if (cell.isFixed()) continue; // ignore if fixed
        int neighbors = countNeighbors(cell.getX(), cell.getY());
        bool currentlyAlive = cell.isAlive();
        CellState* nextState = ruleSet->calculateNextState(currentlyAlive, neighbors);
        cell.prepareNextState(nextState);
    }
    for (Cell& cell : cells) { if (!cell.isFixed()) cell.applyNextState(); } // Apply nextState on all cells
}

// Count neighbors for a cell
size_t Grid::countNeighbors(int x, int y) {
    size_t count = 0;
    
    // Check all 8 neighbors
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) {
                continue;
            }
            
            int nx = x + dx;
            int ny = y + dy;
            
            if (toric) {
                nx = (nx + width) % width;
                ny = (ny + height) % height;
                
                size_t index = ny * width + nx;
                if (cells[index].isAlive()) {
                    count++;
                }
            } else {
                if (nx >= 0 && nx < (int)width && ny >= 0 && ny < (int)height) {
                    size_t index = ny * width + nx;
                    if (cells[index].isAlive()) count++;
                }
            }
        }
    }

    return count;
}

// Cell getter
Cell& Grid::getCell(int x, int y) { 
    size_t index = y*width+x;
    return cells[index]; 
}

// Grid size getters
size_t Grid::getWidth() const { return width; }
size_t Grid::getHeight() const { return height; }

// Toric getter
bool Grid::isToric() const { return toric; }

// Toric setter
void Grid::setToric(bool toric) { this->toric = toric; }

// Returns text grid
string Grid::textGrid() {
    string grid;
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            size_t index = y*width+x;
            grid.append(1, cells[index].isAlive());
        }
        grid.append("\n");
    }
    return grid;
}

// Rules setter
void Grid::setRuleSet(RuleSet* rules) { ruleSet = rules; }