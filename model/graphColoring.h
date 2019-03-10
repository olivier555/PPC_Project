

#ifndef GRAPHCOLORING_H
#define GRAPHCOLORING_H

#include "model.h"

#include <fstream>
#include <vector>
#include <utility>
using namespace std;


class graphColoring  : public model {
public:
    graphColoring(string pathFile, int nbColors);
    void readFile(string pathFile);
private:
    int nbNodes;
    int nbEdges;
    std::vector<std::pair<int, int>> edges;
};

#endif /* GRAPHCOLORING_H */

