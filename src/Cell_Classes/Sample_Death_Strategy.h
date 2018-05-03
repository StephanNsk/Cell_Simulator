#pragma once

#include "Death_Strategy.h"

class Sample_Death_Strategy : public Death_Strategy {
public:
    double conc_thr1 = 0.08;
    double conc_thr2 = 0.08;
    double death_quantille = 2.0;

    bool death(Sample_Cell &cell, Container &enviroment) override;
};



