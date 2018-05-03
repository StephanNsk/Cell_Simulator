#pragma once

#include "../Enviroment_Classes/Container.h"

class Sample_Cell;

class Death_Strategy {
public:
    Death_Strategy() = default;

    virtual bool death(Sample_Cell &cell, Container &enviroment) = 0;

    virtual ~Death_Strategy() = default;
};


