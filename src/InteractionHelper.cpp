//
// Created by pi on 02.12.2022.
//
#include <iostream>

#include "../include/InteractionHelper.h"

using namespace std;

QueryResult InteractionHelper::getCommand() {
    char choice;
    QueryResult res{};
    cout << "Type q for exit or p to proceed..." << endl;
    cin >> choice;
    if (choice == 'q') return res;
    Control::Command command{};
    cout << "Please choose the direction from (1, 1), (-1, 1), (-1, -1), (1, -1). Input example: 1 1" << endl;
    cin >> command.direction[0] >> command.direction[1];
    cout << "Direction chosen: (" << command.direction[0] << ", " << command.direction[1] << ")\n";
    cout << "Please choose the distance of move. Input example: 10.25" << endl;
    cin >> command.distance;
    cout << "Distance chosen: " << command.distance << endl;
    res.success = true;
    res.command = command;
    return res;
}