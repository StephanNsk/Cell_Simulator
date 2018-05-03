#pragma once

#include <string>
#include <map>
#include <vector>

class Gene_Container {

public:
    struct gene {
        std::string name;
        double value;
    };
    std::map<std::string, int> name_to_id;
    std::vector<gene> gene_cont;
public:
    void change_gene_value(int id, double new_value);

    gene get_gene(int id) const;

    gene get_gene(const std::string &name);

    Gene_Container(std::vector<gene> cont, std::map<std::string, int> dict);
};
