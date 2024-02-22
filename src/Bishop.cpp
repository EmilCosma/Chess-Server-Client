#pragma once
#include "Bishop.h"

string Bishop::typeOfPiece()
{
    return "bishop";
}
Bishop::Bishop(int x, int y, bool team)
{
    this->x=x;
    this->y=y;
    this->team=team;
}
bool Bishop::moveTo(int xTo, int yTo, int board[][20])
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
    if(xTo-yTo==x-y) //checks if there are no pieces in the way
    {
            if(y>yTo)
            {
                for(int j =yTo+1, i=xTo+1; j<y; i++, j++)
                {
                    if(board[i][j]!=0)
                    {
                        cout<<"Piece in the way!\n";
                        return 0;
                    }
                }
                return 1;
            }
            else if(y<yTo)
            {
                for(int i=x+1,j=y+1; i<yTo; i++, j++)
                {
                    if(board[i][j]!=0)
                    {
                        cout<<"Piece in the way!\n";
                        return 0;
                    }
                }
                return 1;
            }
    }
    else if(xTo+yTo==x+y)
    {
        if(y>yTo)
            {
                for(int j =yTo+1, i=xTo+1; j<y; i++, j++)
                {
                    if(board[i][j]!=0)
                    {
                        cout<<"Piece in the way!\n";
                        return 0;
                    }
                }
                return 1;
            }
            else if(y<yTo)
            {
                for(int i=x+1,j=y+1; i<yTo; i++, j++)
                {
                    if(board[i][j]!=0)
                    {
                        cout<<"Piece in the way!\n";
                        return 0;
                    }
                }
                return 1;
            }
    }
    return 0;

}
int Bishop::getCoord()
{
    return x*10+y;
}

void Bishop::changeCoord(int xNew, int yNew)
{
    this->x=xNew;
    this->y=yNew;
}
bool Bishop::getTeam()
{
    return this->team;
}

bool Bishop::getHasMoved()
{
    return this->hasMoved;
}
