#pragma once

#include "Eat_Strategy.h"


class Sample_Eat_Strategy : public Eat_Strategy {
public:
    std::vector<double> thr = {0.5, 0.5};
    double eat_vel = 20.;

    void eat(Sample_Cell &cell, Container &container) override;
};



