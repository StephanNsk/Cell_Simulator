#pragma once

#include <string>
#include "Gene_Container.h"
#include "../Substrates_Classes/Substrates_Pull.h"

class Trigger_Gene_Network {
protected:
    int id_gene1 = 0;
    int id_gene2 = 1;
    double c1 = 1;
    double c2 = 1;
    int m = 1;
    double b1 = 0.5;
    double b2 = 0.4;
    double q1 = 3;
    double q2 = 2;
    int ind_substr1 = 0;
    int ind_substr2 = 1;
    double A1;
    double A2;

    double func1(std::pair<double, double> substr_conc);

    double func2(std::pair<double, double> substr_conc);

public:
    Trigger_Gene_Network() = default;

    explicit Trigger_Gene_Network(Gene_Container &gene_container);

    std::vector<double> solver(const Substrates_Pull &sp, double t, int dots, double volume);
};
