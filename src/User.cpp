//
// Created by Daniel Skalski on 28/12/2024.
//

#include <Interface.h>
#include <User.h>
#include <iostream>
#include <algorithm>

std::pair<std::pair<int, int>, char> User::takeTurn() {
    Interface& interface = Interface::getInstance();
    std::vector<char> rows = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    std::vector<int> cols = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<char> digits = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    std::cout << "Select row where you want to insert a digit (A-I):\t";
    char row = interface.getUserInputChar(rows);
    std::cout << "Select colum where you want to insert a digit (1-9):\t";
    int col = interface.getUserInputInt(cols);
    std::cout << "Which digit would you like to insert? (1-9):\t";
    char digit = interface.getUserInputChar(digits);

    auto rowIt = std::find(rows.begin(), rows.end(), row);
    auto colIt = std::find(cols.begin(), cols.end(), col);
    return {{std::distance(rows.begin(), rowIt), std::distance(cols.begin(), colIt)}, digit};
}
