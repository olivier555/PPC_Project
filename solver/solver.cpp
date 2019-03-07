
#include "solver.h"

#include <algorithm>
#include <utility>
#include <vector>
#include <map>
#include <set>

using namespace std;

bool solver::branchAndBound() {
    int currentVariable = 0;
    std::vector<int> initialIdxMax = getInitialIdxMax();
    bool solved = false;
    bool impossible = false;
    nodes.push_back(solver::Node(currentVariable, 0, initialIdxMax));
    unsigned long int nbNodesConsidered = 0;
    while (not solved or not impossible) {
        nbNodesConsidered++;
        if(nbNodesConsidered % 1000 ==0) {
            cout << "nbNodes: " << nbNodesConsidered << " variable: " << nodes.back().variable << endl;
        }
        std::vector<int> newIdxMax(nodes.back().idxMax);
        /*cout << "variable:" << nodes.back().variable;
        cout << " value:" << mod.getDomain(nodes.back().variable).currentDomain[nodes.back().idxChosen];
        cout << " maxIdx:" << nodes.back().idxMax[nodes.back().variable] << endl;
        for (int i = 0; i < int(nodes.back().idxMax.size()); i++) {
            cout << nodes.back().idxMax[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < int(mod.getDomain(nodes.back().variable).currentDomain.size()); i++) {
            cout << mod.getDomain(nodes.back().variable).currentDomain[i] << " ";
        }
        cout << endl;*/
        bool isPossible = forwardCheck(nodes.back().variable,
                mod.getDomain(nodes.back().variable).currentDomain[nodes.back().idxChosen],
                newIdxMax);
        /*cout << "ispossible: " << isPossible << endl;
        for (int i = 0; i < int(newIdxMax.size()); i++) {
            cout << newIdxMax[i] << " ";
        }
        cout << endl;*/
        if (isPossible) {
            if (currentVariable == mod.getNbVariables() - 1) {
                std::cout << "Solution found" << std::endl;
                solved = true;
                return true;
            } else {
                newIdxMax[currentVariable] = - 1;
                currentVariable++;
                nodes.push_back(solver::Node(currentVariable, 0, newIdxMax));
            }
        } else {
            if (nodes.back().idxChosen < nodes.back().idxMax[nodes.back().variable] - 1) {
                nodes.back().idxChosen++;
            } else if (currentVariable == 0) {
                impossible = true;
                std::cout << "impossible" << std::endl;
                return false;
            } else {
                bool variableUsable = false;
                while (not variableUsable) {
                    currentVariable--;
                    nodes.pop_back();
                    if (nodes.back().idxChosen < nodes.back().idxMax[nodes.back().variable] - 1) {
                        nodes.back().idxChosen++;
                        variableUsable = true;
                    } else if (currentVariable == 0) {
                        impossible = false;
                        std::cout << "impossible" << std::endl;
                    }
                }
            }
        }
    }
    return false;
}

std::vector<int> solver::getInitialIdxMax() {
    std::vector<int> result;
    std::vector<model::Domain> domains = mod.getDomains();
    for (std::vector<model::Domain>::const_iterator it = domains.begin(); it != domains.end(); it++) {
        result.push_back(it->nbValue);
    }
    return result;
}

bool solver::forwardCheck(int variable, int value, std::vector<int>& newIdxMax) {
    std::vector<model::Constraint> constraints = mod.getConstraint(variable);
    for (int i = 0; i < int(constraints.size()); i++) {
        if (newIdxMax[constraints[i].secondVariable] != - 1) {
            model::Domain domain = mod.getDomain(constraints[i].secondVariable);
            int nbValueRemoved = 0;
            for (int j = 0; j < newIdxMax[constraints[i].secondVariable]; j++) {
                if (std::find(constraints[i].constraintMap[value].begin(),
                              constraints[i].constraintMap[value].end(),
                              domain.currentDomain[j]) == constraints[i].constraintMap[value].end()) {
                    nbValueRemoved++;
                    mod.swapValues(constraints[i].secondVariable, j, newIdxMax[constraints[i].secondVariable] - nbValueRemoved);
                }
            }
            newIdxMax[constraints[i].secondVariable] = newIdxMax[constraints[i].secondVariable] - nbValueRemoved;
            if (newIdxMax[constraints[i].secondVariable] == 0) {
                return false;
            }
        }
    }
    return true;
}
