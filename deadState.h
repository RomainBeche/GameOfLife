#ifndef DEAD_STATE_h
#define DEAD_STATE_h
#include "cellState.h"

class DeadState : public CellState {
public:
    bool isAlive() override;
    CellState* clone() override;
    char toChar() override;
};

#endif // DEAD_STATE_H