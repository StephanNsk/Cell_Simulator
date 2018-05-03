#include "Container.h"
#include "Enviroment.h"
#include "../Cell_Classes/Cell.h"

std::vector<std::vector<Enviroment>> Enviroment_zone;

Container::Container() = default;

Container::Container(int size_x, int size_y) {
    Enviroment_zone = std::vector<std::vector<Enviroment>>(size_x, std::vector<Enviroment>(size_y));
}

/*
 * По координатам клетки вычисляет нужную ячейку среды и добавляет в нее новую клетку
 */

void Container::add_cell(const std::pair<int, int> &cell_coords) {
    int x = cell_coords.first;
    int y = cell_coords.second;
    double xx = max_x * 1.0 / Enviroment_zone[0].size();
    double yy = max_y * 1.0 / Enviroment_zone.size();
    Enviroment_zone[(int) (x / xx)][(int) (y / yy)].add_cell(cell_coords);
}

/*
 * По координатам клетки вычисляет ячейку среды, в которой находится клетка и удаляет ее
 */

void Container::die_cell(const std::pair<int, int> &cell_coords) {
    int x = cell_coords.first;
    int y = cell_coords.second;
    double xx = max_x * 1.0 / Enviroment_zone[0].size();
    double yy = max_y * 1.0 / Enviroment_zone.size();
    Enviroment_zone[(int) (x / xx)][(int) (y / yy)].die_cell(cell_coords);
}

/*
 * По координатам вычисляет нужную ячейку среды и уменьшает концентрацию субстрата в ней
 */

void Container::remove_substrate(int x, int y, const std::string &name, double count) {
    double xx = max_x * 1.0 / Enviroment_zone[0].size();
    double yy = max_y * 1.0 / Enviroment_zone.size();
    Enviroment_zone[(int) (x / xx)][(int) (y / yy)].remove_substrate(name, count);
}

/*
 * По координатам вычисляет нужную ячейку среды и увеличивает концентрацию субстрата в ней
 */

void Container::add_substrate(int x, int y, const std::string &name, double count) {
    double xx = max_x * 1.0 / Enviroment_zone[0].size();
    double yy = max_y * 1.0 / Enviroment_zone.size();
    Enviroment_zone[(int) (x / xx)][(int) (y / yy)].add_substrate(name, count);
}

/*
 * Выдает концентрацию субстратов в данной точке
 */

Substrates_Pull Container::get_substrates(int x, int y) const {
    double xx = max_x * 1.0 / Enviroment_zone[0].size();
    double yy = max_y * 1.0 / Enviroment_zone.size();

    return Enviroment_zone[(int) (x / xx)][(int) (y / yy)].get_substrates();
}

/*
 * Увеличение концентрации субстрата в данной ячейке среды
 */

void Container::add_ind_substrate(int i, int j, const Substrates_Pull &sp) {
    Enviroment_zone[i][j].Concentration_info = sp;
}

/*
 * Возвращает таблицу ячеек среды
 */

std::vector<std::vector<Enviroment> > Container::get_env() {
    return Enviroment_zone;
}

/*
 * Передвижение клетки по среде
 */

bool Container::move_cell(const std::pair<int, int> &curr, const std::pair<int, int> &diff) {
    die_cell(curr);
    std::pair<int, int> new_coord = {curr.first + diff.first, curr.second + diff.second};
    if (new_coord.first < max_x && new_coord.second < max_y && new_coord.first >= 0 && new_coord.second >= 0) {
        die_cell(curr);
        add_cell(new_coord);
        return true;
    }
    return false;
}

std::vector<std::pair<double, double> > Container::get_counts_substrates_of_nearest_parts(double x, double y) const {
    std::vector<std::pair<double, double> > result(9);
    double xx = max_x * 1.0 / Enviroment_zone[0].size();
    double yy = max_y * 1.0 / Enviroment_zone.size();
    int ind_x = (int) (x / xx);
    int ind_y = (int) (y / yy);
    std::pair<double, double> bad_pair = {-1, -1};
    result[4] = Enviroment_zone[ind_x][ind_y].Concentration_info.get_pair_conc(0, 1);
    if (ind_x == 0) {
        result[0] = bad_pair;
        result[3] = bad_pair;
        result[6] = bad_pair;
        result[5] = Enviroment_zone[ind_x + 1][ind_y].Concentration_info.get_pair_conc(0, 1);
        if (ind_y == 0) {
            result[7] = bad_pair;
            result[8] = bad_pair;
            result[1] = Enviroment_zone[ind_x][ind_y + 1].Concentration_info.get_pair_conc(0, 1);
            result[2] = Enviroment_zone[ind_x + 1][ind_y + 1].Concentration_info.get_pair_conc(0, 1);
            return result;
        }
        if (ind_y == Enviroment_zone.size() - 1) {
            result[1] = bad_pair;
            result[2] = bad_pair;
            result[7] = Enviroment_zone[ind_x][ind_y - 1].Concentration_info.get_pair_conc(0, 1);
            result[8] = Enviroment_zone[ind_x + 1][ind_y - 1].Concentration_info.get_pair_conc(0, 1);
            return result;
        }
        result[1] = Enviroment_zone[ind_x][ind_y + 1].Concentration_info.get_pair_conc(0, 1);
        result[2] = Enviroment_zone[ind_x + 1][ind_y + 1].Concentration_info.get_pair_conc(0, 1);
        result[7] = Enviroment_zone[ind_x][ind_y - 1].Concentration_info.get_pair_conc(0, 1);
        result[8] = Enviroment_zone[ind_x + 1][ind_y - 1].Concentration_info.get_pair_conc(0, 1);
        return result;

    }
    if (ind_x == Enviroment_zone[0].size() - 1) {
        result[2] = bad_pair;
        result[5] = bad_pair;
        result[8] = bad_pair;
        result[3] = Enviroment_zone[ind_x - 1][ind_y].Concentration_info.get_pair_conc(0, 1);
        if (ind_y == 0) {
            result[6] = bad_pair;
            result[7] = bad_pair;
            result[0] = Enviroment_zone[ind_x - 1][ind_y + 1].Concentration_info.get_pair_conc(0, 1);
            result[1] = Enviroment_zone[ind_x][ind_y + 1].Concentration_info.get_pair_conc(0, 1);
            return result;
        }
        if (ind_y == Enviroment_zone.size() - 1) {
            result[0] = bad_pair;
            result[1] = bad_pair;
            result[6] = Enviroment_zone[ind_x - 1][ind_y - 1].Concentration_info.get_pair_conc(0, 1);
            result[7] = Enviroment_zone[ind_x][ind_y - 1].Concentration_info.get_pair_conc(0, 1);
            return result;
        }
        result[1] = Enviroment_zone[ind_x][ind_y + 1].Concentration_info.get_pair_conc(0, 1);
        result[0] = Enviroment_zone[ind_x - 1][ind_y + 1].Concentration_info.get_pair_conc(0, 1);
        result[6] = Enviroment_zone[ind_x - 1][ind_y - 1].Concentration_info.get_pair_conc(0, 1);
        result[7] = Enviroment_zone[ind_x][ind_y - 1].Concentration_info.get_pair_conc(0, 1);
        return result;

    }
    result[5] = Enviroment_zone[ind_x + 1][ind_y].Concentration_info.get_pair_conc(0, 1);
    result[3] = Enviroment_zone[ind_x - 1][ind_y].Concentration_info.get_pair_conc(0, 1);
    if (ind_y == 0) {
        result[6] = bad_pair;
        result[7] = bad_pair;
        result[8] = bad_pair;
        result[0] = Enviroment_zone[ind_x - 1][ind_y + 1].Concentration_info.get_pair_conc(0, 1);
        result[1] = Enviroment_zone[ind_x][ind_y + 1].Concentration_info.get_pair_conc(0, 1);
        result[2] = Enviroment_zone[ind_x + 1][ind_y + 1].Concentration_info.get_pair_conc(0, 1);
        return result;

    }
    if (ind_y == Enviroment_zone.size() - 1) {
        result[0] = bad_pair;
        result[1] = bad_pair;
        result[2] = bad_pair;
        result[6] = Enviroment_zone[ind_x - 1][ind_y - 1].Concentration_info.get_pair_conc(0, 1);
        result[7] = Enviroment_zone[ind_x][ind_y - 1].Concentration_info.get_pair_conc(0, 1);
        result[8] = Enviroment_zone[ind_x + 1][ind_y - 1].Concentration_info.get_pair_conc(0, 1);
        return result;
    }
    result[0] = Enviroment_zone[ind_x - 1][ind_y + 1].Concentration_info.get_pair_conc(0, 1);
    result[1] = Enviroment_zone[ind_x][ind_y + 1].Concentration_info.get_pair_conc(0, 1);
    result[2] = Enviroment_zone[ind_x + 1][ind_y + 1].Concentration_info.get_pair_conc(0, 1);
    result[6] = Enviroment_zone[ind_x - 1][ind_y - 1].Concentration_info.get_pair_conc(0, 1);
    result[7] = Enviroment_zone[ind_x][ind_y - 1].Concentration_info.get_pair_conc(0, 1);
    result[8] = Enviroment_zone[ind_x + 1][ind_y - 1].Concentration_info.get_pair_conc(0, 1);
    return result;
}

Container::~Container() = default;
