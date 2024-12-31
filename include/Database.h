//
// Created by Wiktor on 27/12/2024.
//

#ifndef DATABASE_H
#define DATABASE_H
#include <vector>
#include <Board.h>
#include <fstream>
#include <random>
#include <chrono>
#include <fstream>
#include <sstream>
#include <iostream>

class Database {
public:
    std::ifstream savedBoards;
    const int totalBoards = 14104;
    Board currentBoard;
    int currentBoardID;
    int bestScore;
    int currentErrors;
    bool canBeResumed;
    int difficulty;

    static Database& getInstance();

    void loadSavedState();

    void saveCurrentState(const Board &b, const int &currentBoardID, const int &difficulty, const int &currentErrors);
    void clearCurrentState();
    bool updateBestScore(const int &score);
    void loadChosenBoard(const int &boardID);

private:
    Database();
    ~Database() = default;

    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;
};


#endif //DATABASE_H
