#include <iostream>
#include <string>
#include "Display.h"

class ConsoleDisplay : public Display {
private:
    std::string outputFolder;
public:
    ConsoleDisplay(std::string& folder);

    void displayGrid(Grid& grid) override {
        std::cout << grid.textGrid() << std::endl;
    }
        
    bool isOpen() override {
        return true;
    }

    void handleEvents() override {}
};
