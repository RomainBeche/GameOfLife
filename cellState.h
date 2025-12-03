#ifndef CELL_STATE_H
#define CELL_STATE_H

class CellState {
public:
    virtual bool isAlive() = 0; // Returns true if cell alive
    virtual CellState* clone() = 0; // Clone cell
    virtual char toChar() = 0; // Convert cell state to char
    virtual ~CellState() {} // Cell destructor
};

#endif // CELL_STATE_H