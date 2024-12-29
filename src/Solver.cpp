//
// Created by Daniel Skalski on 28/12/2024.
//

#include <Solver.h>
#include <CSP.h>
#include <Backtracker.h>

//TODO implement isSolvable with timer waiting for the result of the backtracker if some time is exceeded return false
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
    return backtracker.solve().size() > 0;
}

std::pair<std::pair<int, int>, char> Solver::takeTurn() {
    // TODO
}

Board Solver::inputBoardToComplete() {
    // TODO
}
