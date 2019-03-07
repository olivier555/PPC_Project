/* 
 * File:   queens.cpp
 * Author: oliv
 * 
 * Created on February 21, 2019, 6:58 AM
 */

#include "queens.h"
#include "model.h"

queens::queens(int nbLines) {
    setNbVariables(nbLines);
    std::vector<int> domain;
    for (int i=0; i<nbLines; i++) {
        domain.push_back(i);
    }
    std::vector<Domain> domains;
    for (int var=0; var<nbLines; var++) {
        Domain d(domain);
        domains.push_back(d);
    }
    setDomains(domains);
    std::vector<std::vector<Constraint>> constraints;
    for (int var1=0; var1<nbLines; var1++) {
        std::vector<Constraint> constraintVar;
        for (int var2=0; var2<nbLines; var2++) {
            if (var2 != var1) {
                std::map<int, std::vector<int>> constraint;
                for (int d1=0; d1 < nbLines; d1++) {
                    std::vector<int> possibleValues;
                    for (int d2=0; d2 < nbLines; d2++) {
                        if (d1 != d2 && abs(d2 - d1) != var2 - var1) {
                            possibleValues.push_back(d2);
                        }
                    }
                    constraint.insert(std::make_pair(d1, possibleValues));
                }
                Constraint c(var1, var2, constraint);
                constraintVar.push_back(c);
            }
        }
        constraints.push_back(constraintVar);
    }
    addConstraints(constraints);
}
