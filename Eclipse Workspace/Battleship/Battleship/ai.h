/*
 * ai.h
 *
 *  Created on: Oct 20, 2020
 *      Author: Maxim Vovenko
 */

#ifndef BATTLESHIP_AI_H_
#define BATTLESHIP_AI_H_

int * aiPlayer(int board[10][10], int shots[10][10],bool lastShotHit,bool lastShotSank,int*returnR, int*returnC);



#endif /* BATTLESHIP_AI_H_ */
