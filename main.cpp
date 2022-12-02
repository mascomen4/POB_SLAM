#include <iostream>
#include <ceres/ceres.h>
#include <vector>
//#include <math.h>

using namespace std;

// Observations [theta, length] need to be passed for each landmark at time i.
// TODO: What if I pass the heading angle? (orientation)
struct CostFunctor {
    CostFunctor(double lx, double ly, double theta, double ro) : lx(lx), ly(ly), theta(theta), ro(ro) {}
    template<typename T>
    bool operator()(const T* const position, const T* const orientation, T* residuals) const {
        T vec1[2] = { lx - position[0], ly - position[1] };
        T vec2[2] = { cos(orientation[0]), sin(orientation[0]) };

        T vec1_len = (T)sqrt(vec1[0]*vec1[0] + vec1[1]*vec1[1]);
        T vec2_len = (T)sqrt(vec2[0] * vec2[0] + vec2[1] * vec2[1]);
        T cos_est_theta = (vec1[0] * vec2[0] + vec1[1] * vec2[1]) / vec1_len / vec2_len;
        residuals[0] = theta - (T)acos(cos_est_theta);
        residuals[1] = ro - (T)vec1_len;
        return true;
    }

    static ceres::CostFunction* Create(const double lx, const double ly, const double theta, const double ro) {
        return (new ceres::AutoDiffCostFunction<CostFunctor, 2, 2, 1>(new CostFunctor(lx, ly, theta, ro)));
    }

    double lx, ly;
    double theta, ro;
};

double angle(const double * const vec1, const double * const vec2){
    double vec1_len = sqrt(vec1[0]*vec1[0] + vec1[1]*vec1[1]);
    double vec2_len = sqrt(vec2[0] * vec2[0] + vec2[1] * vec2[1]);
    double cos_est_theta = (vec1[0] * vec2[0] + vec1[1] * vec2[1]) / vec1_len / vec2_len;
    return acos(cos_est_theta);
}

double ro (const double landmark[2], const double position[2]){
    double vec[2] = { landmark[0] - position[0], landmark[1] - position[1] };
    return sqrt( vec[0] * vec[0] + vec[1] * vec[1] );
}

int main() {
    double landmarks[4][2] = { {6., 2.}, {3., 4.}, {2., 5.}, {1., 7.} };

    double initial_x = 0.0, initial_y = 0.0, initial_orientation = 10.;
    double x = initial_x, y = initial_y;
    double *orientation = &initial_orientation;
    double position[2] = {x, y};

    ceres::Problem problem;

    vector<vector<double>> observations;
    double curr_point[2] = {2. , 0.};
    observations.reserve(4);
    for (int i = 0; i < 4; ++i){
        vector<double> tmp;
        tmp.push_back(angle(landmarks[i], curr_point ));
        tmp.push_back(ro( landmarks[i], curr_point));
        observations.push_back(tmp);
    }

    for (int i = 0; i < 4; ++i){
        ceres::CostFunction* cost_function = CostFunctor::Create(landmarks[i][0], landmarks[i][1],
                                                                 observations[i][0], observations[i][1]);
        problem.AddResidualBlock(cost_function, nullptr, position, orientation);
    }


    ceres::Solver::Options options;
    ceres::Solver::Summary summary;

    ceres::Solve(options, &problem, &summary);

    std::cout << summary.FullReport() << std::endl;
    cout << "x: " << initial_x << "->" << position[0] << "\ny: " << initial_y << "->" << position[1];
    return 0;
}
