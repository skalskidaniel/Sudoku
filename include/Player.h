//
// Created by Daniel Skalski on 28/12/2024.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <utility>


class Player {
    virtual std::pair<std::pair<int, int>, char> takeTurn() = 0;
};



#endif //PLAYER_H
