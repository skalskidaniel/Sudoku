//
// Created by Wiktor on 27/12/2024.
//

#ifndef DATABASE_H
#define DATABASE_H
#include <vector>
#include <Board.h>

class Database {
public:
    std::vector<Board> savedBoards;
    // storing current state of a game in case we want stop for a while and resume later
    Board currentBoard;
    // best score so far
    int bestScore;

    bool canBeResumed;

    int difficulty;

    Database();

    void loadBoards();

    void loadSavedState();
    // structure of currentState.txt:
    // {int difficulty}
    // {int boardID}
    // {string currentBoardState}

    void addBoard(const std::string &initialState, const std::string &solutionState);

    void saveCurrentState(const Board &b, const int &currentBoardID);

    // returns true if there is a new best score
    bool updateBestScore(const int &score);

};


#endif //DATABASE_H
