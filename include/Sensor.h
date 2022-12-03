//
// Created by pi on 02.12.2022.
//

#ifndef OPTIMIZATION_ROBOT_LOCALIZATION_SENSOR_H
#define OPTIMIZATION_ROBOT_LOCALIZATION_SENSOR_H

#include <utility>
#include <vector>
#include <memory>

#include <ceres/ceres.h>

#include "SystemTypes.h"

class Sensor {
public:
    Sensor(std::shared_ptr<State> state, std::shared_ptr<Landmarks> lm):
        true_state(std::move(state)), landmarks(std::move(lm)) {}

    virtual std::shared_ptr<Observations> sense(){
        std::shared_ptr<Observations> pObs(new Observations);
        for (auto & i : *landmarks){
            double dist = ro( {i.lx, i.ly}, true_state->position );
            double diff_vec[2] = { i.lx - true_state->position[0], i.ly - true_state->position[1] };
            double theta = angle( {1, 0},  diff_vec);
            Observation ob{};
            ob.theta = theta;
            ob.distance = dist;
            pObs->emplace_back(ob);
        }
        return pObs;
    }

    static double angle( const double (&vec1)[2], const double (&vec2)[2] ){
        double vec1_len = sqrt(vec1[0]*vec1[0] + vec1[1]*vec1[1]);
        double vec2_len = sqrt(vec2[0] * vec2[0] + vec2[1] * vec2[1]);
        double cos_est_theta = (vec1[0] * vec2[0] + vec1[1] * vec2[1]) / vec1_len / vec2_len;
        return acos(cos_est_theta);
    }

    static double ro (const double (&landmark)[2], const double (&position)[2]){
        double vec[2] = { landmark[0] - position[0], landmark[1] - position[1] };
        return sqrt( vec[0] * vec[0] + vec[1] * vec[1] );
    }

    std::shared_ptr<State> true_state;
    std::shared_ptr<Landmarks> landmarks;
};


#endif //OPTIMIZATION_ROBOT_LOCALIZATION_SENSOR_H
