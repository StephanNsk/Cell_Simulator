#pragma once

#include "Cell.h"
#include "../Enviroment_Classes/Container.h"
#include "Sample_Cell.h"

class Cell_Container {
public:
    int max_id;
    std::vector<Sample_Cell> container;
    void remove_cell(int id);
    void add_cell(Sample_Cell& cell,Container& enviroment);
    void iteration_death(Container& enviroment);
    void iteration_move(Container& enviroment);
    void iteration_recalculate_substr(double t);
    void iteration_segmentation(Container& enviroment);
    void iteration_secretion(Container& enviroment);
    void iteration_eat(Container& enviroment);
    std::string get_info(double time) const ;
};


