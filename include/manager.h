//
// Created by Wiktor on 27/12/2024.
//

#ifndef MANAGER_H
#define MANAGER_H
#include "Sudoku/include/ErrorTracker.h"
#include "Sudoku/include/Timer.h"
#include "Sudoku/include/History.h"
#include "Sudoku/include/hinter.h"


class manager {
public:
    ErrorTracker errorTracker;
    Timer timer;
    History history;
    hinter hinter;
    manager(int maxErrors);
};



#endif //MANAGER_H
