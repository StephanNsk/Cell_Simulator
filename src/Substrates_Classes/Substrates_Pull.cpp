#include "Substrates_Pull.h"
#include <utility>

Substrates_Pull::Substrates_Pull() = default;

Substrates_Pull::Substrates_Pull(const std::vector<double> &conc, const std::map<std::string, int> dict,
                                 std::vector<std::string> n) {
    concentrations_sub = conc;
    dict_name_substr = dict;
    names = std::move(n);
}

Substrates_Pull::Substrates_Pull(const std::vector<double> &conc) {
    concentrations_sub = conc;
}

/*
 * Увеличение концентрации субстрата по имени
 */

void Substrates_Pull::add_substrate(const std::string &name, double count) {
    concentrations_sub[dict_name_substr[name]] += count;
}

/*
 * Уменьшение концентрации субстрата по имени
 */

void Substrates_Pull::remove_substrate(const std::string &name, double count) {
    concentrations_sub[dict_name_substr[name]] = std::max(concentrations_sub[dict_name_substr[name]] - count, 0.0);
}

/*
 * Возвращает словарь с номерами и названиями субстратов
 */

std::map<std::string, int> Substrates_Pull::get_dict() const {
    return dict_name_substr;
}

/*
 * Информация о концентрации субстрата по номеру
 */

double Substrates_Pull::get_conc(int ind) const {
    return concentrations_sub[ind];
}

/*
 * Информация о концентрации всех субстратов
 */

std::vector<double> Substrates_Pull::get_conc() const {
    return concentrations_sub;
}

/*
 * Возвращает половину концентрации каждого субстрата
 */

Substrates_Pull Substrates_Pull::substratesPull_get_half_substr() const {
    std::vector<double> conc_res = concentrations_sub;
    for (double &conc_re : conc_res) {
        conc_re /= 2;
    }
    return Substrates_Pull(conc_res, dict_name_substr, names);
}

std::pair<double, double> Substrates_Pull::get_pair_conc(int ind1, int ind2) const {
    return {concentrations_sub[ind1], concentrations_sub[ind2]};
}
