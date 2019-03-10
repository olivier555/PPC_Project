
#include "solver.h"

#include <algorithm>
#include <random>
#include <utility>
#include <vector>
#include <map>
#include <set>
#include <chrono>

using namespace std;

auto rngSolver = std::default_random_engine {};

bool solver::branchAndBound() {
    idxCurrent = 0;
    std::vector<int> initialIdxMax = getInitialIdxMax();
    bool notSolved = true;
    bool isImpossible = false;
    nodes.push_back(solver::Node(variablesOrdered[idxCurrent], 0, initialIdxMax));
    unsigned long int nbNodesConsidered = 0;
    while (notSolved) {
        nbNodesConsidered++;
        if(nbNodesConsidered % 1000 ==0) {
            cout << "nbNodes: " << nbNodesConsidered << " variable: " << nodes.back().variable << endl;
        }
        notSolved = makeStep(isImpossible);
    }
    return isImpossible;
}

std::vector<int> solver::getOrderVariables(bool isRandomOrder) {
    std::vector<int> result;
    for (int i = 0; i < mod.getNbVariables(); i++) {
        result.push_back(i);
    }
    if (isRandomOrder) {
        std::shuffle(std::begin(result), std::end(result), rngSolver);
    }
    return result;
}

std::vector<int> solver::getInitialIdxMax() {
    std::vector<int> result;
    std::vector<model::Domain> domains = mod.getDomains();
    for (std::vector<model::Domain>::const_iterator it = domains.begin(); it != domains.end(); it++) {
        result.push_back(it->nbValue);
    }
    return result;
}

bool solver::makeStep(bool& isImpossible) {
    bool notSolved = true;
    std::vector<int> newIdxMax(nodes.back().idxMax);
    bool isPossible = forwardCheck(nodes.back().variable,
            mod.getDomain(nodes.back().variable).currentDomain[nodes.back().idxChosen],
            newIdxMax);
    if (isPossible) {
        if (idxCurrent == mod.getNbVariables() - 1) {
            std::cout << "Solution found" << std::endl;
            notSolved = false;
        } else {
            newIdxMax[variablesOrdered[idxCurrent]] = - 1;
            idxCurrent++;
            nodes.push_back(solver::Node(variablesOrdered[idxCurrent], 0, newIdxMax));
        }
    } else {
        if (nodes.back().idxChosen < nodes.back().idxMax[nodes.back().variable] - 1) {
            nodes.back().idxChosen++;
        } else if (idxCurrent == 0) {
            isImpossible = true;
            notSolved = false;
            std::cout << "impossible" << std::endl;
        } else {
            bool variableUsable = false;
            while (not variableUsable) {
                idxCurrent--;
                nodes.pop_back();
                if (nodes.back().idxChosen < nodes.back().idxMax[nodes.back().variable] - 1) {
                    nodes.back().idxChosen++;
                    variableUsable = true;
                } else if (idxCurrent == 0) {
                    isImpossible = true;
                    notSolved = false;
                    std::cout << "impossible" << std::endl;
                    break;
                }
            }
        }
    }
    return notSolved;
}

bool solver::forwardCheck(int variable, int value, std::vector<int>& newIdxMax) {
    std::vector<model::Constraint> constraints = mod.getConstraint(variable);
    for (std::vector<model::Constraint>::const_iterator it = constraints.begin();
            it != constraints.end();
            it++) {
        if (newIdxMax[it->secondVariable] != - 1) {
            model::Domain domain = mod.getDomain(it->secondVariable);
            int nbValueRemoved = 0;
            for (int j = 0; j < newIdxMax[it->secondVariable]; j++) {
                if (not it->constraintVect[value][domain.currentDomain[j]]) {
                    nbValueRemoved++;
                    mod.swapValues(it->secondVariable, j, newIdxMax[it->secondVariable] - nbValueRemoved);
                }
            }
            newIdxMax[it->secondVariable] = newIdxMax[it->secondVariable] - nbValueRemoved;
            if (newIdxMax[it->secondVariable] == 0) {
                return false;
            }
        }
    }
    return true;
}
