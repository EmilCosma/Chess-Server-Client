#pragma once
#include "King.h"

string King::typeOfPiece()
{
    return "king";
}
King::King(int x, int y, bool team)
{
    this->x=x;
    this->y=y;
    this->team=team;
}
bool King::moveTo(int xTo, int yTo, int board[][20])
{
    if (xTo <0 || xTo >7 || yTo <0 || yTo >7)
    {
        cout<<"Out of bounds coords\n";
        return 0;
    }
    if(team == 0)
    {
        if(board[xTo][yTo] <0)
        {
            cout<<"Friendly piece already there!\n";
            return 0;
        }
    }
    else
    {
       if(board[xTo][yTo] >0)
        {
            cout<<"Friendly piece already there!\n";
            return 0;
        }
    }
    if(xTo == x && yTo == y) //check if is the same position
    {
        return 0;
    }
    if((xTo == x-1 || xTo == x+1 || xTo == x) && (yTo == y-1 || yTo == y+1 || yTo==y))
    {
        hasMoved=1;
        return 1;
    }
    if(hasMoved==0 && yTo == y+2 && board[xTo][yTo-1] == 0 && abs(board[xTo][yTo+1])==2) //O-O
    {
        hasMoved=1;
        return 1;
    }
    if(hasMoved==0 && yTo == y-2 && board[xTo][yTo+1] == 0 && board[xTo][yTo-1]==0 && abs(board[xTo][yTo-2])==2) //O-O-O
    {
        hasMoved=1;
        return 1;
    }
    return 0;
}
int King::getCoord()
{
    return x*10+y;
}

void King::changeCoord(int xNew, int yNew)
{
    this->x=xNew;
    this->y=yNew;
}
bool King::getTeam()
{
    return this->team;
}

bool King::getHasMoved()
{
    return this->hasMoved;
}
