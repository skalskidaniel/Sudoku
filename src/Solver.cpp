//
// Created by Daniel Skalski on 28/12/2024.
//

#include <Solver.h>
#include <CSP.h>
#include <Backtracker.h>
#include <iostream>

//TODO fix ambigous CSP error

Board Solver::solve(Board &b) {
    CSP csp = CSP.sudokuToCSP(b.currentState);
    Backtracker backtracker(csp);
    auto solution = backtracker.solve();
    for (const auto& [var, value] : solution) {
        int row = (var[0] - '1') / 3;
        int col = (var[1] - '1') / 3;
        b.currentState[row][col] = value;
    }
    return b;
}

bool Solver::isSolvable(const Board &b) {
    CSP csp = CSP.sudokuToCSP(b.currentState);
    Backtracker backtracker(csp);
    std::unordered_map<std::string,int> solution = backtracker.solve();
    return !solution.empty();
}

std::pair<std::pair<int, int>, char> Solver::takeTurn() {
    Board b = inputBoardToComplete();
    Board toSolve = b;
    if (!isSolvable(toSolve)) {
        return {{-1, -1}, '0'};
    }
    if(!is_solved){
        solvedBoard = solve(toSolve);
        is_solved = true;
    }
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (b.currentState[i][j] == '0') {
                return {{i, j}, solvedBoard.currentState[i][j]};
            }
        }
    }
}

Board Solver::inputBoardToComplete() {
    Board b;

    std::cout << "Please input your own sudoku board.\n";
    std::cout << "You will have to write each line one by one.\n";
    std::cout << "Places with missing digit mark as '0'.\n";
    std::cout << "Solver will check whether it is solvable, and solve if it is so.\n";

    for (int i = 0; i < 9; ++i) {
        std::string row;
        while (true) {
            std::cout << "Row " << i << ": ";
            std::cin >> row;
            if (row.length() != 9) {
                std::cout << "Error: Each row must be exactly 9 characters long.\n";
                continue;
            }
            bool valid = true;
            for (char c : row) {
                if (c < '0' || c > '9') {
                    std::cout << "Error: Each character must be a digit between 0 and 9.\n";
                    valid = false;
                    break;
                }
            }
            if (valid) break;
        }
        for (int j = 0; j < 9; ++j) {
            b.currentState[i][j] = row[j];
        }
    }
    return b;
}
