#include <iostream>
#include "file.h"
#include "grid.h"
#include "conwayRuleSet.h"
#include "consoleDisplay.h"
#include "graphicalDisplay.h"
#include "aliveState.h"
#include "deadState.h"

// Simple test for File class: read a grid, then write it out as generation 0
void testFile() {
    std::cout << "=== testFile ===" << std::endl;

    ConwayRuleSet rules;
    File file;

    file.setInputFile("input.txt");      // Make sure this file exists
    file.createOutputFolder();

    Grid grid = file.readGrid(&rules);   // Read initial grid
    file.writeFile(grid, 0);             // Write generation 0

    std::cout << "File test completed: readGrid + writeFile." << std::endl;
}

// Test for ConsoleDisplay: display a small grid in the console
void testConsoleDisplay() {
    std::cout << "=== testConsoleDisplay ===" << std::endl;

    ConwayRuleSet rules;
    Grid grid(5, 5, &rules);

    // Manually set some cells alive for testing
    grid.getCell(1, 1).setState(new AliveState());
    grid.getCell(2, 2).setState(new AliveState());
    grid.getCell(3, 3).setState(new AliveState());

    ConsoleDisplay consoleDisplay("output");

    // Single display test
    consoleDisplay.displayGrid(grid);
    consoleDisplay.handleEvents(); // No-op in console mode

    std::cout << "ConsoleDisplay test completed." << std::endl;
}

// Test for GraphicalDisplay: open a window and show a simple pattern
void testGraphicalDisplay() {
    std::cout << "=== testGraphicalDisplay ===" << std::endl;

    ConwayRuleSet rules;
    const int width = 20;
    const int height = 20;
    const int cellSize = 20;

    Grid grid(width, height, &rules);

    // Create a simple pattern (diagonal)
    for (int i = 0; i < 10; ++i) {
        grid.getCell(i, i).setState(new AliveState());
    }

    GraphicalDisplay gDisplay(width, height, cellSize);
    gDisplay.setDelay(100);

    // Run a small loop just to test rendering and events
    int frames = 100;
    while (gDisplay.isOpen() && frames-- > 0) {
        gDisplay.handleEvents();
        gDisplay.displayGrid(grid);
        // No update to grid here, just static display
    }

    std::cout << "GraphicalDisplay test completed." << std::endl;
}

int main() {
    try {
        testFile();
        testConsoleDisplay();
        testGraphicalDisplay();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}