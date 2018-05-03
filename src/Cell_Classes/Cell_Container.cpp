

#include "Cell_Container.h"
#include "Sample_Cell.h"
#include <sstream>
/*
 * удаление клетки из контейнера по id
 */
void Cell_Container::remove_cell(int id) {
    for (int i = 0; i < container.size(); ++i) {
        if (container[i].id == id) {
            container.erase(container.begin() + i);
            break;
        }
    }
}
/*
 * добавление клетки в контейнер
 */
void Cell_Container::add_cell(Sample_Cell &cell, Container& enviroment) {
    cell.id = max_id + 1;
    container.push_back(cell);
    enviroment.add_cell(std::pair<int, int>{cell.x_coord, cell.y_coord});
    ++max_id;
}
/*
 * одна итерация по всем клеткам контейнера, стохастически удаляет клетки
 */
void Cell_Container::iteration_death(Container &enviroment) {
    std::vector<int> death_cells;
    for (int i = 0; i < container.size(); ++i) {
        if (container[i].death(enviroment)) {
            death_cells.push_back(container[i].id);
            enviroment.die_cell(std::pair<int,int> {container[i].x_coord,container[i].y_coord});
        }
    }
    for (int i = 0; i < death_cells.size(); ++i) {
        remove_cell(death_cells[i]);
    }

}
/*
 * одна итерация передвижения клеток контейнера
 */
void Cell_Container::iteration_move(Container &enviroment) {
    for (int i = 0; i < container.size(); ++i) {
        container[i].move(enviroment);
    }

}
/*
 * итерация пересчета субстратов клетки при помощи триггерной генной сети
 */
void Cell_Container::iteration_recalculate_substr(double t) {
    for (int i = 0; i < container.size(); ++i) {
        container[i].recalculate_substr(t);
    }

}
/*
 * итерация деления клеток в контейнере
 */
void Cell_Container::iteration_segmentation(Container& enviroment) {
    std::vector<Sample_Cell> to_add;
    std::vector<int> id_to_death;
    std::vector<Sample_Cell> tmp_vec;
    for (int i = 0; i < container.size(); ++i) {
        tmp_vec = container[i].segmentation();
        if (!tmp_vec.empty()) {
            id_to_death.push_back(container[i].id);
            to_add.push_back(tmp_vec[0]);
            to_add.push_back(tmp_vec[1]);
        }
    }
    for (int i = 0; i < id_to_death.size(); ++i) {
        remove_cell(id_to_death[i]);
    }
    for (int i = 0; i < to_add.size(); ++i) {
        add_cell(to_add[i],enviroment);
    }

}

void Cell_Container::iteration_secretion(Container &enviroment) {
    for (int i = 0; i < container.size(); ++i) {
        container[i].secretion(enviroment);
    }
}
/*
 * возвращает  параметры состояния клеток контейнера в момент времени time
 */
std::string Cell_Container::get_info(double time) const {
    std::ostringstream oss;
    for (int i = 0; i < container.size(); ++i) {
        oss << time << "\t" << container[i].x_coord << "\t" << container[i].y_coord << "\t" << container[i].vol << "\t"
            << container[i].substrates_pull.get_conc(0) / container[i].vol << "\t"
            << container[i].substrates_pull.get_conc(1) / container[i].vol << "\t" <<
            container[i].id << "\t"<<container[i].type_of_move<<std::endl;
    }
    return oss.str();
}

/*
 * клетки контейнера кушают
 */

void Cell_Container::iteration_eat(Container &enviroment) {
    for (int i = 0; i < container.size(); ++i) {
        container[i].eat(enviroment);
    }
}
