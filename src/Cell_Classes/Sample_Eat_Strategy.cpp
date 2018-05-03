#include "Sample_Eat_Strategy.h"
#include "string"
#include "Sample_Cell.h"
#include <vector>

void Sample_Eat_Strategy::eat(Sample_Cell &cell, Container &enviroment) {
    Substrates_Pull env_substr = enviroment.get_substrates(cell.x_coord, cell.y_coord);
    Substrates_Pull cell_substr = cell.substrates_pull;
    double vol = cell.vol;
    std::vector<std::string> n = cell.substrates_pull.names;
    for (int i = 0; i < n.size(); ++i) {
        double c = cell_substr.get_conc(cell_substr.dict_name_substr[n[i]]) / vol;
        if (c < thr[i]) {
            if (env_substr.get_conc(cell_substr.dict_name_substr[n[i]]) > eat_vel) {
                enviroment.remove_substrate(cell.x_coord, cell.y_coord, n[i], std::min(eat_vel, (thr[i] - c) * vol));
                cell_substr.add_substrate(n[i], std::min(eat_vel, (thr[i] - c) * vol));
            }
        }
    }
    cell.substrates_pull = cell_substr;
}

