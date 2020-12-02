/*
 * ai.h
 *
 *  Created on: Oct 20, 2020
 *      Author: Maxim Vovenko
 */

#ifndef BATTLESHIP_AI_H_
#define BATTLESHIP_AI_H_

#include "board.h"

void aiPlayer(board Board, aiMemory *memory, int shot[2]);
void easyAiPlayer(int out[2]);

#endif /* BATTLESHIP_AI_H_ */
