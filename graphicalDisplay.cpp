#include "graphicalDisplay.h"

// Constructor
GraphicalDisplay::GraphicalDisplay(int width, int height, int cellSize) 
    : cellSize(cellSize), delay(100) {
    
    // Create the SFML window with Vector2u for size (SFML 3.0 change)
    int windowWidth = width * cellSize;
    int windowHeight = height * cellSize;
    window = new sf::RenderWindow(
        sf::VideoMode({static_cast<unsigned int>(windowWidth), 
                      static_cast<unsigned int>(windowHeight)}), 
        "Conway's Game of Life"
    );
}

// Destructor
GraphicalDisplay::~GraphicalDisplay() {
    if (window != nullptr) {
        if (window->isOpen()) {
            window->close();
        }
        delete window;
        window = nullptr;
    }
}

// Display the grid
void GraphicalDisplay::displayGrid(Grid& grid) {
    // Clear the window (black background)
    window->clear(sf::Color::Black);
    
    // Create a rectangle shape for cells
    sf::RectangleShape cell({static_cast<float>(cellSize - 1), 
                             static_cast<float>(cellSize - 1)});
    cell.setFillColor(sf::Color::White);
    
    // Draw each alive cell
    for (int y = 0; y < grid.getHeight(); y++) {
        for (int x = 0; x < grid.getWidth(); x++) {
            if (grid.getCell(x, y).isAlive()) {
                cell.setPosition({static_cast<float>(x * cellSize), 
                                 static_cast<float>(y * cellSize)});
                window->draw(cell);
            }
        }
    }
    
    // Display everything we drew
    window->display();
    
    // Apply delay
    sf::sleep(sf::milliseconds(delay));
}

// Check if window is still open
bool GraphicalDisplay::isOpen() {
    return window->isOpen();
}

// Handle SFML events (close window, key press, etc.)
void GraphicalDisplay::handleEvents() {
    // SFML 3.0: pollEvent returns std::optional<sf::Event>
    while (const std::optional event = window->pollEvent()) {
        // SFML 3.0: Use event->is<T>() for type checking
        if (event->is<sf::Event::Closed>()) {
            window->close();
        }
        
        // SFML 3.0: Use event->getIf<T>() to access event data
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            // SFML 3.0: Scoped enumerations
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                window->close();
            }
        }
    }
}

// Set delay between frames
void GraphicalDisplay::setDelay(int ms) {
    if (ms >= 0) {
        delay = ms;
    }
}

// Get window pointer
sf::RenderWindow* GraphicalDisplay::getWindow() {
    return window;
}