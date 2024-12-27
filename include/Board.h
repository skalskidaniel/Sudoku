//
// Created by Daniel Skalski on 26/12/2024.
//

#ifndef BOARD_H
#define BOARD_H



class Board {
private:
  char initialState[9][9];
public:
  char currentState[9][9];

  Board();

  void resetBoard();

};



#endif //BOARD_H
