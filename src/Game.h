#pragma once
#include<vector>
#include "Piece.h"
#include "Pawn.h"
#include "Knight.h"
#include "Rook.h"



class Game{
    bool whoMoves=0;
    bool firstMove=0;
    int board[20][20]={
        {2, 3, 4, 5, 6, 4, 3, 2},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-2, -3, -4, -5, -6, -4, -3, -2}
    };
    vector<Piece*> whitePieces;
    vector<Piece*> blackPieces;
    void deletePiece(int x,int y);
    void promotePawn(int x,int y);
    void rocada(bool team, bool side);
public:
    void setUpGame();
    
    void printPieces();
    
    int movePiece(int xFrom, int yFrom, int xTo, int yTo);
    ~Game();
    
};