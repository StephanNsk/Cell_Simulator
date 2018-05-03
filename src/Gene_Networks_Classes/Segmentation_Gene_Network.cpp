#include "Segmentation_Gene_Network.h"

Segmentation_Gene_Network::strategy

/*
 * Правила деления клетки
 */

Segmentation_Gene_Network::segmentation_rule(double first_conc, double second_conc, double cell_volume) {
    if (first_conc > thr1 && second_conc > thr2 && cell_volume > volume) {
        return segmentation;
    }
    if (first_conc < thr1 || second_conc < thr2) {
        return decline;
    } else {
        return increace_volume;
    }
}
