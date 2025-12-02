#ifndef DISPLAY_H
#define DISPLAY_H

#include "Grid.h"

class Display {
public:
    virtual void displayGrid(Grid& grid) = 0;
    virtual bool isOpen() = 0;
    virtual void handleEvents() = 0;

};

#endif // display.h
