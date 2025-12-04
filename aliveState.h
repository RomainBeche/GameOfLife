#ifndef ALIVE_STATE_H
#define ALIVE_STATE_H
#include "cellState.h"

class AliveState : public CellState {
public:
    bool isAlive() override;
    CellState* clone() override;
    char toChar() override;
};

#endif // ALIVE_STATE_H