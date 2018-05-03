#pragma once

class Segmentation_Gene_Network {
private:
    double thr1 = 0.2;
    double thr2 = 0.3;
    double volume = 3;
public:
    enum strategy {
        increace_volume, segmentation, decline
    };

    strategy segmentation_rule(double first_conc, double second_conc, double cell_colume);
};
