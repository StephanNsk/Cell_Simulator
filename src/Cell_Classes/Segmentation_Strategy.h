#pragma once

#include "Cell.h"

class Segmentation_Strategy {
public:
    virtual ~Segmentation_Strategy() = 0;
    virtual void use ( Cell* c) = 0;
};

