#pragma once

#include "Cell.h"
#include "../Enviroment_Classes/Enviroment.h"
#include "../Gene_Networks_Classes/Segmentation_Gene_Network.h"
#include "../Enviroment_Classes/Container.h"
#include "../Gene_Networks_Classes/Trigger_Gene_Network.h"
#include "Eat_Strategy.h"
#include "Move_Strategy.h"
#include "Death_Strategy.h"
#include "Secretion_Strategy.h"

class Eat_Strategy;

class Sample_Cell : public Cell {
public:
    Sample_Cell() = default;

    Sample_Cell(int x, int y, double volume, Substrates_Pull &sp, int id);

    Sample_Cell(int x, int y, double volume, int id);

    double secr_thr1 = 0.5;
    double secr_thr2 = 0.5;
    double segmentation_quantille = 1.8;
    double x_coord;
    double y_coord;
    int type_of_move;
    Substrates_Pull substrates_pull;
    Eat_Strategy *eat_strategy;
    Move_Strategy *move_strategy;
    Death_Strategy *death_strategy;
    Secretion_Strategy *secretion_strategy;
    double vol;

    Trigger_Gene_Network trigger_gene_network;

    void eat(Container &enviroment) override;

    void secretion(Container &enviroment) override;

    void move(Container &enviroment) override;

    bool death(Container &enviroment) override;

    void recalculate_substr(double t) override;


    ~Sample_Cell() override;
    //  std::vector<double> death(Enviroment enviroment) override ;

    std::vector<Sample_Cell> segmentation();

};



