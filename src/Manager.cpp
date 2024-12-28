//
// Created by Wiktor on 27/12/2024.
//

#include "Manager.h"

Manager::Manager(int maxErrors) : errorTracker(ErrorTracker(maxErrors)), timer(Timer()), history(History()), hinter(Hinter()) {}