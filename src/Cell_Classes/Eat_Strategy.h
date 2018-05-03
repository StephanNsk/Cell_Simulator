

#pragma once


#include "../Enviroment_Classes/Container.h"


class Sample_Cell;
class Eat_Strategy{
public:
    Eat_Strategy() = default;
    virtual void eat(Sample_Cell & cell, Container& container) = 0;
    virtual ~Eat_Strategy() = default;
};


