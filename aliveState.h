#ifndef ALIVE_STATE_h
#define ALIVE_STATE_h
#include "cellState.h"

class AliveState : public CellState {
public:
    bool isAlive();
    CellState* clone();
    char toChar();
};

#endif // aliveState.h