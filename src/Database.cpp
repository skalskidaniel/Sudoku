//
// Created by Daniel Skalski on 27/12/2024.
//

#include "Database.h"
#include <random>
#include <chrono>
#include <fstream>
#include <sstream>
#include <iostream>

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

    // Move to the specific line
    savedBoards.seekg(std::ios::beg);
    for (int i = 0; i < boardID; ++i) {
        savedBoards.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Read the specific line
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
        loadChosenBoard(boardID);

        std::string line;
        currentStateFile >> line;
        currentBoard.updateCurrentState(line);
        canBeResumed = true;
    } else {
        // there is no saved state in file
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
        // there is no best score in file
        bestScore = 0;
    }
}

void Database::saveCurrentState(const Board &b, const int &currentBoardID, const int &difficulty) {
    currentBoard = b;
    this->difficulty = difficulty;
    std::ofstream outputFile("../saves/currentState.txt");
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
    // returns true if there is new best score
    if (score > bestScore) {
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

