#include <unordered_set>
#include <string>

#include "grid.h"
#include "display.h"
#include "file.h"

#include <SFML/Graphics.hpp>

using std::unordered_set;
using std::string;  

class GameOfLife {
private:
    int mode;
    Grid* grid;
    Display* display;
    sf::RenderWindow* window;
    File* file;
    int delay;
    int maxGenerations;
    int generation;
    unordered_set<string> previousGrids;

public:
    GameOfLife();
    ~GameOfLife();
    void setFile(const string& filename);
    void setDelay(int ms);
    void setMaxGenerations(int max);
    void setMode(int mode);
    void setToric(bool toric);
    void start();

private:
    bool checkStability();
};


