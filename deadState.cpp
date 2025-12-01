#include "deadState.h"

bool DeadState::isAlive() { return false; }
CellState* DeadState::clone() { return new DeadState(); }
char DeadState::toChar() { return '.'; }