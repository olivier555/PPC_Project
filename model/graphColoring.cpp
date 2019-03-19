
#include "graphColoring.h"

#include <fstream>
#include <sstream>
#include <string>
#include <utility>
using namespace std;

graphColoring::graphColoring(string pathFile, int nbColorsVar) {
    nbColors = nbColorsVar;
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

    std::vector<std::vector<int>> constraints(nbNodes);
    for (int c = 0; c < nbEdges; c++) {
        constraints[edges[c].first].push_back(edges[c].second);
        constraints[edges[c].second].push_back(edges[c].first);
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
    }
}

void graphColoring::simplifyModel() {
    std::pair<int, int> edgeChosen = edges[0];
    model::Domain domain1(std::vector<int>(1, 0));
    setDomain(domain1, edgeChosen.first);
    model::Domain domain2(std::vector<int>(1, 1));
    setDomain(domain2, edgeChosen.second);
    int nbModifiedVars = 2;
    int currentVar = 0;
    while (nbModifiedVars < nbColors - 1 && currentVar < getNbVariables()) {
        if (currentVar != edgeChosen.first && currentVar != edgeChosen.second) {
            std::vector<int> domainVect(nbModifiedVars + 1);
            for (int i = 0; i < nbModifiedVars + 1; i++) {
                domainVect[i] = i;
            }
            model::Domain domain(domainVect);
            setDomain(domain, currentVar);
            nbModifiedVars++;
        }
        currentVar++;
    }
}

bool graphColoring::isBreakingConstraint(int var1, int val1, int var2, int val2) {
    return (val1 == val2);
}


