/*
 * ai.cpp
 *
 *  Created on: Oct 20, 2020
 *      Author: Maxim Vovenko
 */
#include <stdlib.h>
#include <time.h>

static bool isValidRC(int r,int c)
int * easyAiPlayer()
int * aiPlayer(int board[10][10], int shots[10][10],bool lastShotHit,bool lastShotSank)

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
	if(lastShotSank){
		lastRow0=-1;lastCol0=-1;
		lastRow1=-1;lastCol1=-1;
	}
	if(isValidRC(lastRow0,lastCol0)){
		if(lastShotHit){
			if(isValidRC(lastRow1,lastCol1)){
				out[0]=(2*lastRow0-lastRow1);
				out[1]=(2*lastCol0-lastCol1);
				if(!isValidRC(out[0], out[1])){
					//todo seek back shot chain to find new valid coordinate.
				}
				lastRow1=lastRow0;
				lastCol1=lastCol0;

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
				out[0]=lastRow0=tempr;
				out[1]=lastCol0=tempc;

			}
		}else{
			if(isValidRC(lastRow1,lastCol1)){
				//todo seek back shot chain to find new valid coordinate
			} else {
				srand(time(NULL));
				out[0]=lastRow0=rand()%10;
				out[1]=lastCol0=rand()%10;
				//todo check if i have fired on random coordinate already.
			}
		}
	}else{
		srand(time(NULL));
		out[0]=lastRow0=rand()%10;
		out[1]=lastCol0=rand()%10;
	}
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


