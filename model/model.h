/* 
 * File:   model.h
 * Author: oliv
 *
 * Created on February 12, 2019, 9:58 AM
 */

#ifndef MODEL_H
#define MODEL_H

#include <algorithm>
#include <utility>
#include <vector>
#include <map>

using namespace std;

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
        std::map<int, std::vector<int>> constraintMap;
        Constraint() {};
        Constraint(int var1, int var2, std::map<int, std::vector<int>> c) : 
                firstVariable(var1), secondVariable(var2), constraintMap(c) {}
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
private:
    int nbVariables;
    std::vector<Domain> domains;
    std::vector<std::vector<Constraint>> constraints;
};

#endif /* MODEL_H */

