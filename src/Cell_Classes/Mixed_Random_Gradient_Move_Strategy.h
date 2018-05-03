#pragma once

#include "Move_Strategy.h"
class Sample_Cell;

class Mixed_Random_Gradient_Move_Strategy: public Move_Strategy {
public:
   void move(Sample_Cell &cell, Container &container) override ;
};


