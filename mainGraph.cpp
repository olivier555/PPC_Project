
#include <cstdlib>
#include <ostream>
#include <iostream>
#include <chrono>
#include "model/graphColoring.h"
#include "model/graphColoring.cpp"
#include "solver/arcConsistancer.h"
#include "solver/arcConsistancer.cpp"
#include "solver/solver.h"
#include "solver/solver.cpp"
using namespace std;

int main(int argc, char** argv) {

    cout << "Model generation ..." << endl;
    
    auto t3 = std::chrono::high_resolution_clock::now();
    graphColoring g(argv[1], std::atoi(argv[2]));
    auto t4 = std::chrono::high_resolution_clock::now();
    cout << "Number of variables: " << g.getNbVariables() << endl;
    std::cout << "Generation took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t4-t3).count()
              << " milliseconds\n";

    g.simplifyModel();
    arcConsistancer ac;
    ac.initArcConsistance(g);
    ac.finishArcConsistance(g);

    //g.randomize();
    
    cout << "Start solving ..." << endl;
    auto t1 = std::chrono::high_resolution_clock::now();
    solver solv(g, false);
    bool isImpossible = solv.branchAndBound();
    auto t2 = std::chrono::high_resolution_clock::now();
    if (isImpossible) {
        cout << "Infeasible model" << endl;
    } else {
        std::vector<solver::Node> nodes = solv.getNodes();
        cout << "Solution:" << endl;
        cout << "variable - value" << endl;
        for (int i = 0; i < int(nodes.size()); i++) {
            cout << nodes[i].variable << " - " << g.getDomain(nodes[i].variable).currentDomain[nodes[i].idxChosen] << endl;
        }
    }
    std::cout << "Solving took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()
              << " milliseconds\n";
    return 0;
}

