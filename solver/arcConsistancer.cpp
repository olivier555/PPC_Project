

#include "arcConsistancer.h"
#include "../model/model.h"

#include <algorithm>
#include <utility>
#include <vector>
#include <map>
#include <set>

arcConsistancer::arcConsistancer() {
}

arcConsistancer::arcConsistancer(const arcConsistancer& orig) {
}

arcConsistancer::~arcConsistancer() {
}

void arcConsistancer::makeArcConsistance(model& mod) {
    initArcConsistance(mod);
    finishArcConsistance(mod);
}


void arcConsistancer::initArcConsistance(model& mod) {
    std::set<std::pair<int, int>> Q;
    std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> S;
    std::map<std::pair<std::pair<int, int>, int>, int> count;
    std::vector<std::vector<model::Constraint>> constraints = mod.getConstraints();
    std::map<std::pair<int, int>, model::Constraint>::iterator it;
    for (int varX = 0; varX < int(constraints.size()); varX++) {
        for (int i = 0; i < int(constraints[varX].size()); i++) {
            int varY = constraints[varX][i].secondVariable;
            std::vector<int> domainX = mod.getDomain(varX).domain;
            std::vector<int> domainY = mod.getDomain(varY).domain;
            for (std::vector<int>::iterator itDX = domainX.begin(); itDX != domainX.end(); itDX++) {
                int total = 0;
                std::pair<int, int> pairX = std::make_pair(varX, *itDX);
                for (std::vector<int>::const_iterator itDY = domainY.begin(); itDY != domainY.end(); itDY++) {
                    if (constraints[varX][i].constraintVect[*itDX][*itDY]) {
                        total++;
                        std::pair<int, int> pairY = std::make_pair(varY, *itDY);
                        if (S.count(pairY) != 0) {
                            S[pairY].push_back(pairX);
                        } else {
                            std::vector<std::pair<int, int>> vec;
                            vec.push_back(pairX);
                            S.insert(std::make_pair(pairY, vec));
                        }
                    }
                }
                
                std::pair<std::pair<int, int>, int> idxCount = std::make_pair(std::make_pair(varX, varY), *itDX);
                std::pair<std::pair<std::pair<int, int>, int>, int> pairCount = std::make_pair(idxCount, total);
                count.insert(pairCount);
                if(total == 0) {
                    mod.removeValueFromDomain(varX, *itDX);
                    Q.insert(pairX);
                }
            }
        }
    }
    setQ(Q);
    setS(S);
    setCount(count);
}

void arcConsistancer::finishArcConsistance(model& mod) {
    //std::set<std::pair<int, int>> Q = getQ();
    //std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> S = getS();
    //std::map<std::pair<std::pair<int, int>, int>, int> count = getCount();
    while (Q.size() != 0) {
        std::pair<int, int> pairQ = *Q.begin();
        if (S.count(pairQ) != 0) {
            for (std::vector<std::pair<int, int>>::iterator it = S[pairQ].begin(); it != S[pairQ].end(); it++) {
                std::pair<std::pair<int, int>, int> pairCount = std::make_pair(std::make_pair(it->first, pairQ.first), it->second);
                count[pairCount]--;
                if (count[pairCount] == 0 && std::find(mod.getDomain(it->first).domain.begin(),
                        mod.getDomain(it->first).domain.end(), it->second) != mod.getDomain(it->first).domain.end()) {
                    mod.removeValueFromDomain(it->first, it->second);
                    Q.insert(*it);
                }
            }
        }
        Q.erase(Q.begin());
    }
}
