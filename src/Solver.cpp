//
// Created by Daniel Skalski on 28/12/2024.
//

#include <Solver.h>

bool Solver::isTurnValid(Board &b, int &row, int &col, int &digit) {
    char num = '0' + digit;

    for (int x = 0; x < 9; x++) {
        if (b.currentState[row][x] == num) {
            return false;
        }
    }

    for (int x = 0; x < 9; x++) {
        if (b.currentState[x][col] == num) {
            return false;
        }
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (b.currentState[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}


std::pair<bool, Board> Solver::solve(Board &b) {
    int row = -1, col = -1;
    bool isEmpty = false;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (b.currentState[i][j] == '0') {
                row = i;
                col = j;
                isEmpty = true;
                break;
            }
        }
        if (isEmpty) break;
    }

    if (!isEmpty) return {true, b};

    for (int num = 1; num <= 9; num++) {
        if (isTurnValid(b, row, col, num)) {
            b.currentState[row][col] = '0' + num;
            auto result = solve(b);
            if (result.first) return result;
            b.currentState[row][col] = '0';
        }
    }

    return {false, b};
}

std::pair<std::pair<int, int>, char> Solver::takeTurn() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (solvedBoard.currentState[i][j] == '0') {
                char digit = solvedBoard.currentState[i][j];
                return {{i, j}, digit};
            }
        }
    }
}

Board Solver::inputBoardToComplete() {
    Board b;

    for (int i = 0; i < 9; ++i) {
        std::string row;
        while (true) {
            std::cout << "Row " << i + 1 << ": ";
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
            b.initialState[i][j] = row[j];
            b.currentState[i][j] = row[j];
            b.solvedState[i][j] = row[j];
        }
    }

    return b;
}
