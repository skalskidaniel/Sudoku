//
// Created by Wiktor on 28/12/2024.
//

#ifndef CSP_H
#define CSP_H


#include <unordered_map>
#include <unordered_set>
#include <cassert>

class CSP {
public:
    std::unordered_map<std::string, std::unordered_set<int>> domains;
    std::vector<std::tuple<std::string, std::string, std::string>> binaryConstraints;

    bool verify (int left, const std::string& op, int right) const;

    void addVariable(const std::string& var, const std::vector<int>& domain);
    void addBinaryConstraint(const std::string& var1, const std::string& op, const std::string& var2);
    bool isConsistent(const std::unordered_map<std::string, int>& assignment) const;
    bool isComplete(const std::unordered_map<std::string, int>& assignment) const;
    CSP sudokuToCSP(const std::string& puzzle);
};

#endif //CSP_H