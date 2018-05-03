#include <iostream>
#include "src/Gene_Networks_Classes/Gene_Network.h"
#include "src/Gene_Networks_Classes/Euler_Gene_Network.h"
#include <math.h>
#include <vector>
#include "src/Substrates_Classes/Substrates_Pull.h"
#include "src/Gene_Networks_Classes/Gene_Container.h"
#include "src/Gene_Networks_Classes/Trigger_Gene_Network.h"
#include "src/Enviroment_Classes/Container.h"
#include "src/Enviroment_Classes/Enviroment.h"
#include "random"
#include "src/Cell_Classes/Sample_Cell.h"
#include <fstream>
#include "src/Cell_Classes/Cell_Container.h"
#include "src/Cell_Classes/Eat_Strategy.h"
#include "src/Cell_Classes/Sample_Eat_Strategy.h"
#include "src/Cell_Classes/Move_Strategy.h"
#include "src/Cell_Classes/Sample_Move_Strategy.h"
#include "src/Cell_Classes/Gradient_Move_Strategy.h"
#include "src/Cell_Classes/Death_Strategy.h"
#include "src/Cell_Classes/Sample_Death_Strategy.h"
#include "src/Cell_Classes/Mixed_Random_Gradient_Move_Strategy.h"
#include "src/Cell_Classes/Sample_Secretion_Strategy.h"

double f1(std::vector<double> st_v, std::vector<double> curr_v, double t) {
    double A1 = st_v[0];
    double B1 = st_v[1];
    double q1 = st_v[2];
    double m = st_v[3];
    double P1 = curr_v[0];
    double P2 = curr_v[1];
    return A1 / (B1 + pow(P2, m)) - q1 * P1;

}

double f2(std::vector<double> st_v, std::vector<double> curr_v, double t) {
    double A2 = st_v[0];
    double B2 = st_v[1];
    double q2 = st_v[2];
    double m = st_v[3];
    double P1 = curr_v[0];
    double P2 = curr_v[1];
    return A2 / (B2 + pow(P1, m)) - q2 * P2;
}

double check_f1(std::vector<double> st_v, std::vector<double> curr_v, double t) {
    double x = curr_v[0];
    double y = curr_v[1];
    return st_v[0] * x + st_v[1] * y;
}

double check_f2(std::vector<double> st_v, std::vector<double> curr_v, double t) {
    double x = curr_v[0];
    double y = curr_v[1];
    return st_v[0] * x + st_v[1] * y;
}

double exact1(double t) {
    return 4 * exp(-t) - exp(2 * t);
}

double exact2(double t) {
    return exp(-t) - exp(2 * t);
}

void print_vec(std::vector<double> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

void print_vec(std::vector<std::vector<double> > vec) {
    for (int i = 0; i < vec.size(); ++i) {
        print_vec(vec[i]);
    }
}

void print_pair(std::pair<double, double> p) {
    std::cout << p.first << " " << p.second << std::endl;
}

int main() {
    srand(time(NULL));
    std::ofstream file_cells("/Users/artem/CLionProjects/Gene_Netw/cells.txt");
    std::ofstream file_env("/Users/artem/CLionProjects/Gene_Netw/env.txt");
    int cont1 = 30;
    int cont2 = 30;
    Container container(cont1, cont2);
    Substrates_Pull substratesPull;
    std::vector<std::string> names_substr = {"S1", "S2"};
    std::map<std::string, int> dict;
    dict["S1"] = 0;
    dict["S2"] = 1;
    substratesPull.names = names_substr;
    substratesPull.dict_name_substr = dict;
    substratesPull.concentrations_sub = {0, 0};
    for (int i = 0; i < cont1; ++i) {
        for (int j = 0; j < cont2; ++j) {
            int c1 = rand() % 5000;
            int c2 = rand() % 5000;
            substratesPull.concentrations_sub = {(double) c1, (double) c2};

            container.add_ind_substrate(i, j, substratesPull);
        }
    }


    std::vector<Gene_Container::gene> g = {{"first",  0.2},
                                           {"second", 0.6}};
    std::map<std::string, int> map;
    map["first"] = 0;
    map["second"] = 1;
    Gene_Container gene_container(g, map);
    Trigger_Gene_Network trigger_gene_network(gene_container);
    int cells = 100;
    std::vector<Sample_Cell> cell_cont;
    substratesPull.concentrations_sub = {0, 0};
    Cell_Container cell_container;
    cell_container.max_id = 0;
    for (int k = 0; k < cells; ++k) {
        Sample_Cell sc = Sample_Cell();
        sc.y_coord = rand() % 50;
        sc.x_coord = rand() % 50;
        //sc.y_coord = k;
        //sc.x_coord = k;
        sc.trigger_gene_network = trigger_gene_network;
        sc.vol = rand() % 100 + 100;
        sc.prev_time = 0;
        sc.type_of_move = 0;
        sc.death_strategy = new Sample_Death_Strategy();
        sc.move_strategy = new Sample_Move_Strategy();
        sc.eat_strategy = new Sample_Eat_Strategy();
        sc.secretion_strategy = new Sample_Secretion_Strategy();
        substratesPull.concentrations_sub[0] = (rand() % (int) sc.vol) * 1.0;
        substratesPull.concentrations_sub[1] = (rand() % (int) sc.vol) * 1.0;
        sc.substrates_pull = substratesPull;
        container.add_cell(std::pair<int, int>(sc.x_coord, sc.y_coord));
        cell_container.add_cell(sc, container);
    }
    for (int k = 0; k < cells; ++k) {
        Sample_Cell sc = Sample_Cell();
        sc.y_coord = rand() % 50;
        sc.x_coord = rand() % 50;
        //sc.y_coord = k;
        //sc.x_coord = k;
        sc.trigger_gene_network = trigger_gene_network;
        sc.vol = rand() % 100 + 100;
        sc.prev_time = 0;
        sc.type_of_move = 1;
        sc.death_strategy = new Sample_Death_Strategy();
        sc.move_strategy = new Gradient_Move_Strategy();
        sc.eat_strategy = new Sample_Eat_Strategy();
        sc.secretion_strategy = new Sample_Secretion_Strategy();
        substratesPull.concentrations_sub[0] = (rand() % (int) sc.vol) * 1.0;
        substratesPull.concentrations_sub[1] = (rand() % (int) sc.vol) * 1.0;
        sc.substrates_pull = substratesPull;
        container.add_cell(std::pair<int, int>(sc.x_coord, sc.y_coord));
        cell_container.add_cell(sc, container);
    }

    for (int k = 0; k < cells; ++k) {
        Sample_Cell sc = Sample_Cell();
        sc.y_coord = rand() % 50;
        sc.x_coord = rand() % 50;
        sc.trigger_gene_network = trigger_gene_network;
        sc.vol = rand() % 100 + 100;
        sc.prev_time = 0;
        sc.type_of_move = 2;
        sc.death_strategy = new Sample_Death_Strategy();
        sc.move_strategy = new Mixed_Random_Gradient_Move_Strategy();
        sc.eat_strategy = new Sample_Eat_Strategy();
        sc.secretion_strategy = new Sample_Secretion_Strategy();
        substratesPull.concentrations_sub[0] = (rand() % (int) sc.vol) * 1.0;
        substratesPull.concentrations_sub[1] = (rand() % (int) sc.vol) * 1.0;
        sc.substrates_pull = substratesPull;
        container.add_cell(std::pair<int, int>(sc.x_coord, sc.y_coord));
        cell_container.add_cell(sc, container);
    }

    int max_time = 100;
    file_cells << "t" << "\t" << "x_coord" << "\t" << "y_coord" << "\t" << "vol" << "\t" << "S1" << "\t" << "S2" << "\t"
               << "id"
               << "\t" << "type_of_move" << std::endl;
    file_env << "t" << "\t" << "i_ind" << "\t" << "j_ind" << "\t" << "S1" << "\t" << "S2" << std::endl;
    std::vector<bool> bad_ind(cells);
    for (double l = 0; l < max_time; l += 0.1) {
        cell_container.iteration_secretion(container);
        cell_container.iteration_eat(container);
        if (int(l * 10) % 10 == 0) {
            cell_container.iteration_segmentation(container);
            cell_container.iteration_death(container);

        }
        cell_container.iteration_recalculate_substr(l);
        cell_container.iteration_move(container);

        file_cells << cell_container.get_info(l);
        std::vector<std::vector<Enviroment> > env = container.get_env();
        for (int j = 0; j < env.size(); ++j) {
            for (int k = 0; k < env[0].size(); ++k) {
                file_env << l << "\t" << j << "\t" << k << "\t" << env[j][k].Concentration_info.concentrations_sub[0]
                         << "\t" << env[j][k].Concentration_info.concentrations_sub[1] << std::endl;
            }
        }
    }
    return 0;
}