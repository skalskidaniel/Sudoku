//
// Created by Daniel Skalski on 28/12/2024.
//

#ifndef SOLVER_H
#define SOLVER_H
#include <Board.h>
#include <Player.h>


class Solver : public Player {
    std::pair<std::pair<int, int>, char> takeTurn() override;

    // makes user input board
    Board inputBoardToComplete();

    // check if board given by the user is solvable
    bool isSolvable(const Board &b);

    // estimate difficulty of board given by the user
    int estimateDifficulty(const Board &b);

    // solve board given by the user
    Board solve(Board &b);
};



#endif //SOLVER_H
