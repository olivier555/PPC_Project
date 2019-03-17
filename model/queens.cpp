
#include <algorithm>
#include <random>
#include <utility>
#include <vector>
#include <map>

using namespace std;

#include "queens.h"
#include "model.h"

queens::queens(int nbLines) {
    setNbVariables(nbLines);
    std::vector<int> domain(nbLines);
    std::iota(domain.begin(), domain.end(), 0);
    std::vector<Domain> domains;
    for (int var=0; var<nbLines; var++) {
        Domain d(domain);
        domains.push_back(d);
    }
    setDomains(domains);
    std::vector<std::vector<std::vector<bool>>> constraintDiff(nbLines - 1, vector<vector<bool>>(nbLines, vector<bool>(nbLines, true)));
    for (int diff = 1; diff < nbLines; diff++) {
        for (int d=0; d < nbLines; d++) {
            constraintDiff[diff - 1][d][d] = false;
            if (d - diff >= 0) {
                constraintDiff[diff - 1][d][d - diff] = false;
            }
            if (d + diff <= nbLines - 1) {
                constraintDiff[diff - 1][d][d + diff] = false;
            }
        }
    }
    std::vector<std::vector<Constraint>> constraints(nbLines, vector<Constraint>(nbLines - 1));
    for (int var1=0; var1<nbLines - 1; var1++) {
        for (int var2=var1 + 1; var2<nbLines; var2++) {
            constraints[var1][var2 - 1] = Constraint(var1, var2, constraintDiff[abs(var2 - var1) - 1]);
            constraints[var2][var1] = Constraint(var2, var1, constraintDiff[abs(var1 - var2) - 1]);
        }
    }
    addConstraints(constraints);
}
