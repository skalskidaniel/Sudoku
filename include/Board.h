//
// Created by Daniel Skalski on 26/12/2024.
//

#ifndef BOARD_H
#define BOARD_H
#include <string>


class Board {
public:
    char initialState[9][9];

    char currentState[9][9];

    char solvedState[9][9];

    Board();

    Board(const std::string &original, const std::string &solved);

    void resetBoard();

    void updateCurrentState(const std::string &state);

    Board& operator=(const Board &other);

    bool isInsertedByUser(const int &i, const int &j);

    bool isSolved();

};



#endif //BOARD_H
