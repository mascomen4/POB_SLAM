//
// Created by pi on 02.12.2022.
//

#ifndef OPTIMIZATION_ROBOT_LOCALIZATION_SYSTEMTYPES_H
#define OPTIMIZATION_ROBOT_LOCALIZATION_SYSTEMTYPES_H

#include <vector>


struct Landmark {

    Landmark(double lx, double ly): lx(lx), ly(ly) {}

    double lx{}, ly{};
};

using Landmarks = std::vector<Landmark>;




struct Observation{
    // Do I have to put which observation is this for? No, I'll use indexing of the vector as indexing of the
    // landmarks
    double theta, distance;
};

using Observations = std::vector<Observation>;




struct State {

    State(const double (&pos)[2], double theta): theta(theta) {
        position[0] = pos[0];
        position[1] = pos[1];
    }

    State() = default;

    double position[2]{};
    double theta{};
};





#endif //OPTIMIZATION_ROBOT_LOCALIZATION_SYSTEMTYPES_H
