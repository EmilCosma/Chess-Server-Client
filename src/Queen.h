#pragma once
#include "Piece.h"
#include<iostream>

class Queen : public Piece{
    int hasMoved=0;
    bool team;
    int x,y;
public:
    Queen(int x, int y, bool team);
    bool moveTo(int xTo, int yTo, int board[][20]);
    string typeOfPiece();
    int getCoord();
    void changeCoord(int xNew, int yNew);
    bool getTeam();
    bool getHasMoved();
};