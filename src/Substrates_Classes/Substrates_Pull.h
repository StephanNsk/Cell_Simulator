#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>

class Substrates_Pull {
public:
    std::vector<double> concentrations_sub;

    std::vector<std::string> names;

    std::map<std::string, int> dict_name_substr;

    Substrates_Pull();

    Substrates_Pull(const std::vector<double> &conc, std::map<std::string, int> dict, std::vector<std::string> names);

    explicit Substrates_Pull(const std::vector<double> &conc);

    void remove_substrate(const std::string &name, double count);

    void add_substrate(const std::string &name, double count);


    double get_conc(int ind) const;

    std::vector<double> get_conc() const;

    std::pair<double, double> get_pair_conc(int ind1, int ind2) const;

    std::map<std::string, int> get_dict() const;

    void set_conc(const std::vector<double> &conc) {
        concentrations_sub = conc;
    }

    Substrates_Pull substratesPull_get_half_substr() const;
};
