//
// Created by Wiktor on 27/12/2024.
//

#include "History.h"


Board History::undo(Board &board) {
    auto prev = previousBoard;
    previousBoard = board;

    return prev;
}