#include "consoleDisplay.h"

ConsoleDisplay::ConsoleDisplay(const std::string& folder) : outputFolder(folder) {}

void ConsoleDisplay::displayGrid(Grid& grid) { std::cout << grid.textGrid() << std::endl; }
    
bool ConsoleDisplay::isOpen() { return true; }

void ConsoleDisplay::handleEvents() {}