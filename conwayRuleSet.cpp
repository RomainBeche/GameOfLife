#include "conwayRuleSet.h"
#include "aliveState.h"
#include "deadState.h"

CellState* ConwayRuleSet::calculateNextState(bool currentlyAlive, int neighbors) {
    if (currentlyAlive) {
        if (neighbors == 2 || neighbors == 3) {
            return new AliveState; // Survive
        } else { return new DeadState; } // Dies
    } else {
        if (neighbors == 3) {
            return new AliveState; // Comes to life
        } else { return new DeadState; } // Dies
    }
}