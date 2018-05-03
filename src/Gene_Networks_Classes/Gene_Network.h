#pragma once

#include <iostream>
#include <vector>
#include <functional>

class Gene_Network {

protected:

    std::vector<std::vector<double> > static_params;

public:

    virtual std::vector<double> solver(std::vector<double> &current_values, double t_start) = 0;

    std::vector<std::function<double(std::vector<double>, std::vector<double>, double t)> > vector_function;

    virtual ~Gene_Network() = default;

};
