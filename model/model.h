/* 
 * File:   model.h
 * Author: oliv
 *
 * Created on February 12, 2019, 9:58 AM
 */

#ifndef MODEL_H
#define MODEL_H

#include <algorithm>
#include <random>
#include <utility>
#include <vector>
#include <map>

using namespace std;

auto rng = std::default_random_engine {};

class model {
public:
    struct Domain {
        std::vector<int> domain;
        int nbValue;
        std::vector<int> currentDomain;
        Domain() {};
        Domain(std::vector<int> d) : domain(d), nbValue(d.size()), currentDomain(d) {}
    };
    void setNbVariables(int nbVar) {
        nbVariables = nbVar;
    };
    void setDomain(Domain d, int var) {domains[var] = d;};
    void setDomains(std::vector<Domain> d) {domains = d;};
    void addConstraints(std::vector<std::vector<int>> c) {constraints = c;};
    int getNbVariables() {return nbVariables;};
    std::vector<model::Domain> getDomains() {return domains;};
    model::Domain getDomain(int varIdx) {return domains[varIdx];};
    std::vector<std::vector<int>> getConstraints() {return constraints;};
    std::vector<int> getConstraint(int varIdx) {return constraints[varIdx];};
    
    void removeValueFromDomain(int var, int v) {
        domains[var].domain.erase(std::remove(domains[var].domain.begin(), domains[var].domain.end(), v), domains[var].domain.end());
        domains[var].currentDomain.erase(std::remove(domains[var].currentDomain.begin(), domains[var].currentDomain.end(), v), domains[var].currentDomain.end());
        domains[var].nbValue--;
    }
    void swapValues(int variable, int idx1, int idx2) {
        std::iter_swap(domains[variable].currentDomain.begin() + idx1, domains[variable].currentDomain.begin() + idx2);
    }
    void randomize() {
        for (int i = 0; i < int(domains.size()); i++) {
            std::shuffle(std::begin(domains[i].currentDomain), std::end(domains[i].currentDomain), rng);
        }
    }
    virtual bool isBreakingConstraint(int var1, int val1, int var2, int val2) = 0;
private:
    int nbVariables;
    std::vector<Domain> domains;
    std::vector<std::vector<int>> constraints;
};

#endif /* MODEL_H */

