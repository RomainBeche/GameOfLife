#ifndef GRID_H
#define GRID_H

#include "cell.h"
#include "ruleSet.h"

#include <cstddef>
#include <vector>
#include <string>

class Grid {
private:
    size_t width;
    size_t height;
    std::vector<Cell> cells;
    bool toric;
    RuleSet* ruleSet;

public:
    Grid();
    Grid(size_t width, size_t height, RuleSet* rules);
    ~Grid();
    void setSize(size_t width, size_t height);
    void update();
    size_t countNeighbors(int x, int y);
    Cell& getCell(int x, int y);
    size_t getWidth() const;
    size_t getHeight() const;
    bool isToric() const;
    void setToric(bool toric);
    std::string textGrid();
    void setRuleSet(RuleSet* rules);
};

#endif // grid.h