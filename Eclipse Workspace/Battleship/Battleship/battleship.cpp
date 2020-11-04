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
#include "ai.h"

#define DEBUG 1

static void debugPrintArray(int array[10][10]);
static bool isValidRC(int r,int c);
static bool isHit(int board[10][10], int r, int c);

struct gameBoard{
	int board[10][10];
	int shots[10][10];
	bool ShotHit;
	bool ShipSunk;
};
typedef struct gameBoard board;

void launchBattlehip(){
	setbuf(stdout,NULL);
	bool gameEnd=false;
	board player1={{},{},false,false};
	board player2={{},{},false,false};
	int board0[10][10]={};
	int board1[10][10]={};
	int shots0[10][10]={};
	int shots1[10][10]={};
	bool aiHit0=false,aiSank0=false,aiHit1=false,aiSank1=false;
	int tempr,tempc, gameMode=0;

	setupShipsR(board0);
	setupShipsR(board1);

	while(!gameEnd){
		//Player Code

		clearScreen();
		displayShots(shots0);
		displayShips(board0);
		if(DEBUG){
			printf("Player 1 Shots");
			debugPrintArray(shots0);
			printf("Player 1 Board");
			debugPrintArray(board0);
		}
		if(gameMode>=1){
		printf("Enter Firing Coordinates (Letter Number):\n");
		do{
			char r;
			scanf("%c%d", &r,&tempc);
			tempr=tolower(r)-97;
		}while(!isValidRC(tempr, tempc));
		} else {
			printf("Ai Player0 Is Thinking ... ");
			aiPlayer(board0, shots0, aiHit1, aiSank1, &tempr, &tempc);
			printf("%c%d\n",tempr+97,tempc);
		}
		//Shot Logic Player0
		if(isHit(board1, tempr, tempc)){
			board1[tempr][tempc]=board1[tempr][tempc]*-1;
			shots0[tempr][tempc]=hit;
		} else {
			shots0[tempr][tempc]=miss;
		}

		printf("Ai Player Is Thinking ... ");
		aiPlayer(board1, shots1, aiHit0, aiSank0, &tempr, &tempc);
		printf("%c%d\n",tempr+97,tempc);

		//Shot Logic Player1 or AI
		if(isHit(board0, tempr, tempc)){
			board0[tempr][tempc]=board0[tempr][tempc]*-1;
			shots1[tempr][tempc]=hit;
			aiHit0=true;
		} else {
			shots1[tempr][tempc]=miss;
			aiHit0=false;
		}
		if(DEBUG){
			printf("Player 2 Shots");
			debugPrintArray(shots1);
			printf("Player 2 Board");
			debugPrintArray(board1);
			printf("Hit: %d\n",aiHit0);
		}
		printf("Press Any Key to Start Next Turn");
		getchar();
		getchar();

	}


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
	if(board[r][c]!=0){
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
				if(array[r][c]==0){
					printf("  ");
				}
				else printf(" %d",array[r][c]);
			} else {
				printf("%d",array[r][c]);
			}
		}
		printf(" |\n");
	}
	printf("-----------------------\n");
}
