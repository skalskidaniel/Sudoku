//
// Created by Wiktor on 27/12/2024.
//

#ifndef DATABASE_H
#define DATABASE_H
#include <vector>
#include <Board.h>

class Database {
public:
    // storing {DIFFICULTY, {initialState, solution} }
    std::vector<int, std::pair<Board, Board>> savedBoards;
    // storing current state of a game in case we want stop for a while and resume later
    Board currentState;
    // best score so far
    int bestScore;

    Database();

    void loadData();

    void addBoard(std::string board, std::string solution);
};


#endif //DATABASE_H
