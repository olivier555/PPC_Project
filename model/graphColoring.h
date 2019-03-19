

#ifndef GRAPHCOLORING_H
#define GRAPHCOLORING_H

#include "model.h"

#include <fstream>
#include <vector>
#include <utility>
using namespace std;


class graphColoring  : public model {
public:
    graphColoring(string pathFile, int nbColorsVar);
    void readFile(string pathFile);
    bool isBreakingConstraint(int var1, int val1, int var2, int val2);
    void simplifyModel();
private:
    int nbColors;
    int nbNodes;
    int nbEdges;
    std::vector<std::pair<int, int>> edges;
};

#endif /* GRAPHCOLORING_H */

