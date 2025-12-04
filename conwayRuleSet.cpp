#include "conwayRuleSet.h"
#include "aliveState.h"
#include "deadState.h"

CellState* ConwayRuleSet::calculateNextState(bool currentlyAlive, int neighbors) {
    // Conway's game rules
    if (currentlyAlive) {
        if (neighbors == 2 || neighbors == 3) {
            return new AliveState; // Survives
        } else { return new DeadState; } // Dies
    } else {
        if (neighbors == 3) {
            return new AliveState; // Comes to life
        } else { return new DeadState; } // Dies
    }
}