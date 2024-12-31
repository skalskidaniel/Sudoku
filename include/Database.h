//
// Created by Wiktor on 27/12/2024.
//

#ifndef DATABASE_H
#define DATABASE_H
#include <vector>
#include <Board.h>
#include <fstream>

class Database {
public:
    std::ifstream savedBoards;
    const int totalBoards = 14104;
    Board currentBoard; // storing current state of a game in case we want stop for a while and resume later
    int bestScore;
    bool canBeResumed;
    int difficulty;

    static Database& getInstance();

    void loadSavedState();
    // structure of currentState.txt:
    // {int difficulty}
    // {int boardID}
    // {string currentBoardState}

    void saveCurrentState(const Board &b, const int &currentBoardID, const int &difficulty);
    bool updateBestScore(const int &score); // returns true if there is a new best score
    void loadChosenBoard(const int &boardID);

private:
    Database();
    ~Database() = default;

    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;
};


#endif //DATABASE_H
