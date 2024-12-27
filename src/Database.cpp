//
// Created by Wiktor on 27/12/2024.
//

#include "Sudoku/include/database.h"
#include <fstream>

database::database() {
    bestScore = 0;
    last_id = 0;
    load_data();
}


void database::load_data() {
    std::ifstream file("Sudoku/data.csv");
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
        boards[last_id++] = std::make_pair(board, solution);
    }
}

void database::add_board(std::string board, std::string solution) {
    boards[last_id++] = std::make_pair(board, solution);
}