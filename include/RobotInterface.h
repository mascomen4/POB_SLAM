//
// Created by pi on 02.12.2022.
//

#ifndef OPTIMIZATION_ROBOT_LOCALIZATION_ROBOTINTERFACE_H
#define OPTIMIZATION_ROBOT_LOCALIZATION_ROBOTINTERFACE_H

#include <memory>
#include <utility>

#include "Localizer.h"
#include "Sensor.h"
#include "Control.h"

class RobotInterface {
public:
    virtual void execute(Control::Command &command) = 0;

    virtual void localize() = 0;

    virtual std::shared_ptr<State> getEstimatedState () = 0;
};

class Robot: public RobotInterface {
public:

    Robot(std::shared_ptr<Localizer> l, std::shared_ptr<Sensor> sensor, std::shared_ptr<State> i_state):
        localizer(std::move(l)),
        sensor(std::move(sensor)),
        estimated_state(std::move(i_state)) {}

    explicit Robot(const std::shared_ptr<Landmarks>& lm, const std::shared_ptr<State> & tState):
        estimated_state(new State),
        sensor(new Sensor(tState, lm)),
        localizer(new Localizer(lm)),
        control(new Control(tState)) {}

    // TODO: Consider creating a Robot instance from predefined state

    void execute(Control::Command &command) override{
        control->execute(command);
    }

    void localize() override{
        std::shared_ptr<Observations> obs = sensor->sense();
        localizer->localize(estimated_state, obs);
    }

    std::shared_ptr<State> getEstimatedState () override {
        return estimated_state;
    }

private:
    std::shared_ptr<State> estimated_state;
    std::shared_ptr<Sensor> sensor;
    std::shared_ptr<Localizer> localizer;
    std::shared_ptr<Control> control;

};

#endif //OPTIMIZATION_ROBOT_LOCALIZATION_ROBOTINTERFACE_H
