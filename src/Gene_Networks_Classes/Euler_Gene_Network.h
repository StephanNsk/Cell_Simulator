#pragma once

#include <functional>
#include "Gene_Network.h"

class Euler_Gene_Network : public Gene_Network {

public:

    int count_dots;

    std::vector<double> solver(std::vector<double> &
    current_values, double t) override;

    Euler_Gene_Network(
            std::vector<std::function<double(std::vector<double>, std::vector<double>, double t)> > functions,
            std::vector<std::vector<double> > st_par,
            int count_dots);


    ~Euler_Gene_Network() override;

};
