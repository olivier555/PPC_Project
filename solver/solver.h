
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
    solver(model& modToSolve) : mod(modToSolve) {
        std::vector<Node> nodes;
    };
    //virtual ~solver();
    bool branchAndBound();
    std::vector<int> getInitialIdxMax();
    bool forwardCheck(int variable, int value, std::vector<int>& newIdxMax);
    std::vector<solver::Node> getNodes() {return nodes;};
private:
    model& mod;
    std::vector<Node> nodes;
};

#endif /* SOLVER_H */

