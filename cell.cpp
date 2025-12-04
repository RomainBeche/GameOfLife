#include "cell.h"
#include "deadState.h"

// Constructors
Cell::Cell() : state(nullptr), nextState(nullptr), fixed(false), x(0), y(0) {}
Cell::Cell(int x, int y) : state(nullptr), nextState(nullptr), fixed(false), x(x), y(y) {}

// Destructor
Cell::~Cell() {
    delete state;
    if (nextState != nullptr) delete nextState;
}

// Init method
void Cell::initialize(int x, int y) { 
    this->x = x;
    this->y = y;

    if (state != nullptr) delete state;

    state = new DeadState;
    nextState = nullptr;
    fixed = false;
}

// State setter
void Cell::setState(CellState* newState) { 
    if (state != nullptr) delete state;
    state = newState; 
}

// Prepare nextState
void Cell::prepareNextState(CellState* newState) { 
    if (nextState != nullptr) delete nextState;
    nextState = newState;
}

// Apply: state = nextState
void Cell::applyNextState() { 
    if (nextState != nullptr) {
        delete state;
        state = nextState;
        nextState = nullptr;
    }
}

// Cell state getter
bool Cell::isAlive() { return state->isAlive(); }

// Coordinates Getters
int Cell::getX() const { return x; }
int Cell::getY() const { return y; }

// fixed setter and getter
void Cell::setFixed(bool isFixed) { fixed = isFixed; }
bool Cell::isFixed() const { return fixed; }