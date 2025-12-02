#include "Grid.h"

class Display {
public:
    virtual void displayGrid(Grid& grid) = 0;
    virtual bool isOpen() = 0;
    virtual void handleEvents() = 0;
};