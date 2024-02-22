#include "Game.h"
#include "Piece.h"
#include <vector>
#include <iostream>
#include "Pawn.h"
#include "Pawn.cpp"

#include"Knight.h"
#include"Knight.cpp"

#include "Rook.h"
#include "Rook.cpp"

#include "Bishop.h"
#include "Bishop.cpp"

#include "Queen.h"
#include "Queen.cpp"

#include "King.h"
#include "King.cpp"
using namespace std;


void Game::setUpGame()
{
    Pawn* p1=new Pawn(6, 7, false);
    whitePieces.push_back(p1);


    Pawn* p2=new Pawn(6, 6, false);
    whitePieces.push_back(p2);


    Pawn* p3=new Pawn(6, 5, false);
    whitePieces.push_back(p3);

    Pawn* p4=new Pawn(6, 4, false);
    whitePieces.push_back(p4);

    Pawn* p5=new Pawn(6, 3, false);
    whitePieces.push_back(p5);

    Pawn* p6=new Pawn(6, 2, false);
    whitePieces.push_back(p6);

    Pawn* p7=new Pawn(6, 1, false);
    whitePieces.push_back(p7);

    Pawn* p8=new Pawn(6, 0, false);
    whitePieces.push_back(p8);

    Pawn* pb1=new Pawn(1,7, true);
    blackPieces.push_back(pb1);

    Pawn* pb2=new Pawn(1,6, true);
    blackPieces.push_back(pb2);

    Pawn* pb3=new Pawn(1,5, true);
    blackPieces.push_back(pb3);

    Pawn* pb4=new Pawn(1,4, true);
    blackPieces.push_back(pb4);

    Pawn* pb5=new Pawn(1,3, true);
    blackPieces.push_back(pb5);

    Pawn* pb6=new Pawn(1,2, true);
    blackPieces.push_back(pb6);

    Pawn* pb7=new Pawn(1,1, true);
    blackPieces.push_back(pb7);

    Pawn* pb8=new Pawn(1,0, true);
    blackPieces.push_back(pb8);


    Knight* k1=new Knight(7,6, false);
    whitePieces.push_back(k1);

    Knight* k2=new Knight(7,1, false);
    whitePieces.push_back(k2);

    Knight* k3=new Knight(0,1, true);
    blackPieces.push_back(k3);

    Knight* k4=new Knight(0,6, true);
    blackPieces.push_back(k4);

    Rook* r1=new Rook(7,7,false);
    whitePieces.push_back(r1);

    Rook* r2=new Rook(7,0,false);
    whitePieces.push_back(r2);

    Rook* r3=new Rook(0,7,true);
    blackPieces.push_back(r3);

    Rook* r4=new Rook(0,0,true);
    blackPieces.push_back(r4);

    Bishop* b1= new Bishop(7,5, false);
    whitePieces.push_back(b1);

    Bishop* b2= new Bishop(7,2, false);
    whitePieces.push_back(b2);

    Bishop* b3= new Bishop(0, 2, true);
    blackPieces.push_back(b3);

    Bishop* b4= new Bishop(0, 5, true);
    blackPieces.push_back(b4);

    Queen* q1= new Queen(7,3,false);
    whitePieces.push_back(q1);

    Queen* q2= new Queen(0,3, true);
    blackPieces.push_back(q2);

    King* ki1=new King(7, 4, false);
    whitePieces.push_back(ki1);

    King* ki2= new King(0,4,true );
    blackPieces.push_back(ki2);

}



void Game::printPieces()
{
    
    /*cout<<"White pieces:\n";
    for(Piece* piece: whitePieces){
        cout<<piece->getCoord()<<" - "<<piece->typeOfPiece()<<endl;
    }
    cout<<"Black pieces:\n";
    for(Piece* piece: blackPieces){
        cout<<piece->getCoord()<<" - "<<piece->typeOfPiece()<<endl;
    }*/
    for(int i=0; i<8; i++)
    {
        cout<<8-i<<"| ";
        for(int j=0; j<8; j++)
        {
            if(board[i][j]>=0)
                cout<<' ';
            cout<<board[i][j]<<' ';
        }

        cout<<'\n';
    }
    cout<<"    ";
    for(int i=0; i<8; i++)
        cout<<char('a'+i)<<"  ";
    cout<<endl;
}

void Game::deletePiece(int x, int y)
{
    int found=0;
    for (Piece* piece : whitePieces)
    {
        if(piece->getCoord()/10 == x && piece->getCoord()%10 == y)
        {
            found=1;
            piece->changeCoord(10,10);
        }
    }
    for (Piece* piece : blackPieces)
    {
        if(piece->getCoord()/10 == x && piece->getCoord()%10 == y)
        {
            found=1;
            piece->changeCoord(10,10);
        }

    }
    if(found==0)
        cout<<"No piece was found to delete\n";
}

void Game::promotePawn(int x, int y)
{
    if( board[x][y] <0)
    {
        Queen* q1= new Queen(x,y,false);
        whitePieces.push_back(q1);
        board[x][y]=-5;
    }
    else if(board[x][y] >0)
    {
        Queen* q1= new Queen(x,y,true);
        blackPieces.push_back(q1);
        board[x][y]=5;
    }
    else
        printf("No piece found to promote!\n");
}

void Game::rocada(bool team, bool side) //schimba coordonatele la rook
{
    if(team ==0)
    {
        if(side==0) //rocada mica la alb
        {
            for (Piece* piece : whitePieces)
            {
                if(piece->getCoord()/10 == 7 && piece->getCoord()%10 == 7)
                {
                    piece->changeCoord(7,5);
                    board[7][7]=0;
                    board[7][5]=-8;
                }
            }
        }
        else //rocada mare la alb
        {
            for (Piece* piece : whitePieces)
            {
                if(piece->getCoord()/10 == 7 && piece->getCoord()%10 == 0)
                {
                    piece->changeCoord(7,3);
                    board[7][0]=0;
                    board[7][3]=-8;
                }
            }
        }
    }
    else
    {
        if(side==0) //rocada mica la negru
        {
            for (Piece* piece : blackPieces)
            {
                if(piece->getCoord()/10 == 0 && piece->getCoord()%10 == 7)
                {
                    piece->changeCoord(0,5);
                    board[0][7]=0;
                    board[0][5]=8;
                }
            }
        }
        else //rocada mare la negru
        {
            for (Piece* piece : blackPieces)
            {
                if(piece->getCoord()/10 == 0 && piece->getCoord()%10 == 0)
                {
                    piece->changeCoord(0,3);
                    board[0][0]=0;
                    board[0][3]=8;
                }
            }
        }
    }
}

int Game::movePiece(int xFrom, int yFrom, int xTo, int yTo)
{
    int found=0;
    for (Piece* piece : whitePieces)
    {
        if(piece->getCoord()/10 == xFrom && piece->getCoord()%10 == yFrom)
        {
            found=1;
            if(whoMoves == 1)
            {
                cout<<"Black has to move!\n";
                return 0;
            }
            if(piece->moveTo(xTo, yTo, board))
            {
                if(board[xTo][yTo] == 6) //check mate
                {
                    return 2;
                }
                cout<<"Moved succesfully to "<<xTo<<" "<<yTo<<endl;
                if(board[xTo][yTo]!=0) //eats a piece
                    deletePiece(xTo,yTo);
                piece->changeCoord(xTo,yTo); 
                
                board[xTo][yTo]=board[xFrom][yFrom];
                board[xFrom][yFrom]=0;
                if(board[xTo][yTo] ==-2) //rook becomes 8 if has moved
                {
                    board[xTo][yTo]=-8;
                }
                if(board[xTo][yTo] == -6 && yTo==yFrom+2) //rocada mica
                {
                    rocada(0,0);
                }
                if(board[xTo][yTo] == -6 && yTo==yFrom-2) //rocada mare
                {
                    rocada(0,1);
                }
                if(xTo==0 && board[xTo][yTo] == -1) //promotes pawn
                {
                    piece->changeCoord(10,10);
                    promotePawn(xTo,yTo);
                }

                whoMoves=1;
                firstMove=1;
                return 1;
            }
            else 
            {
                cout<<"Invalid move\n";
                return 0;
            }
        }
    }
    for (Piece* piece : blackPieces)
    {
        if(piece->getCoord()/10 == xFrom && piece->getCoord()%10 == yFrom)
        {
            found=1;
            if(whoMoves == 0 || firstMove == 0)
            {
                cout<<"White has to move!\n";
                return 0;
            }
            if(piece->moveTo(xTo, yTo, board))
            {
                if(board[xTo][yTo] == -6)
                {
                    return 3;
                }
                cout<<"Moved succesfully to "<<xTo<<" "<<yTo<<endl;
                if(board[xTo][yTo]!=0)
                    deletePiece(xTo,yTo);
                piece->changeCoord(xTo,yTo); 
                
                board[xTo][yTo]=board[xFrom][yFrom];
                board[xFrom][yFrom]=0;
                if(board[xTo][yTo] ==2) //rook becomes 8 if has moved
                {
                    board[xTo][yTo]=8;
                }
                if(board[xTo][yTo] == 6 && yTo==yFrom+2) //rocada mica
                {
                    rocada(1,0);
                }
                if(board[xTo][yTo] == 6 && yTo==yFrom-2) //rocada mare
                {
                    rocada(1,1);
                }
                if(xTo==7 && board[xTo][yTo] == 1) //promotes pawn
                {
                    piece->changeCoord(10,10);
                    promotePawn(xTo,yTo);
                }

                whoMoves=0;
                
                return 1;
            }
            else 
            {
                cout<<"Invalid move\n";
                return 0;
            }
        }
    }
    if(found==0)
    {
        cout<<"No piece found on "<<xFrom<<" "<<yFrom<<endl;
        return 0;
    }
    return 0;
}

Game::~Game()
{
    for (Piece* piece : whitePieces) {
            delete piece;
    }
    for (Piece* piece : blackPieces) {
        delete piece;
    }
}
