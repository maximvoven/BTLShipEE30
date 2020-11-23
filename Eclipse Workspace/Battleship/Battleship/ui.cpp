/*
 * ui.cpp
 * Place for all Drawing calls for ui.
 *  Created on: Oct 19, 2020
 *      Author: Maxim Vovenko
 */
#include "ui.h"
#include "battleship.h"
#include <stdio.h>

#define boardrows 10
#define boardcolums 10

int arr[boardrows][boardcolums];

void displayText(char text[],int len){
	printf("%s",text);
}

void displayShips(int board[boardrows][boardcolumns]){
   //arr[r][c] array with 2 dimensions then array[row][colum]
    //Positive = Ship Allive, Negative = Ship Hit
    printf("   0 1 2 3 4 5 6 7 8 9 \n");
    printf("  _____________________ \n");
    for(int r = 0; r < boardrows; r++) {
        putc('A'+r,stdout); //printf("%c",'A'+r);
        putc(' ',stdout);
        for(int c = 0; c < boardcolums; c++)
        {
            if(board[r][c]==0){
                printf("| ");
            }
            else if(board[r][c]==battleship){
                printf("|B");
            }
            else if(board[r][c]==carrier){
                printf("|C");
            }
            else if(board[r][c]==cruiser){
                printf("|F");
            }
            else if(board[r][c]==submarine){
                printf("|S");
            }
            else if(board[r][c]==destroyer){
                printf("|D");
            }
            
            else {
                printf("|X");
            }
            
        }
        printf("|\n");
    }
    printf("  --------------------- \n");
    printf("\n");
}


void displayShots(int board[boardrows][boardcolumns]){
    //Displays all the shots player has taken
    //board = 0 then no shot has been taken ( )
    //board > 0 then shot was taken. but it missed (O)
    //board < 0 then shot was takem, and it hit. (X)
    printf("\n");
    printf("   0 1 2 3 4 5 6 7 8 9 \n");
    printf("  _____________________ \n");
    for(int r = 0; r < boardrows; r++) {
        putc('A'+r,stdout); //printf("%c",'A'+r);
        putc(' ',stdout);
        for(int c = 0; c < boardcolums; c++)
        {
            if(board[r][c]==0){
                printf("| ");
            } else if(board[r][c]>0){
                printf("|O");
            }else if(board[r][c]<0){
                printf("|X");
            }
            
        }
        printf("|\n");
    }
    printf("  --------------------- \n");
    printf("\n");
    
}

void clearScreen(){ //clear screen of characters
    for(int i=0; i<100; i++){
        printf("\n");
    }
}

/*
 *  2x2 -> 10x10
 *    1  2
    -------------
 *A |   | B |   |
 *  -------------
 *B |   | B |   |
 *  -------------
 */
/*
 
 */
