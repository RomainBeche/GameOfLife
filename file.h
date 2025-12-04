#ifndef FILE_H
#define FILE_H

#include <string>
#include "grid.h"
#include "ruleSet.h"

class File {
private:
    std::string inputFile;
    std::string outputFolder;

public:
    File();

    void setInputFile(const string& filename);
    void createOutputFolder();
    void writeFile(Grid& grid, int generation);
    Grid readGrid(RuleSet* ruleSet);
};

#endif // FILE_H
