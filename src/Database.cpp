//
// Created by Daniel Skalski on 27/12/2024.
//

#include "Database.h"
#include <fstream>
#include <sstream>

Database::Database() : currentState(Board()), bestScore(0) {
    loadData();
}

void Database::loadData() {
    std::ifstream file("saves/boards.csv");

    if (!file.is_open()) {
        throw std::runtime_error("Failed to load saved boards!");
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string initialState, solvedState;

        std::getline(ss, initialState, ';');
        std::getline(ss, solvedState);

        Board b(initialState, solvedState);
        // TODO
        // dodac poziomy trudnosci zmaiast zawsze 1
        savedBoards.emplace_back(1, b);

    }

}

void Database::addBoard(const std::string &initialState, const std::string &solutionState) {
    // let the user to add a board to the database
    Board b(initialState, solutionState);
    // TODO
    // estimate difficulty
    savedBoards.emplace_back(1, b);
}

void Database::saveCurrentState(const Board &b) {
    currentState = b;
}

bool Database::updateBestScore(const int &score) {
    if (score > bestScore) {
        bestScore = score;
        return true;
    }
    return false;
}

