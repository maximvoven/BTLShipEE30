/*
 * ai.cpp
 *
 *  Created on: Oct 20, 2020
 *      Author: Maxim Vovenko
 */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "board.h"
#include "ai.h"

static bool isValidRC(int r,int c);
static void resetMemory(aiMemory *memory);
static bool isEmpty(int r, int c, board Board);

void easyAiPlayer(int out[2]){
	srand(time(NULL));
	out[0]=rand()%10;
	out[1]=rand()%10;
}

//todo optimize code to have method calls?.
void aiPlayer(board Board, aiMemory *memory,int shot[2]){
	shot[0]=-1;
	shot[1]=-1;
	//Reset Ai Engine State if we sink ship
	if(Board.ShipSunk){
		Board.ShipSunk=false;
		Board.ShotHit=false;
		resetMemory(memory);
	}
	if(Board.ShotHit==false && memory->secondShot[0]<0){
		resetMemory(memory);
	}
	//Search Pattern (Random Guessing)
	if(memory->firstShot[0]<0){
		srand(time(NULL));
		shot[0]=rand()%10;
		shot[1]=rand()%10;
		while(isEmpty(shot[0],shot[1],Board)==false){
			shot[0]++;
			if(shot[0]>9){
				shot[0]=0;
				shot[1]++;
				if(shot[1]>9) shot[1]=0;
			}
		}
		memory->firstShot[0]=shot[0];
		memory->firstShot[1]=shot[1];
		Sleep(rand()%300 + 100);
		return;
	}
	//+ Search Pattern
	//Initialize Search
	if(Board.ShotHit && memory->searchInProgress==0){
		memory->searchState=1;
		memory->searchInProgress=1;
		memory->secondShot[0]=memory->firstShot[0];
		memory->secondShot[1]=memory->firstShot[1];
		shot[0]=memory->firstShot[0]-1;
		shot[1]=memory->firstShot[1];
		if(!isValidRC(shot[0], shot[1])){
			memory->searchState=2;
			shot[0]=memory->firstShot[0]+1;
			shot[1]=memory->firstShot[1];
		}
		memory->firstShot[0]=shot[0];
		memory->firstShot[1]=shot[1];
		return;
	}

	if(Board.ShotHit && memory->searchInProgress==1){
		//If Last Shot Hit Keep Shooting in that direction
		memory->searchInProgress=2;
		memory->secondShot[0]=memory->firstShot[0];
		memory->secondShot[1]=memory->firstShot[1];
	}else if(!Board.ShotHit && memory->searchInProgress==1){
		//If Shot Miss Continue + Search Pattern
		memory->searchState++;
		do{
			switch(memory->searchState){
			case 2:
				shot[0]=memory->secondShot[0]+1;
				shot[1]=memory->secondShot[1];
				break;
			case 3:
				shot[0]=memory->secondShot[0];
				shot[1]=memory->secondShot[1]-1;
				break;
			case 4:
				shot[0]=memory->secondShot[0];
				shot[1]=memory->secondShot[1]+1;
				break;
			default:
				perror("Search State Exceeded 4, Progress State 1");
				exit(EXIT_FAILURE);
				break;
			}
			if(!(isValidRC(shot[0],shot[1]) || isEmpty(shot[0],shot[1],Board))){
				memory->searchState=(memory->searchState)+1;
			}
			if((memory->searchState) > 4){
				resetMemory(memory);
				aiPlayer(Board, memory, shot);
				break;
			}
		}while(!isValidRC(shot[0],shot[1]) || !isEmpty(shot[0],shot[1],Board));
		memory->firstShot[0]=shot[0];
		memory->firstShot[1]=shot[1];
		return;

	}
	if(Board.ShotHit && (memory->searchInProgress) == 2){
		memory->secondShot[0]=memory->firstShot[0];
		memory->secondShot[1]=memory->firstShot[1];
		switch(memory->searchState){
		case 1:
			shot[0]=memory->secondShot[0]-1;
			shot[1]=memory->secondShot[1];
			break;
		case 2:
			shot[0]=memory->secondShot[0]+1;
			shot[1]=memory->secondShot[1];
			break;
		case 3:
			shot[0]=memory->secondShot[0];
			shot[1]=memory->secondShot[1]-1;
			break;
		case 4:
			shot[0]=memory->secondShot[0];
			shot[1]=memory->secondShot[1]+1;
			break;
		}
		memory->firstShot[0]=shot[0];
		memory->firstShot[0]=shot[1];
		return;
	} else if(!Board.ShotHit && (memory->searchInProgress==2)){
		memory->searchInProgress=3;
	}

}

static void resetMemory(aiMemory *memory){
	memory->firstShot[0]=-1;
	memory->firstShot[1]=-1;
	memory->secondShot[0]=-1;
	memory->secondShot[1]=-1;
	memory->searchState=0;
	memory->searchInProgress=0;
}
static bool isEmpty(int r, int c, board Board){
	if(Board.shots[r][c]==0){
		return true;
	}
	return false;
}

static bool isValidRC(int r,int c){
	if((r>=0) && (r<=9)){
		if((c>=0) && (c<=9)){
			return true;
		}
	}
	return false;
}


