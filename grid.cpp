#include "grid.h"
#include "conwayRuleSet.h"
#include <exception>

// Constructors
Grid::Grid() : width(0), height(0), toric(false), ruleSet(nullptr) {}

Grid::Grid(size_t width, size_t height, RuleSet* rules) : toric(false), ruleSet(rules) { 
    if (width != 0 && height != 0) {
        this->width = width;
        this->height = height;
        cells.resize(width*height);
        for (size_t y = 0; y < height; y++) {
            for (size_t x = 0; x < width; x++) {
                size_t index = y*width+x;
                cells[index].initialize(x,y);
            }
        }
    } else { throw std::invalid_argument("Grid size can't be 0"); }
}

// Destructor
Grid::~Grid() {}

// Size setter
void Grid::setSize(size_t width, size_t height) {
    if (width != 0 && height != 0) {
        this->width = width;
        this->height = height;
        cells.resize(width*height);
    } else { throw std::invalid_argument("Grid size can't be 0"); } // error if grid size set to 0 by 0
}

// Update grid
void Grid::update() {
    for (Cell& cell : cells) { // prepare nextState on all cells
        if (cell.isFixed()) { continue; } // ignore if fixed
        int neighbors = countNeighbors(cell.getX(), cell.getY());
        bool currentlyAlive = cell.isAlive();
        CellState* nextState = ruleSet->calculateNextState(currentlyAlive, neighbors);
        cell.prepareNextState(nextState);
    }
    for (Cell& cell : cells) { if (!cell.isFixed()) { cell.applyNextState(); }} // Apply nextState on all cells
}

// Count neighbors for a cell
size_t Grid::countNeighbors(int x, int y) {
    size_t count = 0;  // Initialize!
    
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
                    if (cells[index].isAlive()) {
                        count++;
                    }
                }
            }
        }
    }

    return count;
}

// Cell getter
Cell& Grid::getCell(int x, int y) { return ; }

// Grid size getters
size_t Grid::getWidth() const { return width; }
size_t Grid::getHeight() const { return height; }

// 
bool Grid::isToric() const { return toric; }

void Grid::setToric(bool toric) { this->toric = toric; }

std::string Grid::textGrid() {
    std::string grid;
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            size_t index = y*width+x;
            if (cells[index].isAlive()) { grid.append("1"); } else { grid.append("0"); }
        }
        grid.append("\n");
    }
    return grid;
}

void Grid::setRuleSet(RuleSet* rules) {}