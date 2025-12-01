#ifndef ALIVE_STATE.h
#define ALIVE_STATE.h
#include "cellState.h"

class AliveState : public CellState {
public:
    bool isAlive();
    CellState* clone();
    char toChar();
};

#endif // aliveState.h