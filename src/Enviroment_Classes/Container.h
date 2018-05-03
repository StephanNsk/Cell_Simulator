
#pragma once

#include <vector>
#include "Enviroment.h"
#include "../Substrates_Classes/Substrates_Pull.h"

class Container {
public:

    int max_x = 50;
    int max_y = 50;

    Container();

    Container(int size_x, int size_y);

    virtual ~Container();

    void add_cell(const std::pair<int, int> &cell_coords);

    void die_cell(const std::pair<int, int> &cell_coords);

    void add_substrate(int x, int y, const std::string &name, double count);

    void remove_substrate(int x, int y, const std::string &name, double count);

    void add_ind_substrate(int i, int j, const Substrates_Pull &sp);

    Substrates_Pull get_substrates(int x, int y) const;

    std::vector<std::vector<Enviroment> > get_env();

    bool move_cell(const std::pair<int, int> &prev_coords, const std::pair<int, int> &diff);

    std::vector<std::pair<double, double> > get_counts_substrates_of_nearest_parts(double x, double y) const;
};





