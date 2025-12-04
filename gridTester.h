#ifndef GRIDTESTER_H
#define GRIDTESTER_H

#include "grid.h"

class GridTester {
public:
    // Compare a grid evolved 'iterations' times to an expected grid
    static bool testGrid(Grid& initialGrid, Grid& expectedGrid, int iterations);

    static void runAllTests();  // Run basic tests and print the results
};

#endif // GRIDTESTER_H