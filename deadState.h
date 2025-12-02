#ifndef DEAD_STATE_h
#define DEAD_STATE_h
#include "cellState.h"

class DeadState : public CellState {
public:
    bool isAlive();
    CellState* clone();
    char toChar();
};

#endif // deadState.h