//
// Created by Daniel Skalski on 27/12/2024.
//

#include "Database.h"
#include <fstream>
#include <sstream>

Database::Database() {
    loadBoards();
    loadSavedState();
}

void Database::loadBoards() {
    std::ifstream boardsFile("../saves/boards.csv");

    if (!boardsFile.is_open()) {
        throw std::runtime_error("Failed to load saved boards!");
    }

    std::string line;
    while (std::getline(boardsFile, line)) {
        std::stringstream ss(line);
        std::string initialState, solvedState;

        std::getline(ss, initialState, ';');
        std::getline(ss, solvedState);

        Board b(initialState, solvedState);

        savedBoards.emplace_back(b);

    }

    boardsFile.close();
}

void Database::loadSavedState() {
    std::ifstream currentStateFile("../saves/currentState.txt");
    if (!currentStateFile.is_open()) {
        throw std::runtime_error("Failed to load saved state of the board!");
    }
    if (currentStateFile.peek() != std::ifstream::traits_type::eof()) {
        currentStateFile >> difficulty;

        int boardID;
        currentStateFile >> boardID;
        currentBoard = savedBoards.at(boardID);

        std::string line;
        currentStateFile >> line;
        currentBoard.updateCurrentState(line);
        canBeResumed = true;
    } else {
        currentBoard = Board();
        canBeResumed = false;
    }

    currentStateFile.close();
    std::ifstream bestScoreFile("../saves/bestScore.txt");
    if (!bestScoreFile.is_open()) {
        throw std::runtime_error("Failed to load saved best score!");
    }

    if (bestScoreFile.peek() != std::ifstream::traits_type::eof()) {
        bestScoreFile >> bestScore;
    } else {
        bestScore = 0;
    }
}


void Database::addBoard(const std::string &initialState, const std::string &solutionState) {
    // let the user to add a board to the database
    Board b(initialState, solutionState);
    savedBoards.emplace_back(b);
}

void Database::saveCurrentState(const Board &b, const int &currentBoardID) {
    currentBoard = b;
    std::ofstream outputFile("saves/currentState.txt");
    if (!outputFile.is_open()) {
        throw std::runtime_error("Failed to save current state of the game!");
    }
    outputFile << difficulty << std::endl;
    outputFile << currentBoardID << std::endl;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            outputFile << b.currentState[i][j];
        }
    }
    outputFile.close();
}

bool Database::updateBestScore(const int &score) {
    if (score > bestScore) {
        bestScore = score;
        std::ofstream outputFile("saves/bestScore.txt", std::ios::trunc);
        if (!outputFile.is_open()) {
            throw std::runtime_error("Failed to save best score to a file!");
        }
        outputFile << score;
        return true;
    }
    return false;
}

