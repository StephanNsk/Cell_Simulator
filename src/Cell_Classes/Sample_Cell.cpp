#include "Sample_Cell.h"
#include "../Gene_Networks_Classes/Gene_Network.h"
#include "../Substrates_Classes/Substrates_Pull.h"
#include "../Gene_Networks_Classes/Trigger_Gene_Network.h"
#include "random"


/*
 * генная сеть пересчитывает концентрации субстратов в момент времени t с момента предыдущего обращения prev_time
 */
void Sample_Cell::recalculate_substr(double t) {
    substrates_pull.set_conc(trigger_gene_network.solver(substrates_pull, t - prev_time, 1000, vol));
    prev_time = t;
}

/*
 * если концентрации субстратов больше некоторых пороагов, то клетка выделяет эти субстраты в среду
 */
void Sample_Cell::secretion(Container &enviroment) {
    secretion_strategy->secretion(*this, enviroment);
}

Sample_Cell::~Sample_Cell() {

}

/*
 * клетка ест,если в данный момент в ней концентрации меньше некоторых порогов,
 * при чем она не может съесть больше некоторого количества субстратов в единицу времени
 */

void Sample_Cell::eat(Container &enviroment) {
    eat_strategy->eat(*this, enviroment);
}

/*
 * клетка перемещается стохастически и стоит, если при перемещении она вылезет за среду
 */
void Sample_Cell::move(Container &enviroment) {
    move_strategy->move(*this, enviroment);
}

/*
 * клетки умирают стохастически
 */
bool Sample_Cell::death(Container &enviroment) {
    return death_strategy->death(*this, enviroment);

}

Sample_Cell::Sample_Cell(int x, int y, double volume, Substrates_Pull &sp, int i) {
    x_coord = x;
    y_coord = y;
    vol = volume;
    substrates_pull = sp;
    id = i;
}

/*
 * клетки делятся стохастически на две клетки равного объема, субстраты распределяются пополам
 */
std::vector<Sample_Cell> Sample_Cell::segmentation() {
    std::normal_distribution<> normal_distribution(0, 1);
    std::random_device random_device;
    std::mt19937 generator(random_device());
    if (abs(normal_distribution(generator)) > segmentation_quantille) {
        Sample_Cell f(x_coord, y_coord, vol, -1);
        Sample_Cell s(x_coord, y_coord, vol, -1);
        Substrates_Pull r = substrates_pull.substratesPull_get_half_substr();
        f.substrates_pull = r;
        s.substrates_pull = r;
        f.prev_time = prev_time;
        s.prev_time = prev_time;
        s.trigger_gene_network = trigger_gene_network;
        f.trigger_gene_network = trigger_gene_network;
        f.eat_strategy = eat_strategy;
        s.eat_strategy = eat_strategy;
        s.move_strategy = move_strategy;
        f.move_strategy = move_strategy;
        s.death_strategy = death_strategy;
        f.death_strategy = death_strategy;
        s.type_of_move = type_of_move;
        f.type_of_move = type_of_move;
        f.secretion_strategy = secretion_strategy;
        s.secretion_strategy = secretion_strategy;
        return std::vector<Sample_Cell>{f, s};

    }
    return std::vector<Sample_Cell>{};
}

Sample_Cell::Sample_Cell(int x, int y, double volume, int i) {
    x_coord = x;
    y_coord = y;
    vol = volume;
    id = i;

}

