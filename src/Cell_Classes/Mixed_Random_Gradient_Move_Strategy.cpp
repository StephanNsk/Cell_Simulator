

#include "Mixed_Random_Gradient_Move_Strategy.h"
#include "random"
#include "Gradient_Move_Strategy.h"
#include "Sample_Move_Strategy.h"
#include "Sample_Cell.h"


void Mixed_Random_Gradient_Move_Strategy::move(Sample_Cell &cell, Container &container) {
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(-1, 1);
    int event = distribution(generator);
    if (event == 0) {
        Sample_Move_Strategy move_strategy;
        move_strategy.move(cell, container);
    } else {
        Gradient_Move_Strategy move_strategy;
        move_strategy.move(cell, container);
    }
}
