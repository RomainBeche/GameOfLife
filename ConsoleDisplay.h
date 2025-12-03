#ifndef CONSOLE_DISPLAY_H
#define CONSOLE_DISPLAY_H

#include <iostream>
#include <string>
#include "display.h"

class ConsoleDisplay : public Display {
private:
    string outputFolder;
public:
    ConsoleDisplay(const string& folder);

    void displayGrid(Grid& grid) override;
        
    bool isOpen() override;

    void handleEvents() override;
};

#endif // CONSOLE_DISPLAY_H