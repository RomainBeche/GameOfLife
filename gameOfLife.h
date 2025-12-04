#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include "grid.h"
#include "display.h"
#include "file.h"
#include <string>

class GameOfLife {
private:
    int mode;                               // 0 = console, 1 = graphical
    Grid* grid;
    Display* display;
    File* file;
    int delay;                              // Delay between iterations (ms)
    int generation;                         // Current generation number
    int maxGenerations;                     // Maximum generations number
    string previousGrid;                    // For stability detection

public:
    GameOfLife();
    ~GameOfLife();
    
    void setFile(const string& filename);
    void setDelay(int delay);
    void setMaxGenerations(int max);
    void setGrid(Grid* g);
    void setMode(int m);
    void setToric(bool toric);
    void setDisplay(Display* d);
    
    Grid* getGrid();
    int getGeneration() const;
    
    void start();
    
private:
    bool checkStability();
};

#endif