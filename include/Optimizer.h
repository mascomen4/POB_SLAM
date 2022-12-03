//
// Created by pi on 02.12.2022.
//

#ifndef OPTIMIZATION_ROBOT_LOCALIZATION_OPTIMIZER_H
#define OPTIMIZATION_ROBOT_LOCALIZATION_OPTIMIZER_H

#include "Sensor.h"
#include "SystemTypes.h"

#include <ceres/ceres.h>


class Optimizer {
public:
    // Observations [theta, length] need to be passed for each landmark at time i.
    // TODO: What if I pass the heading angle? (orientation)
    struct CostFunctor {
        CostFunctor(double lx, double ly, double theta, double ro) : lx(lx), ly(ly), theta(theta), ro(ro) {}

        template<typename T>
        bool operator()(const T *const position, const T *const orientation, T *residuals) const;

        static ceres::CostFunction* Create(const double lx, const double ly, const double theta, const double ro);

        double lx, ly;
        double theta, ro;
    };

    virtual void optimize(std::shared_ptr<State>, const std::shared_ptr<Observations> &,
            const std::shared_ptr<Landmarks> & );
};


#endif //OPTIMIZATION_ROBOT_LOCALIZATION_OPTIMIZER_H
