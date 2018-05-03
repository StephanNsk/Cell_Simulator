#include "Euler_Gene_Network.h"
#include <utility>
#include <vector>
#include <functional>

Euler_Gene_Network::Euler_Gene_Network(
        std::vector<std::function<double(std::vector<double>, std::vector<double>, double t)> > functions,
        std::vector<std::vector<double> > st_p, int cd) {
    static_params = std::move(st_p);
    count_dots = cd;
    vector_function = std::move(functions);
}

Euler_Gene_Network::~Euler_Gene_Network() = default;

/*
 * Решение системы дифференциальных уравнений методом Эйлера
 */

std::vector<double>
Euler_Gene_Network::solver(std::vector<double> &current_values,
                           double t) {
    double start = 0;
    double current_time = start;
    double finish = t;
    double step = (finish - start) / (count_dots - 1);
    std::vector<double> prev_values(vector_function.size());
    prev_values = current_values;
    current_time += step;
    for (int i = 1; i < count_dots; ++i) {
        for (int j = 0; j < vector_function.size(); ++j) {
            current_values[j] =
                    prev_values[j] + step * vector_function[j](static_params[j], prev_values, current_time);
        }
        prev_values = current_values;
        current_time += step;
    }
    return current_values;
}
