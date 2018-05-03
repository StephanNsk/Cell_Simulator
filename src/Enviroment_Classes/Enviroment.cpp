#include "Enviroment.h"

Enviroment::Enviroment() = default;

/*
 * Клетка с указанными координатами удаляется из данной ячейки среды
 */

void Enviroment::die_cell(std::pair<int, int> cell_coords) {
    for (int i = 0; i < Cells.size(); ++i) {
        if (Cells[i].first == cell_coords.first && Cells[i].second == cell_coords.second) {
            Cells.erase(Cells.begin() + i);
            break;
        }
    }
}

/*
 * Добавление клетки с указанными координатами в данную ячейку среды
 */

void Enviroment::add_cell(std::pair<int, int> cell_coords) {
    Cells.push_back(cell_coords);
}

/*
 * Добавление субстрата в данную ячейку среды
 */

void Enviroment::add_substrate(const std::string &name, double count) {
    Concentration_info.add_substrate(name, count);
}

/*
 * Удаление субстрата из данной ячейки среды
 */

void Enviroment::remove_substrate(const std::string &name, double count) {
    Concentration_info.remove_substrate(name, count);
}

/*
 * Информация о концентрации субстратов в данной ячейке среды
 */

Substrates_Pull Enviroment::get_substrates() {
    return Concentration_info;
}

/*
 * Количество клеток в данной ячейке среды
 */

size_t Enviroment::cells_count() {
    return Cells.size();
}

/*
 *
 */

//void Enviroment:: move_cell(int id) {

//}

Enviroment::~Enviroment() = default;