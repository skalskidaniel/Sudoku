//
// Created by Daniel Skalski on 26/12/2024.
//

#include "Sudoku/include/Board.h"

void Board::resetBoard() {
  for (int i = 0; i < 9; ++i){
    for (int j = 0; j < 9; ++j){
      Board::currentState[i][j] = Board::initialState[i][j];
    }
  }
}