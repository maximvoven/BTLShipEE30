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
#include <time.h>
#include <ctype.h>

#include "battleship.h"
#include "randomShip.h"
#include "ui.h"

static void debugPrintArray(int array[10][10]);
static bool isValidRC(int r,int c);
static bool isHit(int board[10][10], int r, int c)

void launchBattlehip(){
	bool gameEnd=false;
	int board0[10][10]={};
	int board1[10][10]={};
	int shots0[10][10]={};
	int shots1[10][10]={};

	setupShipsR(board0);
	setupShipsR(board1);

	while(!gameEnd){
		//Player Code
		int tempr0,tempc0;
		clearScreen();
		displayShots(shots0);
		displayShips(board0);
		printf("Enter Firing Coordinates (Letter Number):\n");
		do{
			int r;
			scanf("%c%d", &r,tempc0);
			tempr0=tolower(r)-97;
		}while(!isValidRC(tempr0, tempc0));
		//Shot Logic Player
		if(isHit(board1, tempr0, tempc0)){
			board1[tempr0][tempc0]=board1[tempr0][tempc0]*-1;
			shots0[tempr0][tempc0]=hit;
		} else {
			shots0[tempr0][tempc0]=miss;
		}




	}

	debugPrintArray(board1);

	exit(EXIT_FAILURE);
}

static bool isValidRC(int r,int c){
	if(r>=0 && r<10){
		if(c>=0 &&c<10){
			return true;
		}
	}
	return false;
}

static bool isHit(int board[10][10], int r, int c){
	if(board[r][c]>0){
		return true;
	}
	return false;
}

static void debugPrintArray(int array[10][10]){
	printf("\n-----------------------\n");
	for(int r=0;r<10;r++){
		printf("|");
		for(int c=0;c<10;c++){
			if(array[r][c]>=0){
				printf(" %d",array[r][c]);
			} else {
				printf("%d",array[r][c]);
			}
		}
		printf(" |\n");
	}
	printf("-----------------------\n");
}
