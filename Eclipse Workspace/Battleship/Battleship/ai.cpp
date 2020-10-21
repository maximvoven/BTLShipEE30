/*
 * ai.cpp
 *
 *  Created on: Oct 20, 2020
 *      Author: Maxim Vovenko
 */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "board.h"

static bool isValidRC(int r,int c);
int * easyAiPlayer();
int * aiPlayer(int board[10][10], int shots[10][10],bool lastShotHit,bool lastShotSank);

int * easyAiPlayer(){
	static int out[2];
	srand(time(NULL));
	out[0]=rand()%10;
	out[1]=rand()%10;
	return out;
}

//todo optimize code to have method calls?.
int * aiPlayer(int board[10][10], int shots[10][10],bool lastShotHit,bool lastShotSank){
	static int lastRow0=-1,lastCol0=-1,
			lastRow1=-1,lastCol1=-1;
	static int out[2];
	if(lastShotSank){ //If Ship Sunk we reset State Machine
		lastRow0=-1;lastCol0=-1;
		lastRow1=-1;lastCol1=-1;
	}
	if(isValidRC(lastRow0,lastCol0)){
		if(lastShotHit){
			if(isValidRC(lastRow1,lastCol1)){
				out[0]=(2*lastRow0-lastRow1);
				out[1]=(2*lastCol0-lastCol1);
				if(!isValidRC(out[0], out[1])){
					int seekr=lastRow1-lastRow0;
					int seekc=lastCol1-lastCol0;
					int seek=1;
					while(shots[lastRow0+seekr*seek][lastCol0+seekc*seek]==hit){
						seek++;
					}
					out[0]=lastRow0+seekr*seek;
					out[1]=lastCol0+seekc*seek;
					lastRow0=lastRow0+seekr*(seek-1);
					lastCol0=lastCol0+seekc*seek;
				}

			} else {
				lastRow1=lastRow0;
				lastCol1=lastCol0;
				srand(time(NULL));
				int direction=rand()%4;
				int tempr,tempc;
				do{
					switch(direction){
					case 0:
						tempr=lastRow0+1;
						tempc=lastCol0;
						break;
					case 1:
						tempr=lastRow0-1;
						tempc=lastCol0;
						break;
					case 2:
						tempr=lastRow0;
						tempc=lastCol0+1;
						break;
					case 3:
						tempr=lastRow0;
						tempc=lastCol0-1;
						break;
					}
					if(!isValidRC(tempr, tempc)) direction = (direction+1)%4;
				} while(!isValidRC(tempr, tempc));
				out[0]=tempr;
				out[1]=tempc;

			}
		}else{
			if(isValidRC(lastRow1,lastCol1)){
				int seekr=lastRow1-lastRow0;
				int seekc=lastCol1-lastCol0;
				int seek=1;
				while(shots[lastRow0+seekr*seek][lastCol0+seekc*seek]==hit){
					seek++;
				}
				out[0]=lastRow0+seekr*seek;
				out[1]=lastCol0+seekc*seek;
			} else {
				srand(time(NULL));
				out[0]=rand()%10;
				out[1]=rand()%10;
				while(shots[out[0]][out[1]]!=0){
					out[0]++;
					if(out[0]>=10){
						out[0]=0;
						out[1]=(out[1]+1)%10;
					}
				}
			}
		}
	}else{
		srand(time(NULL));
		out[0]=rand()%10;
		out[1]=rand()%10;
	}

	if(!isValidRC(out[0], out[1])){
		printf("State Machine Did Ouff");
		printf("CURRENT STATE:\n %d %d %d %d %d %d",out[0],out[1],lastRow0,lastCol0,lastRow1,lastCol1);
		srand(time(NULL));
		out[0]=rand()%10;
		out[1]=rand()%10;
		lastRow0=-1;
		lastCol0=-1;
		lastRow1=-1;
		lastCol1=-1;
	}

	lastRow1=lastRow0;
	lastCol1=lastCol0;
	lastRow0=out[0];
	lastCol0=out[1];
	return out;

}

static bool isValidRC(int r,int c){
	if(r>=0 && r<10){
		if(c>=0 &&c<10){
			return true;
		}
	}
	return false;
}


