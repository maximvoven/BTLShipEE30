/*
 * randomShip.cpp
 * Place for code to place random ships into ship array.
 *  Created on: Oct 19, 2020
 *      Author: Maxim Vovenko
 */
#include "randomShip.h"

//Function Must populate board with 5 ships and respective lengths.
//Ships are defined in board.h with names of type of ship and their lengths
//Notice int array if your placing battleship then board[r][c]=
void setupShipsR(int board[boardrows][boardcolumns]){
	int board1[10][10]={
			{0,0,0,0,0,0,0,0,0,0},
			{0,5,0,0,0,0,3,0,0,0},
			{0,5,0,0,0,0,3,0,0,0},
			{0,5,0,0,0,0,3,0,0,0},
			{0,5,0,0,0,0,0,0,0,0},
			{0,5,0,0,2,2,2,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,4,4,4,4,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,1,1,0,0}
		};
		for(int r=0;r<10;r++){
			for(int c=0;c<10;c++){
				board[r][c]=board1[r][c];
			}
		}
}
