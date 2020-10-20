/*
 * battleship.cpp
 *
 * Contains Core Code for Controlling Game And is launchpoint for game
 *
 *  Created on: Oct 19, 2020
 *      Author: Maxim Vovenko
 */
#include <stdlib.h>
#include <stdio.h>

#include "battleship.h"
#include "randomShip.h"
#include "ui.h"

void launchBattlehip(){
	printf("This Is Battleship");
	int array[10][10];
	setupShipsR(array);
	printf("This Is Battleship");
	exit(EXIT_FAILURE);
}
