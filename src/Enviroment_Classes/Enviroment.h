#pragma once

#include <vector>
#include "../Substrates_Classes/Substrates_Pull.h"

class Enviroment {
public:
    std::vector<std::pair<int, int> > Cells;

    Enviroment();

    Substrates_Pull Concentration_info;

    void die_cell(std::pair<int, int> cell_coords);

    //void move_cell(std::pair<int,int> cell_coords,std::pair<int,int> next_coords);
    void add_cell(std::pair<int, int> cell_coords);

    //bool check(int id);
    void add_substrate(const std::string &name, double count);

    void remove_substrate(const std::string &name, double count);

    Substrates_Pull get_substrates();

    size_t cells_count();

    virtual ~Enviroment();
};
