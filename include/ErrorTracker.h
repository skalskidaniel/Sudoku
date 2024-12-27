//
// Created by Wiktor on 27/12/2024.
//

#ifndef ERRORTRACKER_H
#define ERRORTRACKER_H
#include "Board.h"



class ErrorTracker {
private:
    int maxErrors;

public:
    ErrorTracker(int maxErrors);

    int currentError;

    bool isGameOver;

    bool validateMove(Board board, Board solution, char mode);



};



#endif //ERRORTRACKER_H
