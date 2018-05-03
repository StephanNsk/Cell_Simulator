#pragma once

#include "../Substrates_Classes/Substrates_Pull.h"
#include "../Gene_Networks_Classes/Euler_Gene_Network.h"
#include "../Gene_Networks_Classes/Gene_Network.h"
#include "../Enviroment_Classes/Container.h"
#include "Move_Strategy.h"
#include "Death_Strategy.h"
#include "Secretion_Strategy.h"
#include <map>
#include "Eat_Strategy.h"
class Cell {
public:
    //Gene_Network *gene_network;
    //Metabolite_Network metabolite_network;
    Substrates_Pull substrates_pull;
    Eat_Strategy *eat_strategy;
    //Move_Strategy *move_strategy;
    //Death_Strategy *death_strategy;
    //Secretion_Strategy *secretion_strategy;
    double x_coord;
    double y_coord;
    double volume;
    int id;
    double prev_time;
    Cell() = default;

    virtual void eat(Container& enviroment) = 0;

    virtual void move(Container& enviroment) = 0;

    virtual bool death(Container& container) = 0;

    //virtual std::vector<Cell> segmentation() = 0;

   //virtual std::vector<double> death(Enviroment enviroment) = 0;

    virtual void secretion(Container& enviroment) = 0;

    virtual void recalculate_substr(double time) = 0;

    virtual ~ Cell() = default;

    //virtual int get_id() = 0;

};

