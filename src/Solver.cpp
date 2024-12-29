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
    std::cout << "Input your board to complete:\n";
    for (int i = 0; i < 9; ++i) {
        std::string row;
        std::cin >> row;
        for (int j = 0; j < 9; ++j) {
            b.currentState[i][j] = row[j];
        }
    }
    return b;
}

