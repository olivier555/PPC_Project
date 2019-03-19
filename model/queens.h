/* 
 * File:   queens.h
 * Author: oliv
 *
 * Created on February 21, 2019, 6:57 AM
 */

#ifndef QUEENS_H
#define QUEENS_H

#include "model.h"

class queens : public model{
public:
    queens(int);
    bool isBreakingConstraint(int var1, int val1, int var2, int val2);
private:

};

#endif /* QUEENS_H */

