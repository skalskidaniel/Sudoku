//
// Created by Wiktor on 27/12/2024.
//

#ifndef MANAGER_H
#define MANAGER_H
#include <ErrorTracker.h>
#include <Timer.h>
#include <Hinter.h>


class Manager {
public:
    ErrorTracker errorTracker;
    Timer timer;
    Hinter hinter;

    Manager(int maxErrors);
};



#endif //MANAGER_H
