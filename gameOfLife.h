#include <unordered_set>
#include <string>

#include "grid.h"
#include "display.h"
#include "file.h"

#include <SFML/Graphics.hpp>

class GameOfLife {
private:
    int mode;
    Grid grid;
    Display* display;
    sf::RenderWindow* window;
    File file;
    int delay;
    int maxGenerations;
    int generation;
    std::unordered_set<std::string> previousGrids;

public:
    GameOfLife();
    ~GameOfLife();
    void setFile(const std::string& filename);
    void setDelay(int ms);
    void setMaxGenerations(int max);
    void setMode(int mode);
    void setToric(bool toric);
    void start();

private:
    bool checkStability();
};
