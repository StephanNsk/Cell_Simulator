

#include "Gradient_Move_Strategy.h"
#include "Sample_Cell.h"
#include "random"


void Gradient_Move_Strategy::move(Sample_Cell &cell, Container &enviroment) {
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(-2, 2);
    std::pair<int, int> dxdy = {distribution(generator), distribution(generator)};
    double s1 = cell.substrates_pull.concentrations_sub[0];
    double s2 = cell.substrates_pull.concentrations_sub[1];
    std::vector<std::pair<double, double> > substr_info = enviroment.get_counts_substrates_of_nearest_parts(
            cell.x_coord,
            cell.y_coord);
    int best_ind = 4;
    int dx;
    int dy;
    double best_res1 = substr_info[4].first;
    double best_res2 = substr_info[4].second;
    if (s1 > s2) {
        for (int i = 0; i < substr_info.size(); ++i) {
            if (substr_info[i].second > best_res2) {
                best_ind = i;
                best_res2 = substr_info[i].second;
            }
        }
    } else {
        for (int i = 0; i < substr_info.size(); ++i) {
            if (substr_info[i].first > best_res1) {
                best_ind = i;
                best_res1 = substr_info[i].first;
            }
        }
    }
    switch (best_ind) {
        case 0:
            dx = -1;
            dy = 1;
            break;
        case 1:
            dx = 0;
            dy = 1;
            break;
        case 2:
            dx = 1;
            dy = 1;
            break;
        case 3:
            dx = -1;
            dy = 0;
            break;
        case 4:
            dx = 0;
            dy = 0;
            break;
        case 5:
            dx = 1;
            dy = 0;
            break;
        case 6:
            dx = -1;
            dy = -1;
            break;
        case 7:
            dx = 0;
            dy = -1;
            break;
        case 8:
            dx = 1;
            dy = -1;
            break;
        default:
            break;
    }
    if (enviroment.move_cell(std::pair<int , int >{cell.x_coord, cell.y_coord}, {dx, dy})) {
        cell.x_coord += dx;
        cell.y_coord += dy;
    }
}
