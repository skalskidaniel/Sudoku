//
// Created by Daniel Skalski on 28/12/2024.
//

#ifndef SOLVER_H
#define SOLVER_H
#include <Board.h>
#include <Player.h>

class Solver : public Player {
public:
    Board solvedBoard;

    std::pair<std::pair<int, int>, char> takeTurn() override;

    // makes user input board
    Board inputBoardToComplete();

    // solve board given by the user
    std::pair<bool, Board> solve(Board &b);
private:
    bool isTurnValid(Board &b, int &row, int &col, int &digit);
};



#endif //SOLVER_H
