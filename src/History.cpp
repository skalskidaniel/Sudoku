//
// Created by Wiktor on 27/12/2024.
//

#include "History.h"


History::History() = default;

bool History::canUndo() {
    if (previousBoards.size() > 0) return true;
    return false;
}


Board History::undo(Board &newPreviousBoard) {
    if (canUndo()) {
        auto prev = previousBoards.top();
        previousBoards.pop();
        previousBoards.push(newPreviousBoard);

        return prev;
    } else {
        throw std::runtime_error("Can not undo - there are no more previous states stored");
    }

}

void History::update(Board &board) {
    if (previousBoards.size() == 10) {
        std::stack<Board> tempStack;
        while (previousBoards.size() > 1) {
            tempStack.push(previousBoards.top());
            previousBoards.pop();
        }
        previousBoards.pop();
        while (!tempStack.empty()) {
            previousBoards.push(tempStack.top());
            tempStack.pop();
        }
    }
    previousBoards.push(board);
}