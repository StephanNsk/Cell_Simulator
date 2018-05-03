#include "Gene_Container.h"
#include <utility>

Gene_Container::Gene_Container(std::vector<Gene_Container::gene> cont, std::map<std::string, int> dict) {
    gene_cont = std::move(cont);
    name_to_id = std::move(dict);
}

/*
 * Изменение значения данного гена
 */

void Gene_Container::change_gene_value(int id, double new_value) {
    gene_cont[id].value = new_value;
}

/*
 * Получение информации о гене по номеру
 */

Gene_Container::gene Gene_Container::get_gene(int id) const {
    return gene_cont[id];
}

/*
 * Получение информации о гене по имени
 */

Gene_Container::gene Gene_Container::get_gene(const std::string &name) {
    return gene_cont[name_to_id[name]];
}
