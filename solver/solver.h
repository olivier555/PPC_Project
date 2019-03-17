
#ifndef SOLVER_H
#define SOLVER_H

#include <algorithm>
#include <utility>
#include <vector>
#include <map>
#include <set>

#include "../model/model.h"

class solver {
public:
    struct Node {
        int variable;
        int idxChosen;
        std::vector<int> idxMax;
        Node(int var, int idx, std::vector<int>  idxMaxArg) :
                variable(var), idxChosen(idx), idxMax(idxMaxArg) {}
    };
    solver(model& modToSolve, bool isRandomOrder) : mod(modToSolve) {
        std::vector<Node> nodes;
        variablesOrdered = getOrderVariables(isRandomOrder);
    };
    //virtual ~solver();
    bool branchAndBound();
    bool makeStep(bool& isImpossible);
    std::vector<int> getInitialIdxMax();
    std::vector<int> getOrderVariables(bool isRandomOrder);
    bool forwardCheck(int variable, int value, std::vector<int>& newIdxMax, int& nextVariable);
    std::vector<solver::Node> getNodes() {return nodes;};
private:
    model& mod;
    std::vector<Node> nodes;
    std::vector<int> variablesOrdered;
    int idxCurrent;
    int nbNodes;
};

#endif /* SOLVER_H */

