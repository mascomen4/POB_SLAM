//
// Created by pi on 02.12.2022.
//

#include "../include/Optimizer.h"

template<typename T>
bool Optimizer::CostFunctor::operator()(const T* const position, const T* const orientation, T* residuals) const {
    T vec1[2] = { lx - position[0], ly - position[1] };
    T vec2[2] = { cos(orientation[0]), sin(orientation[0]) };

    // TODO: Make a more robust angle calculation. Currently it's numerically unstable when close to 90 degrees. (WHY ?)
    T vec1_len = (T)sqrt(vec1[0]*vec1[0] + vec1[1]*vec1[1]);
    T vec2_len = (T)sqrt(vec2[0] * vec2[0] + vec2[1] * vec2[1]);
    T cos_est_theta = (vec1[0] * vec2[0] + vec1[1] * vec2[1]) / vec1_len / vec2_len;
    residuals[0] = theta - acos(cos_est_theta);
    residuals[1] = ro - vec1_len;
    return true;
}

ceres::CostFunction* Optimizer::CostFunctor::Create(const double lx, const double ly, const double theta, const double ro) {
    return (new ceres::AutoDiffCostFunction<CostFunctor, 2, 2, 1>(new CostFunctor(lx, ly, theta, ro)));
}

void Optimizer::optimize(std::shared_ptr<State> state, const std::shared_ptr<Observations> & obs,
                         const std::shared_ptr<Landmarks> & landmarks) {
    ceres::Problem problem;
    auto position = state->position;
    auto theta = state->theta;
    for (int i = 0; i < 4; ++i) {
        ceres::CostFunction *cost_function = CostFunctor::Create(landmarks->at(i).lx, landmarks->at(i).ly,
                                                                 obs->at(i).theta, obs->at(i).distance);
        problem.AddResidualBlock(cost_function, nullptr, position, &theta);
    }
    ceres::Solver::Options options;
    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary);
    std::cout << summary.BriefReport();

    state->position[0] = position[0];
    state->position[1] = position[1];
    state->theta = theta;

    std::cout << "\nx: " << state->position[0] << " y: " << state->position[1] << std::endl;
}