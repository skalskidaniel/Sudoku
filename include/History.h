//
// Created by Wiktor on 27/12/2024.
//

#ifndef HISTORY_H
#define HISTORY_H
#include "Board.h"

class History {
public:
    Board previous;

    void undo(Board board);
};



#endif //HISTORY_H
