#pragma once

#include "../Enviroment_Classes/Container.h"

class Sample_Cell;

class Secretion_Strategy {
public:
    Secretion_Strategy() = default;

    virtual void secretion(Sample_Cell &cell, Container &enviroment) = 0;

    virtual ~Secretion_Strategy() = default;
};


