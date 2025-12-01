#ifndef CELL_STATE_H
#define CELL_STATE_H

class CellState {
public:
    virtual bool isAlive() = 0;
    virtual CellState* clone() = 0;
    virtual char toChar() = 0;
};

#endif // cellState.h