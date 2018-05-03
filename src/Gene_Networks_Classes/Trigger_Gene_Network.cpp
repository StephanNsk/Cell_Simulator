#include "Trigger_Gene_Network.h"
#include "../Substrates_Classes/Substrates_Pull.h"
#include <cmath>
#include <iostream>

Trigger_Gene_Network::Trigger_Gene_Network(Gene_Container &gene_container) {
    A1 = gene_container.get_gene(id_gene1).value * c1;
    A2 = gene_container.get_gene(id_gene2).value * c2;

}

/*
 * Первая функция в системе
 */

double Trigger_Gene_Network::func1(std::pair<double, double> substr_conc) {
    return A1 / (b1 + pow(substr_conc.second, m)) - q1 * substr_conc.first;
}

/*
 * Вторая функция в системе
 */

double Trigger_Gene_Network::func2(std::pair<double, double> substr_conc) {
    return A2 / (b2 + pow(substr_conc.first, m)) - q2 * substr_conc.second;
}

/*
 * Решение системы дифференциальных уравнений для генной сети
 */

std::vector<double> Trigger_Gene_Network::solver(const Substrates_Pull &sp, double t, int dots, double volume) {
    double start = 0;
    double finish = t;
    std::pair<double, double> curr_values = {sp.get_conc(ind_substr1) / volume, sp.get_conc(ind_substr2) / volume};
    double step = (finish - start) / (dots - 1);
    std::pair<double, double> prev_values = curr_values;
    for (int i = 0; i < dots; ++i) {
        curr_values.first = prev_values.first + step * func1(prev_values);
        curr_values.second = prev_values.second + step * func2(prev_values);
        if (curr_values.first < 0) {
            curr_values.first = 0;
        }
        if (curr_values.second < 0) {
            curr_values.second = 0;
        }
        prev_values = curr_values;
    }
    std::vector<double> res = sp.concentrations_sub;
    res[ind_substr1] = curr_values.first * volume;
    res[ind_substr2] = curr_values.second * volume;

    return res;
}
