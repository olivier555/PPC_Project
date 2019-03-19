
/* 
 * File:   main.cpp
 * Author: oliv
 *
 * Created on February 9, 2019, 11:10 AM
 */

#include <cstdlib>
#include <ostream>
#include <iostream>
#include <chrono>
#include "model/queens.h"
#include "model/queens.cpp"
#include "solver/arcConsistancer.h"
#include "solver/arcConsistancer.cpp"
#include "solver/solver.h"
#include "solver/solver.cpp"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    cout << "Model generation ..." << endl;
    
    auto t3 = std::chrono::high_resolution_clock::now();
    queens q(std::atoi(argv[1]));
    
    auto t4 = std::chrono::high_resolution_clock::now();
    cout << "Number of variables: " << q.getNbVariables() << endl;
    std::cout << "Generation took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t4-t3).count()
              << " milliseconds\n";

    q.randomize();

    cout << "Start solving ..." << endl;
    auto t1 = std::chrono::high_resolution_clock::now();
    solver solv(q, false);
    bool isImpossible = solv.branchAndBound();
    auto t2 = std::chrono::high_resolution_clock::now();
    if (isImpossible) {
        cout << "Infeasible model" << endl;
    } else {
        std::vector<solver::Node> nodes = solv.getNodes();
        cout << "Solution:" << endl;
        cout << "variable - value" << endl;
        for (int i = 0; i < int(nodes.size()); i++) {
            cout << nodes[i].variable << " - " << q.getDomain(nodes[i].variable).currentDomain[nodes[i].idxChosen] << endl;
        }
    }
    std::cout << "Solving took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()
              << " milliseconds\n";
    return 0;
}

