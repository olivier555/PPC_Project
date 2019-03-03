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
        std::vector<std::pair<int, int>> constraint;
        int nbValues;
        Constraint() {};
        Constraint(std::vector<std::pair<int, int>> c) : constraint(c), nbValues(c.size()) {}
    };
    //model();
    //model(const model& orig);
    //virtual ~model();
    void setNbVariables(int nbVar) {nbVariables = nbVar;};
    void setDomain(int var_idx, Domain domain) {domains.insert(std::make_pair(var_idx, domain));};
    void addConstraint(std::pair<int, int> variables, model::Constraint constraint) {
        constraints.insert(std::make_pair(variables, constraint));
    };
    int getNbVariables() {return nbVariables;};
    std::map<int, model::Domain> getDomains() {return domains;};
    model::Domain getDomain(int var_idx) {return domains[var_idx];};
    std::map<std::pair<int, int>, model::Constraint> getConstraints() {return constraints;};
    
    void removeValueFromDomain(int var, int v) {
        domains[var].domain.erase(std::remove(domains[var].domain.begin(), domains[var].domain.end(), v), domains[var].domain.end());
    }
private:
    int nbVariables;
    std::map<int, Domain> domains;
    std::map<std::pair<int, int>, Constraint> constraints;
};

#endif /* MODEL_H */

