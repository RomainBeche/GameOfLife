#include "consoleDisplay.h"

ConsoleDisplay::ConsoleDisplay(const string& folder) : outputFolder(folder) {} // Constructor

// Display the grid using textGrid() method
void ConsoleDisplay::displayGrid(Grid& grid) {} // No grid to display in console

bool ConsoleDisplay::isOpen() { return true; } // No renderWindow here so always open

void ConsoleDisplay::handleEvents() {} // Empty method here because not relevant to implement