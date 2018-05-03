#pragma once

#include "Secretion_Strategy.h"
#include "vector"

class Sample_Secretion_Strategy: public Secretion_Strategy {
public:
    std::vector<double > thr = {0.5, 0.5};
    void secretion(Sample_Cell& cell, Container& enviroment) override ;
};
