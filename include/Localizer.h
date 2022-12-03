//
// Created by pi on 02.12.2022.
//

#ifndef OPTIMIZATION_ROBOT_LOCALIZATION_LOCALIZER_H
#define OPTIMIZATION_ROBOT_LOCALIZATION_LOCALIZER_H

#include <utility>
#include <vector>
#include <memory>

#include "Sensor.h"
#include "Optimizer.h"
#include "SystemTypes.h"

class Localizer {
public:

    Localizer(std::shared_ptr<Landmarks> lm, std::shared_ptr<Optimizer> optimizer) : landmarks(std::move(lm)),
        optimizer(std::move(optimizer)) {}

    explicit Localizer(std::shared_ptr<Landmarks> lm) : landmarks(std::move(lm)), optimizer(new Optimizer) {}

    virtual void localize(std::shared_ptr<State> state, std::shared_ptr<Observations> &obs) {
        optimizer->optimize(std::move(state), obs, landmarks);
    };

    std::shared_ptr<Landmarks> landmarks;
    std::shared_ptr<Optimizer> optimizer;
};

#endif //OPTIMIZATION_ROBOT_LOCALIZATION_LOCALIZER_H
