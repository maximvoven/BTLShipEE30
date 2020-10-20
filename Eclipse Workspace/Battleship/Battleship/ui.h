/*
 * ui.h
 *
 *  Created on: Oct 19, 2020
 *      Author: Maxim Vovenko
 */

#ifndef BATTLESHIP_UI_H_
#define BATTLESHIP_UI_H_

void displayText(char text[],int len);
void clearScreen();

//TODO Figure out how to reference board.h boardcolumns and boardrows directly from header file!
void displayShips(int board[10][10]);
void displayShots(int board[10][10]);


#endif /* BATTLESHIP_UI_H_ */
