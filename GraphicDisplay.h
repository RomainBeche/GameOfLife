#include <iostream>
#include "Display.h"

class GraphicDisplay : public Display {
public:
    GraphicDisplay() = default;

    void displayGrid(Grid& grid) override {
        std::cout << "Affichage graphique non implémenté" << std::endl;
    }

    bool isOpen() override {
        return true;
    }

    void handleEvents() override {}
};
