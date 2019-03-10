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
    struct Constraint {
        int firstVariable;
        int secondVariable;
        std::vector<std::vector<bool>> constraintVect;
        Constraint() {};
        Constraint(int var1, int var2, std::vector<std::vector<bool>> c) : 
                firstVariable(var1), secondVariable(var2), constraintVect(c) {}
    };
    void setNbVariables(int nbVar) {
        nbVariables = nbVar;
    };
    void setDomains(std::vector<Domain> d) {domains = d;};
    void addConstraints(std::vector<std::vector<Constraint>> c) {constraints = c;};
    int getNbVariables() {return nbVariables;};
    std::vector<model::Domain> getDomains() {return domains;};
    model::Domain getDomain(int varIdx) {return domains[varIdx];};
    std::vector<std::vector<model::Constraint>> getConstraints() {return constraints;};
    std::vector<model::Constraint> getConstraint(int varIdx) {return constraints[varIdx];};
    
    void removeValueFromDomain(int var, int v) {
        domains[var].domain.erase(std::remove(domains[var].domain.begin(), domains[var].domain.end(), v), domains[var].domain.end());
    }
    void swapValues(int variable, int idx1, int idx2) {
        std::iter_swap(domains[variable].currentDomain.begin() + idx1, domains[variable].currentDomain.begin() + idx2);
    }
    void randomize() {
        for (int i = 0; i < int(domains.size()); i++) {
            std::shuffle(std::begin(domains[i].currentDomain), std::end(domains[i].currentDomain), rng);
        }
    }
private:
    int nbVariables;
    std::vector<Domain> domains;
    std::vector<std::vector<Constraint>> constraints;
};

#endif /* MODEL_H */

