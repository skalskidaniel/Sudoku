//
// Created by Wiktor on 27/12/2024.
//

#ifndef ERRORTRACKER_H
#define ERRORTRACKER_H
#include "Board.h"



class ErrorTracker {
public:
    int currentError;
    bool isGameOver;
    bool validateMove(Board board, Board solution, char mode);
    ErrorTracker(int maxErrors);
private:
    int maxErrors;
};



#endif //ERRORTRACKER_H
