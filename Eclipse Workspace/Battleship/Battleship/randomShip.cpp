/*
 * randomShip.cpp
 * Place for code to place random ships into ship array.
 *  Created on: Oct 19, 2020
 *      Author: Maxim Vovenko
 */

/*
Code runs One Ship at time
setup random
Largest Ship to the Smallest Ship (Ships definitions are in board.h)

1.Pick Random Coordinate
2.Pick a random direction (0=up,1=down,2=left,3=right)
3. Check that for the length of the ship, none of coordinates have a value greater then 0 and that all of them are in bounds. (Check inbounds first then coordinate value)
3A. If you are out of bounds, or you come across a value that is not zero. - Go back to step 1.
3B. Values are valid, and you are inbounds. Go to step 4.
4. Place ship to the coordinates you just checked (board[r][c]=battleship;

repeat for each ship.
*/

#include "randomShip.h"
#include "stdlib.h"
#include "time.h"

//Function Must populate board with 5 ships and respective lengths.
//Ships are defined in board.h with names of type of ship and their lengths
//Notice int array if your placing battleship then board[r][c]=
static int checkIfValid(int board[boardrows][boardcolumns],int r,int c,int d, int length);
void setupShipsR(int board[boardrows][boardcolumns])
{
    //L at the end of ship name gives length ship
    int r,c,d,temp; //row colum direction

    //Carrier
    r=rand()%boardrows;
    c=rand()%boardcolumns;
    d=rand()%4;
    temp=d;
    while(!checkIfValid(board,r,c,d%4,carrierL)){
        d++;
        if(d>=temp+4){
            d=temp;
            c++;
            if(c>=10){
                r++;
                c=c%10;
                if(r>=10){
                    r=r%10;
                }
            }
        }
    }
    for(int i=0;i<carrierL;i++){
        switch(d%4){
            case 0:
                board[r-i][c]=carrier;
                break;
            case 1:
                board[r+i][c]=carrier;
                break;
            case 2:
                board[r][c-i]=carrier;
                break;
            case 3:
                board[r][c+i]=carrier;
                break;
            default:
                perror("Direction Exceeded 4, Carrier");
                while(1);
                break;
        }
    }
    //END Carrier
    
    //Battleship
    r=rand()%boardrows;
    c=rand()%boardcolumns;
    d=rand()%4;
    temp=d;
    while(!checkIfValid(board,r,c,d%4,battleshipL)){
        d++;
        if(d>=temp+4){
            d=temp;
            c++;
            if(c>=10){
                r++;
                c=c%10;
                if(r>=10){
                    r=r%10;
                }
            }
        }
    }
    for(int i=0;i<battleshipL;i++){
        switch(d%4){
            case 0:
                board[r-i][c]=battleship;
                break;
            case 1:
                board[r+i][c]=battleship;
                break;
            case 2:
                board[r][c-i]=battleship;
                break;
            case 3:
                board[r][c+i]=battleship;
                break;
            default:
                perror("Direction Exceeded 3 Battleship");
                while(1);
                break;
        }
    }
    //END Battleship
    
    //Cruiser
    r=rand()%boardrows;
    c=rand()%boardcolumns;
    d=rand()%4;
    temp=d;
    while(!checkIfValid(board,r,c,d%4,cruiserL)){
        d++;
        if(d>=temp+4){
            d=temp;
            c++;
            if(c>=10){
                r++;
                c=c%10;
                if(r>=10){
                    r=r%10;
                }
            }
        }
    }
    for(int i=0;i<cruiserL;i++){
        switch(d%4){
            case 0:
                board[r-i][c]=cruiser;
                break;
            case 1:
                board[r+i][c]=cruiser;
                break;
            case 2:
                board[r][c-i]=cruiser;
                break;
            case 3:
                board[r][c+i]=cruiser;
                break;
            default:
                perror("Direction Exceeded 3 Cruiser");
                while(1);
                break;
        }
    }
    //END Cruiser
    
    //Submarine
    r=rand()%boardrows;
    c=rand()%boardcolumns;
    d=rand()%4;
    temp=d;
    while(!checkIfValid(board,r,c,d%4,submarineL)){
        d++;
        if(d>=temp+4){
            d=temp;
            c++;
            if(c>=10){
                r++;
                c=c%10;
                if(r>=10){
                    r=r%10;
                }
            }
        }
    }
    for(int i=0;i<submarineL;i++){
        switch(d%4){
            case 0:
                board[r-i][c]=submarine;
                break;
            case 1:
                board[r+i][c]=submarine;
                break;
            case 2:
                board[r][c-i]=submarine;
                break;
            case 3:
                board[r][c+i]=submarine;
                break;
            default:
                perror("Direction Exceeded 3 Submarine");
                while(1);
                break;
        }
    }
    //END Submarine
    
    //Destroyer
    r=rand()%boardrows;
    c=rand()%boardcolumns;
    d=rand()%4;
    temp=d;
    while(!checkIfValid(board,r,c,d%4,destroyerL)){
        d++;
        if(d>=temp+4){
            d=temp;
            c++;
            if(c>=10){
                r++;
                c=c%10;
                if(r>=10){
                    r=r%10;
                }
            }
        }
    }
    for(int i=0;i<destroyerL;i++){
        switch(d%4){
            case 0:
                board[r-i][c]=destroyer;
                break;
            case 1:
                board[r+i][c]=destroyer;
                break;
            case 2:
                board[r][c-i]=destroyer;
                break;
            case 3:
                board[r][c+i]=destroyer;
                break;
            default:
                perror("Direction Exceeded 3 Destroyer");
                while(1);
                break;
        }
    }
    //END Destroyer
}

static int checkIfValid(int board[boardrows][boardcolumns],int r,int c,int d, int length){
    switch(d%4){
        case 0:
            if(r-(length-1)<0) return 0;
            break;
        case 1:
            if(r+(length-1)>=10) return 0;
            break;
        case 2:
            if(c-(length-1)<0) return 0;
            break;
        case 3:
            if(c+(length-1)>=10) return 0;
            break;
        default:
            perror("Direction Exceeded 3 CheckIfValid");
            while(1);
            break;
    }

    for(int i=0;i<length;i++){
        switch(d%4){
            case 0:
                if(board[r-i][c]!=0) return 0;
                break;
            case 1:
                if(board[r+i][c]!=0) return 0;
                break;
            case 2:
                if(board[r][c-i]!=0) return 0;
                break;
            case 3:
                if(board[r][c+i]!=0) return 0;
                break;
            default:
                perror("Direction Exceeded 3 CheckIfValid");
                while(1);
                break;
        }
    }
    return 1;
}

