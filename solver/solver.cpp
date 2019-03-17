
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
    bool notSolved = true;
    bool isImpossible = false;
    nodes.push_back(solver::Node(variablesOrdered[idxCurrent], 0, initialIdxMax));
    //unsigned long int nbNodesConsidered = 0;
    while (notSolved) {
        //nbNodesConsidered++;
        //cout << "Variable: " << nodes.back().variable << endl;
        //cout << "Value: " << mod.getDomain(nodes.back().variable).currentDomain[nodes.back().idxChosen] << endl;
        if(nbNodes % 1000 ==0) {
            cout << "nbNodes: " << nbNodes << " variable: " << nodes.back().variable << endl;
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
    int nextVariable;
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
            nbNodes++;
            nodes.push_back(solver::Node(nextVariable, 0, newIdxMax));
        }
    } else {
        if (nodes.back().idxChosen < nodes.back().idxMax[nodes.back().variable] - 1) {
            nodes.back().idxChosen++;
        } else if (int(nodes.size()) == 1) {
            isImpossible = true;
            notSolved = false;
            std::cout << "impossible" << std::endl;
        } else {
            bool variableUsable = false;
            while (not variableUsable) {
                //idxCurrent--;
                nodes.pop_back();
                if (nodes.back().idxChosen < nodes.back().idxMax[nodes.back().variable] - 1) {
                    nodes.back().idxChosen++;
                    variableUsable = true;
                } else if (int(nodes.size()) == 0) {
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

bool solver::forwardCheck(int variable, int value, std::vector<int>& newIdxMax, int& nextVariable) {
    std::vector<model::Constraint> constraints = mod.getConstraint(variable);
    int minDomain = mod.getNbVariables();
    for (std::vector<model::Constraint>::const_iterator it = constraints.begin();
            it != constraints.end();
            it++) {
        int secondVariable = it->secondVariable;
        if (newIdxMax[secondVariable] != - 1) {
            //cout << "first and second variable: " << it->firstVariable << " & " << it->secondVariable << endl;
            //std::vector<int> currentDomain = mod.getDomain(secondVariable).currentDomain;
            //cout << "max domain: " << newIdxMax[secondVariable] << endl;
            //for (int j = 0; j < int(currentDomain.size()); j++) {
            //    cout << currentDomain[j] << ' ';
            //}
            //cout << endl;
            for (int j = newIdxMax[secondVariable] - 1; j >= 0; j--) {
                if (not it->constraintVect[value][mod.getDomain(secondVariable).currentDomain[j]]) {
                    //cout << "value removed: " << currentDomain[j] << endl;
                    newIdxMax[secondVariable]--;
                    mod.swapValues(secondVariable, j, newIdxMax[secondVariable]);
                }
            }
            if (newIdxMax[secondVariable] == 0) {
                return false;
            } else if (newIdxMax[secondVariable] < minDomain) {
                nextVariable = secondVariable;
                minDomain = newIdxMax[secondVariable];
            }
        }
    }
    return true;
}
