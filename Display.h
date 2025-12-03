#ifndef DISPLAY_H
#define DISPLAY_H

#include "grid.h"

class Display {
public:
    virtual void displayGrid(Grid& grid) = 0;
    virtual bool isOpen() = 0;
    virtual void handleEvents() = 0;
    virtual ~Display() {}
};

#endif // DISPLAY_H
