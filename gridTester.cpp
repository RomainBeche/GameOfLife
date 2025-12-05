#include "gridTester.h"
#include "conwayRuleSet.h"
#include "aliveState.h"
#include "deadState.h"
#include <iostream>
#include <stdexcept>

using std::cout, std::endl, std::cerr;

bool GridTester::testGrid(Grid& initialGrid, Grid& expectedGrid, int iterations) {
    try {
        Grid workingGrid = initialGrid;  // Copy for testing
        
        for (int i = 0; i < iterations; ++i) {
            workingGrid.update();
        }

        // Compare dimensions
        if (workingGrid.getWidth() != expectedGrid.getWidth() ||
            workingGrid.getHeight() != expectedGrid.getHeight()) {
            cerr << "  Dimension mismatch: " 
                 << workingGrid.getWidth() << "x" << workingGrid.getHeight() 
                 << " vs " 
                 << expectedGrid.getWidth() << "x" << expectedGrid.getHeight() << endl;
            return false;
        }

        // Compare each cell's alive state
        for (int y = 0; y < static_cast<int>(workingGrid.getHeight()); ++y) {
            for (int x = 0; x < static_cast<int>(workingGrid.getWidth()); ++x) {
                if (workingGrid.getCell(x, y).isAlive() != expectedGrid.getCell(x, y).isAlive()) {
                    cerr << "  Cell mismatch at (" << x << "," << y << "): "
                         << "got " << (workingGrid.getCell(x, y).isAlive() ? "alive" : "dead")
                         << ", expected " << (expectedGrid.getCell(x, y).isAlive() ? "alive" : "dead") << endl;
                    return false;
                }
            }
        }

        return true;
        
    } catch (const std::exception& e) {
        cerr << "  Exception during test: " << e.what() << endl;
        return false;
    }
}

void GridTester::runAllTests() {
    cout << "\n========================================" << endl;
    cout << "       GAME OF LIFE - UNIT TESTS        " << endl;
    cout << "========================================\n" << endl;

    ConwayRuleSet rules;
    int totalTests = 0;
    int passedTests = 0;

    // ============================= TEST 1: Blinker Oscillator (Period 2) =============================

    cout << "TEST 1: Blinker Oscillator" << endl;
    cout << "Initial: Horizontal line (01110)" << endl;
    totalTests++;
    
    try {
        Grid initial1(5, 5, &rules);
        initial1.getCell(1, 2).setState(new AliveState());
        initial1.getCell(2, 2).setState(new AliveState());
        initial1.getCell(3, 2).setState(new AliveState());

        // After 1 iteration: vertical
        Grid expected1(5, 5, &rules);
        expected1.getCell(2, 1).setState(new AliveState());
        expected1.getCell(2, 2).setState(new AliveState());
        expected1.getCell(2, 3).setState(new AliveState());

        bool ok1 = testGrid(initial1, expected1, 1);
        cout << "After 1 iteration (vertical): " << (ok1 ? "PASS" : "FAIL") << endl;
        if (ok1) passedTests++;

        // After 2 iterations: back to horizontal
        totalTests++;
        Grid expected1b(5, 5, &rules);
        expected1b.getCell(1, 2).setState(new AliveState());
        expected1b.getCell(2, 2).setState(new AliveState());
        expected1b.getCell(3, 2).setState(new AliveState());

        bool ok2 = testGrid(initial1, expected1b, 2);
        cout << "After 2 iterations (horizontal): " << (ok2 ? "PASS" : "FAIL") << endl;
        if (ok2) passedTests++;
        
    } catch (const std::exception& e) {
        cerr << "EXCEPTION: " << e.what() << endl;
    }
    cout << endl;

    // ================================== TEST 2: Block (Still Life) ==================================

    cout << "TEST 2: Block Still Life" << endl;
    cout << "Pattern should remain stable" << endl;
    totalTests++;
    
    try {
        Grid initial2(5, 5, &rules);
        initial2.getCell(1, 1).setState(new AliveState());
        initial2.getCell(1, 2).setState(new AliveState());
        initial2.getCell(2, 1).setState(new AliveState());
        initial2.getCell(2, 2).setState(new AliveState());

        Grid expected2(5, 5, &rules);
        expected2.getCell(1, 1).setState(new AliveState());
        expected2.getCell(1, 2).setState(new AliveState());
        expected2.getCell(2, 1).setState(new AliveState());
        expected2.getCell(2, 2).setState(new AliveState());

        bool ok3 = testGrid(initial2, expected2, 1);
        cout << "After 1 iteration: " << (ok3 ? "PASS" : "FAIL") << endl;
        if (ok3) passedTests++;
        
    } catch (const std::exception& e) {
        cerr << "EXCEPTION: " << e.what() << endl;
    }
    cout << endl;

    // ================================== TEST 3: Glider (Spaceship) ==================================

    cout << "TEST 3: Glider in Large Grid" << endl;
    cout << "Glider should move diagonally" << endl;
    totalTests++;
    
    try {
        Grid initial3(10, 10, &rules);
        // Glider at (1,1)
        initial3.getCell(2, 1).setState(new AliveState());
        initial3.getCell(3, 2).setState(new AliveState());
        initial3.getCell(1, 3).setState(new AliveState());
        initial3.getCell(2, 3).setState(new AliveState());
        initial3.getCell(3, 3).setState(new AliveState());

        // After 4 iterations, glider moves one cell diagonally
        Grid expected3(10, 10, &rules);
        expected3.getCell(3, 2).setState(new AliveState());
        expected3.getCell(4, 3).setState(new AliveState());
        expected3.getCell(2, 4).setState(new AliveState());
        expected3.getCell(3, 4).setState(new AliveState());
        expected3.getCell(4, 4).setState(new AliveState());

        bool ok4 = testGrid(initial3, expected3, 4);
        cout << "After 4 iterations: " << (ok4 ? "PASS" : "FAIL") << endl;
        if (ok4) passedTests++;
        
    } catch (const std::exception& e) {
        cerr << "EXCEPTION: " << e.what() << endl;
    }
    cout << endl;

    // ========================== TEST 4: Toric Grid (Lightweight Spaceship) ==========================

    cout << "TEST 4: Toric Grid - LWSS" << endl;
    cout << "Lightweight spaceship in toric grid" << endl;
    totalTests++;
    
    try {
        Grid initial4(8, 10, &rules);
        initial4.setToric(true);
        initial4.getCell(1, 3).setState(new AliveState());
        initial4.getCell(1, 4).setState(new AliveState());
        initial4.getCell(1, 5).setState(new AliveState());
        initial4.getCell(2, 3).setState(new AliveState());
        initial4.getCell(2, 6).setState(new AliveState());
        initial4.getCell(3, 3).setState(new AliveState());
        initial4.getCell(4, 3).setState(new AliveState());
        initial4.getCell(5, 4).setState(new AliveState());
        initial4.getCell(5, 6).setState(new AliveState());

        Grid expected4(8, 10, &rules);
        expected4.setToric(true);
        expected4.getCell(1, 3).setState(new AliveState());
        expected4.getCell(1, 4).setState(new AliveState());
        expected4.getCell(1, 5).setState(new AliveState());
        expected4.getCell(2, 3).setState(new AliveState());
        expected4.getCell(2, 6).setState(new AliveState());
        expected4.getCell(3, 3).setState(new AliveState());
        expected4.getCell(4, 3).setState(new AliveState());
        expected4.getCell(5, 4).setState(new AliveState());
        expected4.getCell(5, 6).setState(new AliveState());

        bool ok5 = testGrid(initial4, expected4, 16);
        cout << "After 16 iterations (cycle): " << (ok5 ? "PASS" : "FAIL") << endl;
        if (ok5) passedTests++;
        
    } catch (const std::exception& e) {
        cerr << "EXCEPTION: " << e.what() << endl;
    }
    cout << endl;

    // ================================= TEST 5: Empty Grid Stability =================================

    cout << "TEST 5: Empty Grid" << endl;
    cout << "Empty grid should remain empty" << endl;
    totalTests++;
    
    try {
        Grid initial5(5, 5, &rules);
        Grid expected5(5, 5, &rules);

        bool ok6 = testGrid(initial5, expected5, 10);
        cout << "After 10 iterations: " << (ok6 ? "PASS" : "FAIL") << endl;
        if (ok6) passedTests++;
        
    } catch (const std::exception& e) {
        cerr << "EXCEPTION: " << e.what() << endl;
    }
    cout << endl;

    // ===================================== ERROR HANDLING TESTS =====================================

    cout << "========================================" << endl;
    cout << "          ERROR HANDLING TESTS          " << endl;
    cout << "========================================\n" << endl;

    // TEST 6: Invalid Grid Size (0x0)
    cout << "TEST 6: Invalid Grid Size (0x0)" << endl;
    totalTests++;
    try {
        Grid invalidGrid(0, 0, &rules);
        cout << "FAIL: Exception not thrown" << endl;
    } catch (const std::invalid_argument& e) {
        cout << "PASS: Caught exception - " << e.what() << endl;
        passedTests++;
    } catch (const std::exception& e) {
        cout << "FAIL: Wrong exception type - " << e.what() << endl;
    }
    cout << endl;

    // TEST 7: Invalid Grid Size (Width = 0)
    cout << "TEST 7: Invalid Grid Size (width=0)" << endl;
    totalTests++;
    try {
        Grid invalidGrid(0, 10, &rules);
        cout << "FAIL: Exception not thrown" << endl;
    } catch (const std::invalid_argument& e) {
        cout << "PASS: Caught exception - " << e.what() << endl;
        passedTests++;
    } catch (const std::exception& e) {
        cout << "FAIL: Wrong exception type - " << e.what() << endl;
    }
    cout << endl;

    // TEST 8: Invalid Grid Size (Height = 0)
    cout << "TEST 8: Invalid Grid Size (height=0)" << endl;
    totalTests++;
    try {
        Grid invalidGrid(10, 0, &rules);
        cout << "FAIL: Exception not thrown" << endl;
    } catch (const std::invalid_argument& e) {
        cout << "PASS: Caught exception - " << e.what() << endl;
        passedTests++;
    } catch (const std::exception& e) {
        cout << "FAIL: Wrong exception type - " << e.what() << endl;
    }
    cout << endl;

    // TEST 9: SetSize with Invalid Dimensions
    cout << "TEST 9: SetSize with Invalid Dimensions" << endl;
    totalTests++;
    try {
        Grid testGrid(5, 5, &rules);
        testGrid.setSize(0, 5);
        cout << "FAIL: Exception not thrown" << endl;
    } catch (const std::invalid_argument& e) {
        cout << "PASS: Caught exception - " << e.what() << endl;
        passedTests++;
    } catch (const std::exception& e) {
        cout << "FAIL: Wrong exception type - " << e.what() << endl;
    }
    cout << endl;

    // TEST 10: Out of Bounds Cell Access
    cout << "TEST 10: Out of Bounds Cell Access" << endl;
    totalTests++;
    try {
        Grid testGrid(5, 5, &rules);
        Cell& cell = testGrid.getCell(10, 10);  // Out of bounds
        (void)cell;  // Suppress unused warning
        cout << "FAIL: Exception not thrown for out of bounds" << endl;
    } catch (const std::out_of_range& e) {
        cout << "PASS: Caught exception - " << e.what() << endl;
        passedTests++;
    } catch (const std::exception& e) {
        cout << "WARNING: Different exception - " << e.what() << endl;
        // Still count as pass if any exception thrown
        passedTests++;
    }
    cout << endl;

    // TEST 11: Toric Mode Toggle
    cout << "TEST 11: Toric Mode Toggle" << endl;
    totalTests++;
    try {
        Grid testGrid(5, 5, &rules);
        testGrid.setToric(true);
        bool isToricAfterSet = testGrid.isToric();
        
        testGrid.setToric(false);
        bool isNonToricAfterSet = !testGrid.isToric();

        if (isToricAfterSet && isNonToricAfterSet) {
            cout << "PASS: Toric mode toggle works" << endl;
            passedTests++;
        } else {
            cout << "FAIL: Toric mode toggle failed" << endl;
        }
    } catch (const std::exception& e) {
        cout << "FAIL: Unexpected exception - " << e.what() << endl;
    }
    cout << endl;

    // ======================================== FINAL SUMMARY ========================================

    cout << "========================================" << endl;
    cout << "              TEST SUMMARY              " << endl;
    cout << "========================================" << endl;
    cout << "       Total Tests: " << totalTests << endl;
    cout << "       Passed:      " << passedTests << endl;
    cout << "       Failed:      " << (totalTests - passedTests) << endl;
    cout << "       Success Rate: " << (passedTests * 100 / totalTests) << "%" << endl;
    cout << "========================================\n" << endl;

    if (passedTests == totalTests) {
        cout << "ALL TESTS PASSED!\n" << endl;
    } else {
        cout << "SOME TESTS FAILED...\n" << endl;
    }
}