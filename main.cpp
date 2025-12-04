#include <iostream>
#include <string>
#include "gameOfLife.h"
#include "grid.h"
#include "file.h"
#include "conwayRuleSet.h"
#include "consoleDisplay.h"
#include "graphicalDisplay.h"

using std::cerr, std::cout, std::endl, std::stoi, std::exception;

void printUsage() {
    cout << "Usage: ./exec <input_file> [options]" << endl;
    cout << "Options:" << endl;
    cout << "  --mode <0|1>        0: console, 1: graphical (default)" << endl;
    cout << "  --toric <0|1>       0: non-toric (default), 1: toric" << endl;
    cout << "  --delay <ms>        Delay between iterations (default: 500ms)" << endl;
    cout << "  --max-gen <n>       Maximum generations (default: 1000)" << endl;
    cout << "  --cell-size <n>     Cell size in pixels for graphical mode (default: 10)" << endl;
}

int main(int argc, char* argv[]) {
    // Check minimum arguments
    if (argc < 2) {
        cerr << "Error: Input file required!" << endl;
        printUsage();
        return 1;
    }
    
    // Parse command line arguments
    string inputFile = argv[1];
    int mode = 1;
    bool toric = false;
    int delay = 500;
    int maxGen = 1000;
    int cellSize = 10;
    
    // Parse optional arguments
    for (int i = 2; i < argc - 1; i += 2) {
        string arg = argv[i];
        
        if (arg == "--mode") {
            mode = stoi(argv[i + 1]);
        } else if (arg == "--toric") {
            toric = (stoi(argv[i + 1]) == 1);
        } else if (arg == "--delay") {
            delay = stoi(argv[i + 1]);
        } else if (arg == "--max-gen") {
            maxGen = stoi(argv[i + 1]);
        } else if (arg == "--cell-size") {
            cellSize = stoi(argv[i + 1]);
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
            string outputFolder = inputFile + "_out";
            display = new ConsoleDisplay(outputFolder);
            cout << "Running in console mode. Output folder: " << outputFolder << endl;
        } else if (mode == 1){
            // Graphical mode
            cout << "Grid dimensions: " << grid.getWidth() << "x" << grid.getHeight() << endl;
            cout << "Cell size: " << cellSize << endl;
            cout << "Window will be: " << (grid.getWidth() * cellSize) << "x" << (grid.getHeight() * cellSize) << " pixels" << endl;
            
            display = new GraphicalDisplay(
                grid.getWidth(), 
                grid.getHeight(), 
                cellSize
            );

            if (display != nullptr) {
                // Set delay for graphical display
                GraphicalDisplay* graphDisplay = dynamic_cast<GraphicalDisplay*>(display);
                if (graphDisplay) graphDisplay->setDelay(delay);
            }
            cout << "Running in graphical mode. Cell size: " << cellSize << "px" << endl;
        } else { throw invalid_argument("Invalid mode"); }
        
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
        
        cout << "Game of Life completed successfully!" << endl;
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}