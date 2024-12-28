//
// Created by Wiktor on 27/12/2024.
//

#ifndef DATABASE_H
#define DATABASE_H
#include <vector>
#include <Board.h>

class Database {
public:
    // storing {DIFFICULTY, Board}
    // DIFFICULTY IN [1, 2, 3]
    std::vector<std::pair<int, Board>> savedBoards;
    // storing current state of a game in case we want stop for a while and resume later
    Board currentBoard;
    // best score so far
    int bestScore;


    Database();

    void loadBoards();

    void loadSavedState();

    void addBoard(const std::string &initialState, const std::string &solutionState);

    void saveCurrentState(const Board &b, const int &currentBoardID);

    // returns true if there is a new best score
    bool updateBestScore(const int &score);

};


#endif //DATABASE_H
