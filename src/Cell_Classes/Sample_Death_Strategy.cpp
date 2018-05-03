

#include "Sample_Death_Strategy.h"
#include "Sample_Cell.h"
#include "random"

bool Sample_Death_Strategy::death(Sample_Cell &cell, Container &enviroment) {
    double c1 = cell.substrates_pull.get_conc(0) / cell.vol;
    double c2 = cell.substrates_pull.get_conc(1) / cell.vol;
    if (c1 < conc_thr1 || c2 < conc_thr2) {
        enviroment.die_cell(std::pair<int, int>{cell.x_coord, cell.y_coord});
        return true;
    }
    std::normal_distribution<> normal_distribution(0, 1);
    std::random_device random_device;
    std::mt19937 generator(random_device());
    if (abs(normal_distribution(generator)) > death_quantille) {
        enviroment.die_cell(std::pair<int, int>{cell.x_coord, cell.y_coord});
        return true;
    }
    return false;
}
