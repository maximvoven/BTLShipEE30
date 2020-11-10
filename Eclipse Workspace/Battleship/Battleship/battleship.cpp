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

static void debugState(board Board, aiMemory ai);
static bool isValidRC(int r,int c);
static bool isHit(int board[10][10], int r, int c);

void launchBattlehip(){
	setbuf(stdout,NULL);
	bool gameEnd=false;
	board player1={{},{},false,false};
	board player2={{},{},false,false};
	//We Initialize Memory of Both Ai Engines
	aiMemory ai1={{-1,-1},{-1,-1},0,0};
	aiMemory ai2={{-1,-1},{-1,-1},0,0};
	int shot[2]={}, gameMode=0; //gamemode 0=ai v ai, 1=human vs ai, 2=human v human

	setupShipsR(player1.board);
	setupShipsR(player2.board);

	while(!gameEnd){
		//Player Code

		clearScreen();
		displayShots(player1.shots);
		displayShips(player1.board);

		if(DEBUG){
			printf("Player 1");
			debugState(player1, ai1);
		}
		//Ai Vs Human Player, Selected by game mode
		if(gameMode>=1){
//			printf("Enter Firing Coordinates (Letter Number):\n");
//			do{
//				char r;
//				scanf("%c%d", &r,&shot[1]);
//				shot[0]=tolower(r)-97;
//			}while(!isValidRC(shot[0], shot[1]));
		} else {
			printf("Ai 1 Is Thinking ... ");
			aiPlayer(player1, &ai1, shot);
			printf("%c%d\n",shot[0]+97,shot[1]);
		}

		//Shot Logic Player1
		if(isHit(player2.board, shot[0], shot[1])){
			player2.board[shot[0]][shot[1]]=player2.board[shot[0]][shot[1]]*-1;
			player1.shots[shot[0]][shot[1]]=hit;
			player1.ShotHit=true;
		} else {
			player1.shots[shot[0]][shot[1]]=miss;
			player1.ShotHit=false;
		}


		if(DEBUG){
			printf("Ai 2");
			debugState(player2,ai2);
		}

		printf("Ai 2 Is Thinking ... ");
		aiPlayer(player2, &ai2, shot);
		printf("%c%d\n",shot[0]+97,shot[1]);

		//Shot Logic Player2 or AI
		if(isHit(player1.board, shot[0], shot[1])){
			player1.board[shot[0]][shot[1]]=player1.board[shot[0]][shot[1]]*-1;
			player2.shots[shot[0]][shot[1]]=hit;
			player2.ShotHit=true;
		} else {
			player2.shots[shot[0]][shot[1]]=miss;
			player2.ShotHit=false;
		}

		printf("Press Any Key to Start Next Turn");
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

static void debugState(board Board,aiMemory ai){
	printf("\n----------------------------------------------\n");
	for(int r=0;r<10;r++){
		printf("|");
		for(int c=0;c<10;c++){
			if(Board.shots[r][c]>=0){
				if(Board.shots[r][c]==0){
					printf("  ");
				}
				else printf(" %d",Board.shots[r][c]);
			} else {
				printf("%d",Board.shots[r][c]);
			}
		}
		printf(" |");
		for(int c=0;c<10;c++){
			if(Board.board[r][c]>=0){
				if(Board.board[r][c]==0){
					printf("  ");
				}
				else printf(" %d",Board.board[r][c]);
			} else {
				printf("%d",Board.board[r][c]);
			}
		}
		printf(" |");
		switch(r){
		case 1:
			printf(" SIP: %d",ai.searchInProgress);
			break;
		case 2:
			printf(" SST: %d",ai.searchState);
			break;
		case 3:
			printf(" FSS: %d %d",ai.firstShot[0], ai.firstShot[1]);
			break;
		case 4:
			printf(" SSS: %d %d",ai.secondShot[0],ai.secondShot[1]);
			break;
		}
		printf("\n");
	}
	printf("----------------------------------------------\n");
}
