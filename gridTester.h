#ifndef GRIDTESTER_H
#define GRIDTESTER_H

#include "grid.h"

class GridTester {
public:
    // Compare a grid evolved 'iterations' times to an expected grid
    static bool testGrid(Grid initialGrid, Grid& expectedGrid, int iterations);

    // Run basic tests and print the results
    static void runAllTests();
};

#endif // GRIDTESTER_H