//
// Created by Wiktor on 28/12/2024.
//

#include <Backtracker.h>

Backtracker::Backtracker(CSP &csp) : csp(csp), counter(0) {}

std::unordered_map<std::string, int> Backtracker::solve() {
    counter = 0;
    assignment.clear();
    start_time = std::chrono::steady_clock::now();
    return backtrack(assignment);
}

bool Backtracker::isTimeExceeded() const {
	auto now = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start_time).count();
	return elapsed > 15;
}

std::string Backtracker::selectUnassignedVariable(const std::unordered_map<std::string, int> &assignment,
                                                  const std::unordered_map<std::string, std::unordered_set<int>> &domains) {
    std::string bestVar;
    int minDomainSize = std::numeric_limits<int>::max();
    int maxDegree = -1;

    for (const auto& [var, domain] : csp.domains) {
        if (assignment.find(var) != assignment.end()) continue;

        int degree = 0;
        for (const auto& [var1, op, var2] : csp.binaryConstraints) {
            if ((var1 == var && assignment.find(var2) == assignment.end()) ||
                (var2 == var && assignment.find(var1) == assignment.end())) {
                ++degree;
                }
        }

        int domainSize = domains.at(var).size();
        if (domainSize < minDomainSize ||
            (domainSize == minDomainSize && degree > maxDegree)) {
            bestVar = var;
            minDomainSize = domainSize;
            maxDegree = degree;
            }
    }
    return bestVar;
}

std::unordered_map<std::string, std::unordered_set<int>> Backtracker::removeInconsistent(const std::unordered_map<std::string, int>& assignment) {
    auto domainsCopy = csp.domains;

    for (const auto& [var, value] : assignment) {
        domainsCopy[var] = {value};
    }

    for (const auto& [var1, op, var2] : csp.binaryConstraints) {
        if (assignment.find(var1) != assignment.end() && assignment.find(var2) != assignment.end()) continue;

        if (assignment.find(var1) != assignment.end()) {
            for (auto it = domainsCopy[var2].begin(); it != domainsCopy[var2].end();) {
                if (!csp.verify(assignment.at(var1), op, *it)) {
                    it = domainsCopy[var2].erase(it);
                } else {
                    ++it;
                }
            }
        } else if (assignment.find(var2) != assignment.end()) {
            for (auto it = domainsCopy[var1].begin(); it != domainsCopy[var1].end();) {
                if (!csp.verify(*it, op, assignment.at(var2))) {
                    it = domainsCopy[var1].erase(it);
                } else {
                    ++it;
                }
            }
        }
    }
    return domainsCopy;
}

std::unordered_map<std::string, int> Backtracker::backtrack(std::unordered_map<std::string, int> &assignment) {
    if (isTimeExceeded()) {
        return {};
    }

  	if (csp.isComplete(assignment) && csp.isConsistent(assignment)) {
        return assignment;
    }

    auto domains = removeInconsistent(assignment);
    std::string var = selectUnassignedVariable(assignment, domains);

    for (int value : domains[var]) {
        assignment[var] = value;

        if (csp.isConsistent(assignment)) {
            auto result = backtrack(assignment);
            if (!result.empty()) {
                ++counter;
                return result;
            }
        }

        assignment.erase(var);
    }
    return {};
}

int Backtracker::getCounter() const {
    return counter;
}

