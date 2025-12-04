#include <iostream>
#include <string>
#include "gameOfLife.h"
#include "grid.h"
#include "file.h"
#include "conwayRuleSet.h"
#include "consoleDisplay.h"
#include "graphicalDisplay.h"

void printUsage() {
    std::cout << "Usage: ./exec <input_file> [options]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --mode <0|1>        0=console (default), 1=graphical" << std::endl;
    std::cout << "  --toric <0|1>       0=non-toric (default), 1=toric" << std::endl;
    std::cout << "  --delay <ms>        Delay between iterations (default: 100ms)" << std::endl;
    std::cout << "  --max-gen <n>       Maximum generations (default: 1000)" << std::endl;
    std::cout << "  --cell-size <n>     Cell size in pixels for graphical mode (default: 10)" << std::endl;
}

int main(int argc, char* argv[]) {
    // Check minimum arguments
    if (argc < 2) {
        std::cerr << "Error: Input file required!" << std::endl;
        printUsage();
        return 1;
    }
    
    // Parse command line arguments
    std::string inputFile = argv[1];
    int mode = 0;           // 0 = console, 1 = graphical
    bool toric = false;
    int delay = 100;
    int maxGen = 1000;
    int cellSize = 10;
    
    // Parse optional arguments
    for (int i = 2; i < argc - 1; i += 2) {
        std::string arg = argv[i];
        
        if (arg == "--mode") {
            mode = std::stoi(argv[i + 1]);
        } else if (arg == "--toric") {
            toric = (std::stoi(argv[i + 1]) == 1);
        } else if (arg == "--delay") {
            delay = std::stoi(argv[i + 1]);
        } else if (arg == "--max-gen") {
            maxGen = std::stoi(argv[i + 1]);
        } else if (arg == "--cell-size") {
            cellSize = std::stoi(argv[i + 1]);
        }
    }
    
    try {
        // Create rule set
        RuleSet* ruleSet = new ConwayRuleSet();
        
        // Create file reader
        File* file = new File();
        file->setInputFile(inputFile);
        
        // Read grid from file
        Grid grid = file->readGrid(ruleSet);
        grid.setToric(toric);
        
        // Create display based on mode
        Display* display = nullptr;
        
        if (mode == 0) {
            // Console mode
            std::string outputFolder = inputFile + "_out";
            display = new ConsoleDisplay(outputFolder);
            std::cout << "Running in console mode. Output folder: " << outputFolder << std::endl;
        } else if (mode == 1){
            // Graphical mode
            std::cout << "Grid dimensions: " << grid.getWidth() << "x" << grid.getHeight() << std::endl;
            std::cout << "Cell size: " << cellSize << std::endl;
            std::cout << "Window will be: " << (grid.getWidth() * cellSize) << "x" << (grid.getHeight() * cellSize) << " pixels" << std::endl;
            
            display = new GraphicalDisplay(
                grid.getWidth(), 
                grid.getHeight(), 
                cellSize
            );
            if (display != nullptr) {
                // Set delay for graphical display
                GraphicalDisplay* graphDisplay = dynamic_cast<GraphicalDisplay*>(display);
                if (graphDisplay) {
                    graphDisplay->setDelay(delay);
                }
            }
            std::cout << "Running in graphical mode. Cell size: " << cellSize << "px" << std::endl;
        } else { throw std::invalid_argument("Invalid mode"); }
        
        // Create and configure GameOfLife
        GameOfLife* game = new GameOfLife();
        game->setGrid(&grid);
        game->setDisplay(display);
        game->setFile(inputFile);
        game->setMode(mode);
        game->setDelay(delay);
        game->setMaxGenerations(maxGen);
        game->setToric(toric);
        
        // Start simulation
        game->start();
        
        // Cleanup
        delete game;
        delete display;
        delete file;
        delete ruleSet;
        
        std::cout << "Game of Life completed successfully!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}