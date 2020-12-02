/*
 * File Contains Main Call to Launch Program and
 * should also be used for debugging/unit testing
 * your specific task.
 *
 */
#include <stdlib.h>

#include "Battleship/battleship.h"

int unitTest = 0; //Auto Play the Game

int main(int argc, char **argv) {
	if(unitTest==0){
		launchBattlehip();
		return EXIT_SUCCESS;
	}else{
		testBattleShip(unitTest);
	}
	return EXIT_SUCCESS;
}
