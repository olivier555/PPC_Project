
#include "graphColoring.h"

#include <fstream>
#include <sstream>
#include <string>
#include <utility>
using namespace std;

graphColoring::graphColoring(string pathFile, int nbColors) {
    readFile(pathFile);
    
    setNbVariables(nbNodes);

    std::vector<int> domain;
    for (int i=0; i<nbColors; i++) {
        domain.push_back(i);
    }
    std::vector<Domain> domains;
    for (int var=0; var<nbNodes; var++) {
        Domain d(domain);
        domains.push_back(d);
    }
    setDomains(domains);

    std::vector<std::vector<Constraint>> constraints;
    for (int var1=0; var1<nbNodes; var1++) {
        std::vector<Constraint> constraintVar;
        constraints.push_back(constraintVar);
    }
    std::vector<std::vector<bool>> constraint;
    for (int d = 0; d < nbColors; d++) {
        std::vector<bool> possibleValues(nbColors, true);
        possibleValues[d] = false;
        constraint.push_back(possibleValues);
    }
    for (int c = 0; c < nbEdges; c++) {
        model::Constraint constraint1 = Constraint(edges[c].first, edges[c].second, constraint);
        model::Constraint constraint2 = Constraint(edges[c].second, edges[c].first, constraint);
        constraints[edges[c].first].push_back(constraint1);
        constraints[edges[c].second].push_back(constraint2);
    }
    addConstraints(constraints);
}

void graphColoring::readFile(string pathFile) {
    ifstream inFile;
    inFile.open(pathFile);
    std::string line;
    while (std::getline(inFile, line))
    {
        std::istringstream iss(line);
        string paramLine;
        if (!(iss >> paramLine)) { break; }
        if (paramLine == "p") {
            string tmp;
            int n, e;
            iss >> tmp >> n >> e;
            nbNodes = n;
            nbEdges = e;
        } else if (paramLine == "e") {
            int n1, n2;
            iss >> n1 >> n2;
            edges.push_back(std::make_pair(int(n1) - 1, int(n2) - 1));
        }

        // process pair (a,b)
    }
}


