#pragma once
#include <string>
using namespace std;


class Piece{
    
public:
    virtual bool moveTo( int xTo,int yTo, int board[][20]) =0;
    virtual string typeOfPiece() =0;
    virtual int getCoord()=0;
    virtual void changeCoord(int xNew,int yNew)=0;
    virtual bool getTeam()=0;
    virtual bool getHasMoved()=0;
};