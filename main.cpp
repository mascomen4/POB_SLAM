#include <iostream>
#include <vector>
#include <thread>

#include <ceres/ceres.h>

#include "include/RobotInterface.h"
#include "include/Viz.h"
#include "include/InteractionHelper.h"


using namespace std;

int main(){
    shared_ptr<Landmarks> landmarks( new Landmarks({ {3, 3}, {2, 4}, {6, 1}, {1, 8} }) );
    shared_ptr<State> tState(new State);

    RobotInterface *robot = new Robot(landmarks, tState);
    auto eState = robot->getEstimatedState();

    Viz viz(tState, eState);
    std::thread plot_thread( [viz]() mutable {viz.runPlotter();} );

    while (true) {
        QueryResult qr = InteractionHelper::getCommand();
        if (!qr) break;
        Control::Command command = qr.command;
        robot->execute(command);
        robot->localize();
    }

    plot_thread.join();
}
