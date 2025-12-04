#ifndef CELL_H
#define CELL_H
#include "cellState.h"

class Cell {
private:
    CellState* state;
    CellState* nextState;
    bool fixed;
    int x;
    int y;

public:
    Cell();
    Cell(int x, int y);
    ~Cell();

    void initialize(int x, int y);
    void setState(CellState* state);
    void prepareNextState(CellState* state);
    void applyNextState();
    bool isAlive() const;
    int getX() const;
    int getY() const;
    void setFixed(bool fixed);
    bool isFixed() const;
};

#endif // CELL_H