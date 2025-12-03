#ifndef GRAPHICAL_DISPLAY_H
#define GRAPHICAL_DISPLAY_H

#include "display.h"
#include "grid.h"
#include <SFML/Graphics.hpp>

class GraphicalDisplay : public Display {
private:
    int cellSize;
    sf::RenderWindow* window;
    int delay;  // Delay in milliseconds between frames

public:
    // Constructor
    GraphicalDisplay(int width, int height, int cellSize);
    
    // Destructor
    ~GraphicalDisplay();
    
    // Override Display methods
    void displayGrid(Grid& grid) override;
    bool isOpen() override;
    void handleEvents() override;
    
    // Additional methods
    void setDelay(int ms);
    sf::RenderWindow* getWindow();
};

#endif