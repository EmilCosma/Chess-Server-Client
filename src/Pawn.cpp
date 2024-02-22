#pragma once
#include "Pawn.h"

string Pawn::typeOfPiece()
{
    return "pawn";
}
Pawn::Pawn(int x, int y, bool team)
{
    this->x=x;
    this->y=y;
    this->team=team;
}
bool Pawn::moveTo(int xTo, int yTo, int board[][20])
{
    if (xTo <0 || xTo >7 || yTo <0 || yTo >7)
    {
        cout<<"Out of bounds coords\n";
        return 0;
    }
    if(team == 0)
    {
        if(yTo == this->y && xTo == this->x-1  && board[xTo][yTo]==0) //verifies if it can move forward without capture
        {
            hasMoved=1;
            return 1;
        }
        if((yTo == this->y-1|| yTo==this->y+1) && xTo == this->x-1 && board[xTo][yTo] >0) // verifies if capture
        {
            hasMoved=1;
            return 1;
        }
        if(yTo == this->y && xTo == this->x-2  && board[xTo][yTo]==0 && board[xTo+1][yTo]==0 && hasMoved==0) //verifies for double square move
        {
            hasMoved=1;
            return 1;
        }
        return 0;

    }
    else
    {
       if(yTo == this->y && xTo == this->x+1  && board[xTo][yTo]==0) //verifies if it can move forward without capture
        {
            hasMoved=1;
            return 1;
        }
        if((yTo == this->y-1|| yTo==this->y+1) && xTo == this->x+1 && board[xTo][yTo] <0) // verifies if capture
        {
            hasMoved=1;
            return 1;
        }
        if(yTo == this->y && xTo == this->x+2  && board[xTo][yTo]==0 && board[xTo-1][yTo]==0 && hasMoved==0) //verifies for double square move
        {
            hasMoved=1;
            return 1;
        }
        return 0;
    }
    

}
int Pawn::getCoord()
{
    return x*10+y;
}

void Pawn::changeCoord(int xNew, int yNew)
{
    this->x=xNew;
    this->y=yNew;
}
bool Pawn::getTeam()
{
    return this->team;
}

bool Pawn::getHasMoved()
{
    return this->hasMoved;
}
