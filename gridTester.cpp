#include "gridTester.h"
#include "conwayRuleSet.h"
#include "aliveState.h"
#include "deadState.h"
#include <iostream>

bool GridTester::testGrid(Grid initialGrid, Grid& expectedGrid, int iterations) {
    // Evolve the grid 'iterations' times
    for (int i = 0; i < iterations; ++i) initialGrid.update();

    // Compare dimensions
    if (initialGrid.getWidth() != expectedGrid.getWidth() ||
        initialGrid.getHeight() != expectedGrid.getHeight()) {
        return false;
    }

    // Compare each cell's alive state
    for (int y = 0; y < static_cast<int>(initialGrid.getHeight()); ++y) {
        for (int x = 0; x < static_cast<int>(initialGrid.getWidth()); ++x) {
            if (initialGrid.getCell(x, y).isAlive() != expectedGrid.getCell(x, y).isAlive()) return false;
        }
    }

    return true;
}

void GridTester::runAllTests() {
    std::cout << "##### GridTester::runAllTests #####" << std::endl;

    ConwayRuleSet rules;

    // Example test: blinker oscillator
    // Generation 0:
    // 00000
    // 00000
    // 01110
    // 00000
    // 00000

    Grid initial(5, 5, &rules);
    initial.getCell(1, 2).setState(new AliveState());
    initial.getCell(2, 2).setState(new AliveState());
    initial.getCell(3, 2).setState(new AliveState());

    // Expected after 1 iteration:
    // 00000
    // 00100
    // 00100
    // 00100
    // 00000

    Grid expected1(5, 5, &rules);
    expected1.getCell(2, 1).setState(new AliveState());
    expected1.getCell(2, 2).setState(new AliveState());
    expected1.getCell(2, 3).setState(new AliveState());

    bool ok1 = testGrid(initial, expected1, 1);
    std::cout << "Blinker test (1 iteration): " << (ok1 ? "OK" : "FAIL") << std::endl;

    // Expected after 2 iterations: back to initial
    bool ok2 = testGrid(initial, initial, 2);
    std::cout << "Blinker test (2 iterations): " << (ok2 ? "OK" : "FAIL") << std::endl;
}