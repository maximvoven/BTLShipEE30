/*
 * board.h
 *
 *  Created on: Oct 19, 2020
 *      Author: Maxim Vovenko
 */

#ifndef BATTLESHIP_BOARD_H_
#define BATTLESHIP_BOARD_H_

//Do not change boardw boardl from value 10
#define boardrows 10
#define boardcolumns 10

#define hit -1
#define miss 1

#define carrier 5
#define carrierL 5
#define battleship 4
#define battleshipL 4
#define cruiser 3
#define cruiserL 3
#define submarine 2
#define submarineL 3
#define destroyer 1
#define destroyerL 2

struct gameBoard{
	int board[10][10];
	int shots[10][10];
	bool ShotHit;
	bool ShipSunk;
};

struct gameShotHistory{
	int firstShot[2];
	int secondShot[2];
	int searchState;
	int searchInProgress;
};

typedef struct gameBoard board;
typedef struct gameShotHistory aiMemory;

#endif /* BATTLESHIP_BOARD_H_ */
