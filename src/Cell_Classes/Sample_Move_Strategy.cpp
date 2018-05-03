

#include "Sample_Move_Strategy.h"
#include "Sample_Cell.h"
#include "random"

void Sample_Move_Strategy::move(Sample_Cell &cell, Container &enviroment) {
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(-1, 1);
    std::pair<int, int> dxdy = {distribution(generator), distribution(generator)};
    if (enviroment.move_cell(std::pair<int, int>{cell.x_coord, cell.y_coord}, dxdy)) {
        cell.x_coord += dxdy.first;
        cell.y_coord += dxdy.second;
    }

}