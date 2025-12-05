    #include "gridTester.h"
    #include "conwayRuleSet.h"
    #include "aliveState.h"
    #include "deadState.h"
    #include <iostream>

    using std::cout, std::endl;

    bool GridTester::testGrid(Grid& initialGrid, Grid& expectedGrid, int iterations) {
    Grid initialGridCopy = initialGrid;  // Copy for testing
    
    for (int i = 0; i < iterations; ++i) initialGridCopy.update();

    // Compare dimensions
    if (initialGridCopy.getWidth() != expectedGrid.getWidth() ||
        initialGridCopy.getHeight() != expectedGrid.getHeight()) {
        return false;
    }

    // Compare each cell's alive state
    for (int y = 0; y < static_cast<int>(initialGridCopy.getHeight()); ++y) {
        for (int x = 0; x < static_cast<int>(initialGridCopy.getWidth()); ++x) {
            if (initialGridCopy.getCell(x, y).isAlive() != expectedGrid.getCell(x, y).isAlive()) {
                return false;
            }
        }
    }

    return true;
}

    void GridTester::runAllTests() {
        cout << "##### GridTester::runAllTests #####" << endl;

        ConwayRuleSet rules;

        // Example test 1: blinker oscillator
        // Generation 0:
        // 00000
        // 00000
        // 01110
        // 00000
        // 00000

        Grid initial1(5, 5, &rules);
        initial1.getCell(1, 2).setState(new AliveState());
        initial1.getCell(2, 2).setState(new AliveState());
        initial1.getCell(3, 2).setState(new AliveState());

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

        bool ok1 = testGrid(initial1, expected1, 1);
        cout << "Blinker test (1 iteration): " << (ok1 ? "OK" : "FAIL") << endl;

        // Expected after 2 iterations: back to initial
        bool ok2 = testGrid(initial1, initial1, 2);
        cout << "Blinker test (2 iterations): " << (ok2 ? "OK" : "FAIL") << endl;

        // Example test 2: block
        // 00000
        // 01100
        // 01100
        // 00000
        // 00000

        Grid initial2(5, 5, &rules);
        initial2.getCell(1, 1).setState(new AliveState());
        initial2.getCell(1, 2).setState(new AliveState());
        initial2.getCell(2, 1).setState(new AliveState());
        initial2.getCell(2, 2).setState(new AliveState());

        // Expected after 1 iteration is the same as initial

        bool ok3 = testGrid(initial2, initial2, 1);
        cout << "Block test (1 iteration): " << (ok3 ? "OK" : "FAIL") << endl;

        // Example test 3: lightweight spaceship in a toric grid
        // 00000000
        // 00000000
        // 00000000
        // 01111000
        // 01000100
        // 01000000
        // 00100100
        // 00000000
        // 00000000
        // 00000000

        Grid initial3(8, 10, &rules);
        initial3.setToric(true);
        initial3.getCell(1, 3).setState(new AliveState());
        initial3.getCell(1, 4).setState(new AliveState());
        initial3.getCell(1, 5).setState(new AliveState());
        initial3.getCell(2, 3).setState(new AliveState());
        initial3.getCell(2, 6).setState(new AliveState());
        initial3.getCell(3, 3).setState(new AliveState());
        initial3.getCell(4, 3).setState(new AliveState());
        initial3.getCell(5, 4).setState(new AliveState());
        initial3.getCell(5, 6).setState(new AliveState());

        // Expected grid after 16 iterations is the same as initial

        bool ok4 = testGrid(initial3, initial3, 16);
        cout << "Toric grid test (16 iterations): " << (ok3 ? "OK" : "FAIL") << endl;
    }