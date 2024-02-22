#pragma once
#include "Piece.h"
#include<iostream>

class Pawn : public Piece{
    int hasMoved=0;
    bool team;
    int x,y;
public:
    Pawn(int x, int y, bool team);
    bool moveTo(int xTo, int yTo, int board[][20]);
    string typeOfPiece();
    int getCoord();
    void changeCoord(int xNew, int yNew);
    bool getTeam();
    bool getHasMoved();
};