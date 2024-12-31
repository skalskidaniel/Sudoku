//
// Created by Wiktor on 27/12/2024.
//

#ifndef ERRORTRACKER_H
#define ERRORTRACKER_H
#include <Board.h>



class ErrorTracker {
public:
    int maxErrors;

    int currentErrors;

    bool isGameOver;

    ErrorTracker(int maxErrors);

    
    bool validateMove(Board board, std::pair<std::pair<int, int>, char> move);



};



#endif //ERRORTRACKER_H
