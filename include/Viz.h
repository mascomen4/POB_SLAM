//
// Created by pi on 02.12.2022.
//

#ifndef OPTIMIZATION_ROBOT_LOCALIZATION_VIZ_H
#define OPTIMIZATION_ROBOT_LOCALIZATION_VIZ_H


#include <memory>
#include <utility>
#include "SystemTypes.h"

class Viz {
public:
    Viz(std::shared_ptr<State> tState, std::shared_ptr<State> eState):
        tState(std::move(tState)), eState(std::move(eState)) {}

    void runPlotter();

    std::shared_ptr<State> tState;
    std::shared_ptr<State> eState;
};


#endif //OPTIMIZATION_ROBOT_LOCALIZATION_VIZ_H
