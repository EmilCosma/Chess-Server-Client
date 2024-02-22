#pragma once
#include "Knight.h"

string Knight::typeOfPiece()
{
    return "knight";
}
Knight::Knight(int x, int y, bool team)
{
    this->x=x;
    this->y=y;
    this->team=team;
}

bool Knight::moveTo(int xTo, int yTo, int board[][20])
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
    if(xTo== x-1 && yTo==y-2)
            return 1;
    if(xTo== x-1 && yTo==y+2)
            return 1;
    if(xTo== x+1 && yTo==y-2)
            return 1;
    if(xTo== x+1 && yTo==y+2)
            return 1;

    if(xTo== x-2 && yTo==y-1)
            return 1;
    if(xTo== x-2 && yTo==y+1)
            return 1;
    if(xTo== x+2 && yTo==y-1)
            return 1;
    if(xTo== x+2 && yTo==y+1)
            return 1;
    return 0;

}
int Knight::getCoord()
{
    return x*10+y;
}

void Knight::changeCoord(int xNew, int yNew)
{
    this->x=xNew;
    this->y=yNew;
}
bool Knight::getTeam()
{
    return this->team;
}

bool Knight::getHasMoved()
{
    return this->hasMoved;
}
