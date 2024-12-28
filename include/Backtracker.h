//
// Created by Wiktor on 28/12/2024.
//

#ifndef BACKTRACKER_H
#define BACKTRACKER_H

#endif //BACKTRACKER_H

#include <unordered_map>
#include <unordered_set>
#include <CSP.h>

//TODO find the issue with ambigious CSP error

class Backtracker {
private:
    CSP& csp;
    int counter;
    std::unordered_map<std::string, int> assignment;

    std::string selectUnassignedVariable(const std::unordered_map<std::string, int>& assignment,
                                         const std::unordered_map<std::string, std::unordered_set<int>>& domains);

    std::unordered_map<std::string, std::unordered_set<int>> removeInconsistent(const std::unordered_map<std::string, int>& assignment);

    std::unordered_map<std::string, int> backtrack(std::unordered_map<std::string, int>& assignment);
public:
    Backtracker(CSP& csp);

    std::unordered_map<std::string, int> solve();

    int getCounter() const;
};