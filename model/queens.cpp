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
    Domain d(domain);
    for (int var=0; var<nbLines; var++) {
        setDomain(var, d);
    }
    for (int var1=0; var1<nbLines-1; var1++) {
        for (int var2=var1+1; var2<nbLines; var2++) {
            std::pair<int, int> variables = std::make_pair(var1, var2);
            std::vector<std::pair<int, int>> constraint;
            for (int d1=0; d1 < nbLines; d1++) {
                for (int d2=0; d2 < nbLines; d2++) {
                    if (d1 != d2 && abs(d2 - d1) != var2 - var1) {
                        constraint.push_back(std::make_pair(d1, d2));
                    }
                }
            }
            Constraint c(constraint);
            addConstraint(variables, c);
        }
    }
}
