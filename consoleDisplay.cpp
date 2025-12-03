#include "consoleDisplay.h"

ConsoleDisplay::ConsoleDisplay(const std::string& folder) : outputFolder(folder) {} // Constructor

// Display the grid using textGrid() method
void ConsoleDisplay::displayGrid(Grid& grid) {} // Nothing to display in console

bool ConsoleDisplay::isOpen() { return true; }

void ConsoleDisplay::handleEvents() {} // Empty method here because not relevant to implement