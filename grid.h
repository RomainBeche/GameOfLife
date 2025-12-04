#ifndef GRID_H
#define GRID_H

#include "cell.h"
#include "ruleSet.h"

#include <cstddef>
#include <vector>
#include <string>

using std::string, std::invalid_argument, std::vector;

class Grid {
private:
    size_t width;
    size_t height;
    vector<Cell> cells;
    bool toric;
    RuleSet* ruleSet;

public:
    Grid();
    Grid(size_t width, size_t height, RuleSet* rules);
    Grid(const Grid& other);                // Copy constructor
    Grid& operator=(const Grid& other);     // Copy assignment
    ~Grid();
    void setSize(size_t width, size_t height);
    void update();
    size_t countNeighbors(int x, int y);
    Cell& getCell(int x, int y);
    size_t getWidth() const;
    size_t getHeight() const;
    bool isToric() const;
    void setToric(bool toric);
    string textGrid();
    void setRuleSet(RuleSet* rules);
};

#endif // GRID_H