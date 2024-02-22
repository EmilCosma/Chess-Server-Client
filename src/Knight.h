#pragma once
#include "Piece.h"
#include<string>
#include<iostream>

class Knight : public Piece{
    bool team;
    int x,y;
    int hasMoved=0;
public:
    Knight(int x, int y, bool team);
    bool moveTo(int xTo, int yTo, int board[][20]);
    string typeOfPiece();
    int getCoord();
    void changeCoord(int xNew, int yNew);
    bool getTeam();
    bool getHasMoved();
};