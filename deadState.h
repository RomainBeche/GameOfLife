#ifndef DEAD_STATE_H
#define DEAD_STATE_H
#include "cellState.h"

class DeadState : public CellState {
public:
    bool isAlive() override;
    CellState* clone() override;
    char toChar() override;
};

#endif // DEAD_STATE_H