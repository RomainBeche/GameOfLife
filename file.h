#ifndef FILE_H
#define FILE_H

#include <string>

#include "grid.h"

using std::string;
class File {
private:
    string inputFile;
    string outputFolder;
public:
    File();
    void setInputFile(string fileName);
    void createOutputFolder();
    void writeFile(Grid grid, int generation);
    Grid readGrid(RuleSet* ruleSet);
};

#endif // FILE_H