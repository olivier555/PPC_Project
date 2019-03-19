
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
    nbNodes = 1;
    std::vector<int> initialIdxMax = getInitialIdxMax();
    int initialVar = std::distance(initialIdxMax.begin(), std::min_element(initialIdxMax.begin(), initialIdxMax.end()));
    bool notSolved = true;
    bool isImpossible = false;
    nodes.push_back(solver::Node(initialVar, 0, initialIdxMax));
    while (notSolved) {
        if(nbNodes % 1000 ==0) {
            cout << "Number of nodes: " << nbNodes << endl;
        }
        notSolved = makeStep(isImpossible);
    }
    cout << "Number of visited nodes: " << nbNodes << endl;
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
    int nextVariable = - 1;
    std::vector<int> newIdxMax(nodes.back().idxMax);
    bool isPossible = forwardCheck(nodes.back().variable,
            mod.getDomain(nodes.back().variable).currentDomain[nodes.back().idxChosen],
            newIdxMax, nextVariable);
    if (isPossible) {
        if (int(nodes.size()) == mod.getNbVariables()) {
            std::cout << "Solution found" << std::endl;
            notSolved = false;
        } else {
            newIdxMax[nodes.back().variable] = - 1;
            if (nextVariable == - 1) {
                nextVariable = std::distance(newIdxMax.begin(), std::max_element(newIdxMax.begin(), newIdxMax.end()));
            }
            nbNodes++;
            nodes.push_back(solver::Node(nextVariable, 0, newIdxMax));
        }
    } else {
        if (nodes.back().idxChosen < nodes.back().idxMax[nodes.back().variable] - 1) {
            nodes.back().idxChosen++;
        } else if (int(nodes.size()) == 1) {
            isImpossible = true;
            notSolved = false;
            std::cout << "Impossible" << std::endl;
        } else {
            bool variableUsable = false;
            while (not variableUsable) {
                nodes.pop_back();
                if (int(nodes.size()) == 0) {
                    isImpossible = true;
                    notSolved = false;
                    std::cout << "Impossible" << std::endl;
                    break;
                } else if (nodes.back().idxChosen < nodes.back().idxMax[nodes.back().variable] - 1) {
                    nodes.back().idxChosen++;
                    variableUsable = true;
                }
            }
        }
    }
    return notSolved;
}

bool solver::forwardCheck(int variable, int value, std::vector<int>& newIdxMax, int& nextVariable) {
    std::vector<int> constraints = mod.getConstraint(variable);
    int minDomain = mod.getNbVariables();
    for (std::vector<int>::const_iterator it = constraints.begin();
            it != constraints.end();
            it++) {
        if (newIdxMax[*it] != - 1) {
            for (int j = newIdxMax[*it] - 1; j >= 0; j--) {
                if (mod.isBreakingConstraint(variable, value, *it, mod.getDomain(*it).currentDomain[j])) {
                    newIdxMax[*it]--;
                    mod.swapValues(*it, j, newIdxMax[*it]);
                }
            }
            if (newIdxMax[*it] == 0) {
                return false;
            } else if (newIdxMax[*it] < minDomain) {
                nextVariable = *it;
                minDomain = newIdxMax[*it];
            }
        }
    }
    return true;
}
