
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
    std::vector<std::vector<int>> constraints(nbLines, vector<int>(nbLines - 1));
    for (int var1=0; var1<nbLines - 1; var1++) {
        for (int var2=var1 + 1; var2<nbLines; var2++) {
            constraints[var1][var2 - 1] = var2;
            constraints[var2][var1] = var1;
        }
    }
    addConstraints(constraints);
}

bool queens::isBreakingConstraint(int var1, int val1, int var2, int val2) {
    if (val1 == val2) {
        return true;
    } else if (abs(var1 - var2) == abs(val1 - val2)) {
        return true;
    }
    return false;
}
