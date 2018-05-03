

#include "Sample_Secretion_Strategy.h"
#include "Sample_Cell.h"

void Sample_Secretion_Strategy::secretion(Sample_Cell &cell, Container &enviroment) {
    for (int i = 0; i < cell.substrates_pull.names.size(); ++i) {
        double c = cell.substrates_pull.get_conc(cell.substrates_pull.dict_name_substr[cell.substrates_pull.names[i]]) /
                   cell.vol;
        if (c > thr[i]) {
            cell.substrates_pull.remove_substrate(cell.substrates_pull.names[i], (c - thr[i]) * cell.vol);
            enviroment.add_substrate(cell.x_coord, cell.y_coord, cell.substrates_pull.names[i],
                                     (c - thr[i]) * cell.vol);
        }
    }
}
