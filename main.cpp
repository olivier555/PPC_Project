
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

    queens q(std::atoi(argv[1]));
    cout << q.getNbVariables() << endl;
    /*std::map<int, model::Domain> domains = q.getDomains();
    cout << "Domains:" << endl;
    for (int var = 0; var != q.getNbVariables(); var++) {
        model::Domain d = domains[var];
        cout << var << endl;
        for (std::vector<int>::const_iterator it = d.domain.begin(); it != d.domain.end(); it++) {
            cout << *it << ' ';
        }
        cout << endl;
    }
    cout << "Constraints:" << endl;
    std::map<std::pair<int, int>, model::Constraint> constraints = q.getConstraints();
    for (std::map<std::pair<int, int>, model::Constraint>::const_iterator it = constraints.begin(); it != constraints.end(); it++) {
        cout << "Variables: " << it->first.first << ' ' << it->first.second << endl;
        for (std::vector<std::pair<int, int>>::const_iterator it_v = it->second.constraint.begin(); it_v != it->second.constraint.end(); it_v++) {
            cout << "(" << it_v->first << ',' << it_v->second << ") ";
        }
        cout << endl;
    }*/
    arcConsistancer ac;
    ac.initArcConsistance(q);
    /*cout << "Domains:" << endl;
    std::map<int, model::Domain> domainsModif = q.getDomains();
    for (int var = 0; var != q.getNbVariables(); var++) {
        model::Domain d = domainsModif[var];
        cout << var << endl;
        for (std::vector<int>::const_iterator it = d.domain.begin(); it != d.domain.end(); it++) {
            cout << *it << ' ';
        }
        cout << endl;
    }*/
    ac.finishArcConsistance(q);
    /*cout << "Domains:" << endl;
    std::map<int, model::Domain> domainsModifFinal = q.getDomains();
    for (int var = 0; var != q.getNbVariables(); var++) {
        model::Domain d = domainsModifFinal[var];
        cout << var << endl;
        for (std::vector<int>::const_iterator it = d.domain.begin(); it != d.domain.end(); it++) {
            cout << *it << ' ';
        }
        cout << endl;
    }*/
    cout << "Start solving ..." << endl;
    auto t1 = std::chrono::high_resolution_clock::now();
    solver solv(q);
    solv.branchAndBound();
    auto t2 = std::chrono::high_resolution_clock::now();
    std::vector<solver::Node> nodes = solv.getNodes();
    cout << "Solution:" << endl;
    cout << "variable - value" << endl;
    for (int i = 0; i < int(nodes.size()); i++) {
        cout << nodes[i].variable << " - " << q.getDomain(nodes[i].variable).currentDomain[nodes[i].idxChosen] << endl;
    }
    std::cout << "Solving took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()
              << " milliseconds\n";
    return 0;
}

