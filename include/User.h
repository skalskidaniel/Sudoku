//
// Created by Daniel Skalski on 28/12/2024.
//

#ifndef USER_H
#define USER_H
#include <string>
#include <Player.h>
#include <iostream>
#include <algorithm>
#include <Interface.h>


class User : public Player{
public:
    std::pair<std::pair<int, int>, char> takeTurn() override;

};



#endif //USER_H
