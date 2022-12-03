//
// Created by pi on 02.12.2022.
//

#ifndef OPTIMIZATION_ROBOT_LOCALIZATION_INTERACTIONHELPER_H
#define OPTIMIZATION_ROBOT_LOCALIZATION_INTERACTIONHELPER_H

#include "../include/Control.h"

struct QueryResult{

    QueryResult(): success(false) {}

    explicit operator bool () const {
        return success;
    }

    Control::Command get() const{
        return command;
    }

    bool success;
    Control::Command command{};
};

class InteractionHelper {
public:

    static void printShortGuide();

    static QueryResult getCommand();
};


#endif //OPTIMIZATION_ROBOT_LOCALIZATION_INTERACTIONHELPER_H
