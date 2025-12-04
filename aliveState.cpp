#include "aliveState.h"

bool AliveState::isAlive() { return true; }
CellState* AliveState::clone() { return new AliveState(); }
char AliveState::toChar() { return '1'; }