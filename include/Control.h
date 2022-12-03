//
// Created by pi on 02.12.2022.
//

#ifndef OPTIMIZATION_ROBOT_LOCALIZATION_CONTROL_H
#define OPTIMIZATION_ROBOT_LOCALIZATION_CONTROL_H

#include <memory>
#include <utility>
#include <math.h>

#include "SystemTypes.h"

class Control {
public:

    explicit Control(std::shared_ptr<State> ts): true_state(std::move(ts)) {}

    struct Command{
        double direction[2];
        double distance;
    };

    virtual void execute(const Command& command){
        double e[2] = {1, 0};
        // sqrt of 2 because the length of direction is always sqrt(2)
        double est_cos = cos( abs(e[0] * command.direction[0] + e[1] * command.direction[1]) / sqrt(2) );
        double x_diff = command.distance * est_cos;
        double y_diff = command.distance * sin( acos( est_cos ) );
        true_state->position[0] += command.direction[0] * x_diff;
        true_state->position[1] += command.direction[1] * y_diff;
    }

    std::shared_ptr<State> true_state;
};


#endif //OPTIMIZATION_ROBOT_LOCALIZATION_CONTROL_H
