#pragma once

#include "Move_Strategy.h"

class Sample_Move_Strategy : public Move_Strategy {
public:
    void move(Sample_Cell &cell, Container &enviroment) override;

};



