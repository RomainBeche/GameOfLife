#include "file.h"
#include "cell.h"
#include "aliveState.h"
#include "deadState.h"

#include <fstream>
#include <sstream>
#include <filesystem>
#include <stdexcept>

using namespace std::filesystem;
using std::ostringstream, std::runtime_error, std::ofstream, std::ifstream, std::vector;

File::File() : inputFile(""), outputFolder("output") {}

// Set the input file path
void File::setInputFile(const string& filename) { inputFile = filename; }

// Create the output folder if it doesn't exist
void File::createOutputFolder() {
    if (outputFolder.empty()) outputFolder = "output";
    if (!exists(outputFolder)) create_directories(outputFolder);
}

// Write the current grid to a text file named generation_X.txt
void File::writeFile(Grid& grid, int generation) {
    createOutputFolder();

    ostringstream oss;
    oss << outputFolder << "/generation_" << generation << ".txt";
    const string filepath = oss.str();

    ofstream out(filepath);
    if (!out) {
        throw runtime_error("Failed to open output file: " + filepath);
    }

    // Use Grid::textGrid() to get a string representation
    out << grid.textGrid() << '\n';
}

// Read initial grid from inputFile and build a Grid using the given RuleSet
Grid File::readGrid(RuleSet* ruleSet) {
    if (inputFile.empty()) {
        throw runtime_error("Input file not set");
    }

    ifstream in(inputFile);
    if (!in) {
        throw runtime_error("Failed to open input file: " + inputFile);
    }

    vector<string> lines;
    string line;
    while (getline(in, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back(); // Handle Windows line endings
        }
        if (!line.empty()) {
            lines.push_back(line);
        }
    }

    if (lines.empty()) {
        throw runtime_error("Input file is empty: " + inputFile);
    }

    const int height = static_cast<int>(lines.size());
    const int width = static_cast<int>(lines[0].size());

    // Create grid with the given RuleSet
    Grid grid(width, height, ruleSet);

    // Initialize cells from characters
    for (int y = 0; y < height; ++y) {
        if (static_cast<int>(lines[y].size()) != width) {
            throw runtime_error("Inconsistent line length in input file.");
        }
        for (int x = 0; x < width; ++x) {
            char c = lines[y][x];

            Cell& cell = grid.getCell(x, y);
            if (c == '*') { // Alive
                cell.setState(new AliveState());
            } else {        // Dead (default for any other char)
                cell.setState(new DeadState());
            }
        }
    }

    return grid;
}
