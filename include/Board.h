//
// Created by Daniel Skalski on 26/12/2024.
//

#ifndef BOARD_H
#define BOARD_H
#include <string>


class Board {
public:
    char initialState[9][9];
    std::string originalString;

    char currentState[9][9];

    char solvedState[9][9];

    // default constructor with null values
    Board();

    // constructor allows to convert pure string into Board object
    Board(const std::string &original, const std::string &solved);

    void resetBoard();

    // used when reading current state from saved file
    void updateCurrentState(const std::string &state);

    Board& operator=(const Board &other);

    bool isInsertedByUser(const int &i, const int &j);

    bool isSolved();

};



#endif //BOARD_H
