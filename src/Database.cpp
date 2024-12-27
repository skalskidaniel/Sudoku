//
// Created by Wiktor on 27/12/2024.
//

#include "Database.h"
#include <fstream>

Database::Database() {
    bestScore = 0;
    loadData();
}

void Database::loadData() {
    // TODO
    // zapisane tablice musza byc wpisywane jako klasa Board a nie string
    std::ifstream file("saves/boards.csv");

    if (!file.is_open()) {
        throw std::runtime_error("Failed to load saved boards!");
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        std::string board = "";
        std::string solution = "";
        int i = 0;
        while(line[i] != ';') {
            if (line[i++] == ';') {
                break;
            }
            board += line[i++];
        }
        while(i < line.size()) {
            solution += line[i++];
        }
        savedBoards.push_back({board, solution});
    }
}

