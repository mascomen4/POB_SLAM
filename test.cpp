//
// Created by pi on 02.12.2022.
//
#include <ceres/ceres.h>
#include <iostream>

using namespace std;

struct CostFunctor{
    template<typename T>
    bool operator ()( T const * const x, T* residual) const {
        residual[0] = 5. - x[0];
        return true;
    }
};

int main(){
    double initial_x = -100, x = initial_x;

    ceres::Problem problem;

    auto *cost_function = new ceres::AutoDiffCostFunction<CostFunctor, 1, 1>(new CostFunctor());

    problem.AddResidualBlock(cost_function, nullptr, &x);

    ceres::Solver::Options options;
    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary);
    cout << summary.FullReport() << endl;
    cout << "x: " << initial_x << "-> " << x;
    return 0;



}