//
// Created by Wiktor on 28/12/2024.
//

#include <CSP.h>

bool CSP::verify(int left, const std::string& op, int right) const {
    if (op == "=") return left == right;
    if (op == "!=") return left != right;
    if (op == "<") return left < right;
    if (op == "<=") return left <= right;
    if (op == ">") return left > right;
    if (op == ">=") return left >= right;
    return false;
}

void CSP::addVariable(const std::string& var, const std::vector<int>& domain) {
    assert(domains.find(var) == domains.end());
    domains[var] = std::unordered_set<int>(domain.begin(), domain.end());
}

void CSP::addBinaryConstraint(const std::string& var1, const std::string& op, const std::string& var2) {
    assert(domains.find(var1) != domains.end());
    assert(domains.find(var2) != domains.end());
    binaryConstraints.emplace_back(var1, op, var2);
}

bool CSP::isComplete(const std::unordered_map<std::string, int>& assignment) const{
    for (const auto& [var, domain] : domains) {
        if (assignment.find(var) == assignment.end()) {
            return false;
        }
    }
    return true;
}

bool CSP::isConsistent(const std::unordered_map<std::string, int>& assignment) const{
    for (const auto& [var, value] : assignment) {
        if (domains.at(var).find(value) == domains.at(var).end()) {
            return false;
        }
    }
    for (const auto& [var1, op, var2] : binaryConstraints) {
        if (assignment.find(var1) != assignment.end() && assignment.find(var2) != assignment.end()) {
            if (!verify(assignment.at(var1), op, assignment.at(var2))) {
                return false;
            }
        }
    }
    return true;
}

CSP CSP::sudokuToCSP(const std::string& puzzle) {
    CSP sudoku;
    std::string rows = "123456789";
    std::string cols = "123456789";

    for (char i : rows) {
        for (char j : cols) {
            int index = (i - '1') * 9 + (j - '1');
            char value = puzzle[index];

            if (value == '0') {
                sudoku.addVariable(std::string(1, i) + j, {1, 2, 3, 4, 5, 6, 7, 8, 9});
            } else {
                sudoku.addVariable(std::string(1, i) + j, {value - '0'});
            }
        }
    }

    for (char i : rows) {
        for (char j : cols) {
            std::string cell = std::string(1, i) + j;

            for (char k : cols) {
                if (k != j) {
                    sudoku.addBinaryConstraint(cell, "!=", std::string(1, i) + k);
                }
            }

            for (char k : rows) {
                if (k != i) {
                    sudoku.addBinaryConstraint(cell, "!=", std::string(1, k) + j);
                }
            }

            int startRow = (i - '1') / 3 * 3;
            int startCol = (j - '1') / 3 * 3;
            for (int k = 0; k < 3; ++k) {
                for (int l = 0; l < 3; ++l) {
                    char boxRow = '1' + startRow + k;
                    char boxCol = '1' + startCol + l;
                    if (boxRow != i || boxCol != j) {
                        sudoku.addBinaryConstraint(cell, "!=", std::string(1, boxRow) + boxCol);
                    }
                }
            }
        }
    }

    return sudoku;
}