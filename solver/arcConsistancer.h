#ifndef ARCCONSISTANCER_H
#define ARCCONSISTANCER_H

#include "../model/model.h"


#include <utility>
#include <vector>
#include <map>
#include <set>

class arcConsistancer {
public:
    arcConsistancer();
    arcConsistancer(const arcConsistancer& orig);
    void makeArcConsistance(model& model);
    void initArcConsistance(model& model);
    void finishArcConsistance(model& model);
    virtual ~arcConsistancer();
    std::set<std::pair<int, int>> getQ() {return Q;}
    std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> getS() {return S;}
    std::map<std::pair<std::pair<int, int>, int>, int> getCount() {return count;}
    void setQ(std::set<std::pair<int, int>> Qvar) {Q = Qvar;}
    void setS(std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> Svar) {S = Svar;}
    void setCount(std::map<std::pair<std::pair<int, int>, int>, int> Cvar) {count = Cvar;}
private:
    std::set<std::pair<int, int>> Q;
    std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> S;
    std::map<std::pair<std::pair<int, int>, int>, int> count;
};

#endif /* ARCCONSISTANCER_H */

