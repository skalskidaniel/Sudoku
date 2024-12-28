//
// Created by Daniel Skalski on 26/12/2024.
//

#ifndef BOARD_H
#define BOARD_H



class Board {
private:
    char initialState[9][9];

    char solvedState[9][9];

public:
    char currentState[9][9];
    // default constructor with null values
    Board();

    // constructor allows to convert pure string into Board object
    Board(const std::string &original, const std::string &solved);

    void resetBoard();

    // used when reading current state from saved file
    void updateCurrentState(const std::string &state);

};



#endif //BOARD_H
