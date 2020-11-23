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
#include <math.h>

#include "battleship.h"
#include "randomShip.h"
#include "ui.h"
#include "ai.h"

#define DEBUG 0

static void debugState(board Board, aiMemory ai);
static bool isValidRC(int r,int c);
static bool isHit(int board[10][10], int r, int c);
static void shipSunk(board *player1, board *player2, int shot[2]);
static int sGameOver(int arr[10][10]);
static bool isGameOver(int arr[10][10],int gameOverState);

static int UnitTesting=0;//If True then Disables all interactions and forces duals between ai players.
static int setuprandom=0;

int launchBattlehip(){
	setbuf(stdout,NULL);
	if(setuprandom==0){
		setuprandom=1;
		srand(time(NULL));
	}
	bool gameEnd=false;
	board player1={{},{},false,false};
	board player2={{},{},false,false};
	//We Initialize Memory for Both Ai Engines
	//todo move initialization into ai.cpp function call.
	aiMemory ai1={{-1,-1},{-1,-1},0,0};
	aiMemory ai2={{-1,-1},{-1,-1},0,0};
	int shot[2]={}, gameMode=0; //gamemode 0=ai v ai, 1=human vs ai, 2=human v human

	if(!UnitTesting){
		//todo: We Should Draw Title Screen, and let player select game mode (gamemode 0=ai v ai, 1=human vs ai, 2=human v human)
	}else if(UnitTesting==1){
		gameMode=0;
	}

	setupShipsR(player1.board);
	setupShipsR(player2.board);

	int gameOverState1 = sGameOver(player1.board);
	int gameOverState2 = sGameOver(player2.board);

	while(!gameEnd){
		if(DEBUG && gameMode!=0){
			printf("Player 1");
			debugState(player1, ai1);
		}

		//Ai Vs Human Player, Selected by game mode
		if(gameMode>=1){
			if(!DEBUG)clearScreen();
			displayShots(player1.shots);
			displayShips(player1.board);
			printf("Enter Firing Coordinates (Letter Number):\n");
			do{
				char r;
				scanf("%c%d", &r,&shot[1]);
				shot[0]=tolower(r)-'a';
				if(!isValidRC(shot[0], shot[1])){
					fputs("Coordinates Invalid\n",stdout);
				}
			}while(!isValidRC(shot[0], shot[1]));
		} else {
			printf("Ai 1 Is Thinking ...");
			if(gameMode==0)debugState(player1, ai1);
			aiPlayer(player1, &ai1, shot);
			printf("%c%d\n",shot[0]+97,shot[1]);
		}

		//Shot Logic Player1
		if(isHit(player2.board, shot[0], shot[1])){
			player2.board[shot[0]][shot[1]]=abs(player2.board[shot[0]][shot[1]])*-1;
			player1.shots[shot[0]][shot[1]]=hit;
			player1.ShotHit=true;
		} else {
			if(isValidRC(shot[0], shot[1])) player1.shots[shot[0]][shot[1]]=miss;
			player1.ShotHit=false;
		}
		shipSunk(&player1, &player2, shot);
		if((gameEnd=isGameOver(player2.board, gameOverState2))){
			printf("Player 1 Wins !!!!!!!!!!");
			return(1);
			break;
		}
		//END Shot Logic Player1

		if(DEBUG && gameMode!=0){
			printf("Player 2");
			debugState(player2, ai2);
		}

		//Player 2 Interaction
		if(gameMode>=2){
			if(!DEBUG)clearScreen();
			displayShots(player2.shots);
			displayShips(player2.board);
			printf("Enter Firing Coordinates (Letter Number):\n");
			do{
				char r;
				scanf("%c%d", &r,&shot[1]);
				shot[0]=tolower(r)-'a';
				if(!isValidRC(shot[0], shot[1])){
					fputs("Coordinates Invalid\n",stdout);
				}
			}while(!isValidRC(shot[0], shot[1]));
		}else{
			printf("Ai 2 Is Thinking ... ");
			if(gameMode==0)debugState(player2, ai2);
			aiPlayer(player2, &ai2, shot);
			printf("%c%d\n",shot[0]+97,shot[1]);
		}
		//END PLayer 2 Interaction

		//Shot Logic Player2
		if(isHit(player1.board, shot[0], shot[1])){
			player1.board[shot[0]][shot[1]]=abs(player1.board[shot[0]][shot[1]])*-1;
			player2.shots[shot[0]][shot[1]]=hit;
			player2.ShotHit=true;
		} else {
			player2.shots[shot[0]][shot[1]]=miss;
			player2.ShotHit=false;
		}
		shipSunk(&player2, &player1, shot);
		if((gameEnd=isGameOver(player1.board, gameOverState1))){
			printf("Player 2 Wins !!!!!!!!!!");
			return(2);
			break;
		}
		//END Shot Logic Player 2

		if(!UnitTesting && gameMode==0){
			printf("Press Any Key to Start Next Ai Turn");
			getchar();
		}
	}


	return(0);
}

static int sGameOver(int arr[10][10]){
	int state=0;
	for(int r=0;r<boardrows;r++){
		for(int c=0;c<boardcolumns;c++){
			state+=-1*abs(arr[r][c]);
		}
	}
	return state;
}

static bool isGameOver(int arr[10][10],int gameOverState){
	int sum;
	for(int r=0;r<boardrows;r++){
		for(int c=0;c<boardcolumns;c++){
			sum+=arr[r][c];
		}
	}
	if(sum<=gameOverState) return true;
	return false;
}

static void shipSunk(board *player1,board *player2, int shot[2]){

	if(player1->ShotHit==true){
		int test = abs(player2->board[shot[0]][shot[1]]), accumelator=0;

		for(int r=0;r<boardrows;r++){
			for(int c=0;c<boardcolumns;c++){
				if(player2->board[r][c]==test)
					accumelator++;
			}
		}
		if(accumelator==0){
			player1->ShipSunk=true;
		}
	}else{
		player1->ShipSunk=false;
	}
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
	if(isValidRC(r, c) && board[r][c]>0){
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
					printf(" .");
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
					printf(" .");
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
		case 5:
			printf(" Hit: %d",Board.ShotHit);
			break;
		case 6:
			printf(" Sunk: %d",Board.ShipSunk);
			break;
		}
		printf("\n");
	}
	printf("----------------------------------------------\n");
}

void testBattleShip(int typeTest){
	if(typeTest==1){
		int sum1=0,sum2=0,rounds=0,temp;
		UnitTesting=1;
		for(int i=0;i<1000;i++){
			temp=launchBattlehip();
			if(temp==1)sum1++;
			if(temp==2)sum2++;
			rounds++;
		}
		printf("Ran %d rounds, Player 1: %.2f Player 2: %.2f\n",rounds,1.0*sum1/rounds,1.0*sum2/rounds);
	}
}
