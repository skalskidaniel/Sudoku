//
// Created by Daniel Skalski on 27/12/2024.
//

#include <Database.h>

Database::Database() : savedBoards("../saves/boards.csv") {
    loadSavedState();
}

Database& Database::getInstance() {
    static Database instance;
    return instance;
}

void Database::loadChosenBoard(const int &boardID) {
    if (!savedBoards.is_open()) {
        throw std::runtime_error("Could not open boards.csv");
    }

    savedBoards.seekg(std::ios::beg);
    for (int i = 0; i < boardID; ++i) {
        savedBoards.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::string line;
    std::getline(savedBoards, line);

    std::istringstream ss(line);
    std::string initialState, solutionState;
    std::getline(ss, initialState, ';');
    std::getline(ss, solutionState);

    currentBoard = Board(initialState, solutionState);
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
        currentBoardID = boardID;
        loadChosenBoard(boardID);

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
    bestScoreFile.close();

    std::ifstream currentErrorsFile("../saves/currentErrors.txt");
    if (!currentErrorsFile.is_open()) {
        throw std::runtime_error("Failed to load saved current errors!");
    }
    if (currentErrorsFile.peek() != std::ifstream::traits_type::eof()) {
        bestScoreFile >> currentErrors;
    } else {
        currentErrors = 0;
    }
    currentErrorsFile.close();
}

void Database::saveCurrentState(const Board &b, const int &currentBoardID, const int &difficulty, const int &currentErrors) {
    currentBoard = b;
    this->difficulty = difficulty;
    std::ofstream currentStateFile("../saves/currentState.txt", std::ios::trunc);
    if (!currentStateFile.is_open()) {
        throw std::runtime_error("Failed to save current state of the game!");
    }
    currentStateFile << difficulty << std::endl;
    currentStateFile << currentBoardID << std::endl;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            currentStateFile << b.currentState[i][j];
        }
    }
    currentStateFile.close();

    std::ofstream currentErrorsFile("../saves/currentErrors.txt", std::ios::trunc);
    if (!currentErrorsFile.is_open()) {
        throw std::runtime_error("Failed to save current errors from the game!");
    }
    currentErrorsFile << currentErrors;
    currentErrorsFile.close();
    this->currentErrors = currentErrors;
}

bool Database::updateBestScore(const int &score) {
    // returns true if there is new best score
    if (score < bestScore) {
        bestScore = score;
        std::ofstream outputFile("../saves/bestScore.txt", std::ios::trunc);
        if (!outputFile.is_open()) {
            throw std::runtime_error("Failed to save best score to a file!");
        }
        outputFile << score;
        return true;
    }
    return false;
}

void Database::clearCurrentState() {
    std::ofstream outputFile("../saves/currentState.txt", std::ios::trunc);
    if (!outputFile.is_open()) {
        throw std::runtime_error("Failed to clear current state of the game!");
    }
    outputFile.close();
    currentBoard = Board();
    canBeResumed = false;
}