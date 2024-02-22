#pragma once
#include "Queen.h"

string Queen::typeOfPiece()
{
    return "queen";
}
Queen::Queen(int x, int y, bool team)
{
    this->x=x;
    this->y=y;
    this->team=team;
}
bool Queen::moveTo(int xTo, int yTo, int board[][20])
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
    if(xTo==x) //checks if there are no pieces in the way
    {
            if(y>yTo)
            {
                for(int i =yTo+1; i<y; i++)
                {
                    if(board[xTo][i]!=0)
                    {
                        cout<<"Piece in the way!\n";
                        return 0;
                    }
                }
                return 1;
            }
            else if(y<yTo)
            {
                for(int i=y+1; i<yTo; i++)
                {
                    if(board[xTo][i]!=0)
                    {
                        cout<<"Piece in the way!\n";
                        return 0;
                    }
                }
                return 1;
            }
    }
    else if(yTo==y)
    {
        if(x>xTo)
        {
            for(int i=xTo+1; i<x; i++)
            {
                if(board[i][y]!=0)
                {
                    cout<<"Piece in the way\n";
                    return 0;
                }
            }
            return 1;
        }
        else if(x<xTo)
        {
            for(int i=x+1; i<xTo; i++)
            {
                if(board[i][y]!=0)
                {
                    cout<<"Piece in the way\n";
                    return 0;
                }
            }
            return 1;
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
int Queen::getCoord()
{
    return x*10+y;
}

void Queen::changeCoord(int xNew, int yNew)
{
    this->x=xNew;
    this->y=yNew;
}
bool Queen::getTeam()
{
    return this->team;
}

bool Queen::getHasMoved()
{
    return this->hasMoved;
}
