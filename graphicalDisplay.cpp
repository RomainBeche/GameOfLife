#include "graphicalDisplay.h"
#include <iostream>

using sf::RenderWindow, sf::VideoMode, sf::Color, sf::RectangleShape, sf::sleep, sf::milliseconds, sf::Event, std::optional;

// Constructor
GraphicalDisplay::GraphicalDisplay(int width, int height, int cellSize) : cellSize(cellSize), delay(500) {
    
    // Create the SFML window (SFML 3.0 change)
    int windowWidth = width * cellSize;
    int windowHeight = height * cellSize;
    window = new RenderWindow(
        VideoMode({static_cast<unsigned int>(windowWidth), 
                       static_cast<unsigned int>(windowHeight)}), 
        "Conway's Game of Life"
    );
}

// Destructor
GraphicalDisplay::~GraphicalDisplay() {
    if (window != nullptr) {
        if (window->isOpen()) window->close();
        delete window;
        window = nullptr;
    }
}


void GraphicalDisplay::displayGrid(Grid& grid) {
    window->clear(Color::Black);
    
    // Init ailve cells shapes
    RectangleShape aliveCell({static_cast<float>(cellSize - 1), 
                                   static_cast<float>(cellSize - 1)});
    aliveCell.setFillColor(Color::White);
    
    // Init grid lines
    RectangleShape gridLine;
    gridLine.setFillColor(Color(40, 40, 40));
    
    // Draw vertical lines
    for (int x = 0; x <= grid.getWidth(); x++) {
        gridLine.setSize({1.0f, static_cast<float>(grid.getHeight() * cellSize)});
        gridLine.setPosition({static_cast<float>(x * cellSize), 0.0f});
        window->draw(gridLine);
    }
    
    // Draw horizontal lines
    for (int y = 0; y <= grid.getHeight(); y++) {
        gridLine.setSize({static_cast<float>(grid.getWidth() * cellSize), 1.0f});
        gridLine.setPosition({0.0f, static_cast<float>(y * cellSize)});
        window->draw(gridLine);
    }
    
    // Draw alive cells
    for (int y = 0; y < grid.getHeight(); y++) {
        for (int x = 0; x < grid.getWidth(); x++) {
            if (grid.getCell(x, y).isAlive()) {
                aliveCell.setPosition({static_cast<float>(x * cellSize), 
                                       static_cast<float>(y * cellSize)});
                window->draw(aliveCell);
            }
        }
    }
    
    window->display();
    sleep(milliseconds(delay));
}

// Check if window is still open
bool GraphicalDisplay::isOpen() { return window->isOpen(); }

// Handle SFML events
void GraphicalDisplay::handleEvents() {
    // SFML 3.0: pollEvent returns std::optional<sf::Event>
    while (const optional event = window->pollEvent()) {
        if (event->is<Event::Closed>()) window->close(); // Close window properly
        
        // Key pressed detection
        if (const auto* keyPressed = event->getIf<Event::KeyPressed>()) {
            // If escape key pressed: close window
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) window->close();
        }
    }
}

// Set delay between frames
void GraphicalDisplay::setDelay(int ms) { if (ms >= 0) delay = ms; }

// Get window pointer
RenderWindow* GraphicalDisplay::getWindow() { return window; }