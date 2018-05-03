
#pragma once

#include "../Enviroment_Classes/Container.h"

class Sample_Cell;

class Move_Strategy {
public:
    Move_Strategy() = default;

    virtual void move(Sample_Cell &cell, Container &container) = 0;

    virtual ~Move_Strategy() = default;
};


