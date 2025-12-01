#ifndef DEAD_STATE.h
#define DEAD_STATE.h
#include "cellState.h"

class DeadState : public CellState {
public:
    bool isAlive();
    CellState* clone();
    char toChar();
};

#endif // deadState.h