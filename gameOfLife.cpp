#include "gameOfLife.h"
#include "grid.h"

GameOfLife::GameOfLife()
    : mode(0),          
      grid(),           
      display(nullptr),
      window(nullptr),
      file(),
      delay(0),
      maxGenerations(0),
      generation(0),
      previousGrids()
{
}

GameOfLife::~GameOfLife() = default;

void GameOfLife::setFile(const std::string& filename) {
    file.setInputFile(filename);
}

void GameOfLife::setDelay(int ms) {
    delay = ms;
}


void GameOfLife::setMaxGenerations(int max) {
    maxGenerations = max;
}

void GameOfLife::setMode(int m) {
    mode = m;
}

bool GameOfLife::checkStability() {
    std::string current = grid.textGrid();
    auto result = previousGrids.insert(current);
    if (result.second == false) {
        return true;
    }
    else {
        return false;
    }
}

void GameOfLife::setToric(bool toric) {
grid->setToric(Toric);
}
    
void GameOfLife::start() {

    generation = 0;

    previousGrids.clear();

    bool stop = false;

    while (stop == false) {

        display->displayGrid(grid);
        display->handleEvents();

        bool open = display->isOpen();
        if (open == false) {
            stop = true;
        }

        if (stop == false) {
            if (maxGenerations > 0) {
                if (generation >= maxGenerations) {
                    stop = true;
                }
            }
        }
        if (stop == false) {
            bool stable = checkStability();
            if (stable == true) {
                stop = true;
            }
        }
        if (stop == false) {
            grid.update();
            generation = generation + 1;
        }

        // 7) Si tu veux un délai entre les générations, tu pourras l'ajouter ici
        //    (par exemple avec std::this_thread::sleep_for), mais ce n'est pas obligatoire
    }
}


