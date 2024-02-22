#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include<iostream>
#include <signal.h>
#include <cstdlib>
#include <SFML/Graphics.hpp>
using namespace std;

#define PORT 8080
#define BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1"

int sock = 0;

void sigintHandler(int sig_num)
{
    close(sock);  
    printf("Closed sockets...\n");
    exit(0);
}

void printBoard(int board [][20])
{
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

void modifyIntoReadable(char buffer[])
{
    char aux= buffer[0];
    buffer[0]=buffer[1]-'0'+'a';
    buffer[1]=('9'-aux+'0')-1;
    aux=buffer[2];
    buffer[2]=buffer[3]-'0'+'a';
    buffer[3]=('9'-aux+'0')-1;
}

void modifyIntoFormat(char move[])
{
    char aux=move[0];
    move[0]=('9'-move[1]+'0')-1;
    move[1]=aux-'a'+'0';
    aux=move[2];
    move[2]=('9'-move[3]+'0')-1;
    move[3]=aux-'a'+'0';
}
void rocada(int xTo, int yTo, int board[][20])
{
    if(xTo == 0)
    {
        if(yTo >4)
        {
            board[0][7]=0;
            board[0][5]=2;
        }
        else
        {
            board[0][0]=0;
            board[0][3]=2;
        }
    }
    else if ( xTo == 7)
    {
        if(yTo >4)
        {
            board[7][7]=0;
            board[7][5]=2;
        }
        else
        {
            board[7][0]=0;
            board[7][3]=2;
        }
    }
}

int main() {
    



    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return -1;
    }
    signal(SIGINT, sigintHandler);
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        return -1;
    }
    int rematch=1;
    while(rematch)
    {
        rematch=0;
        char playerNumber[10];
        int valread = read(sock, playerNumber, sizeof(playerNumber));
        printf("Buffer received %s\n", playerNumber);

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

        printBoard(board);
        char move[10];
        if(playerNumber[0]=='1')
        {
            printf("You play with white pieces!\n");
            int gameActive=1;
            while(gameActive)
            {
                memset(move,0,sizeof(move));
                cin.getline(move,9);    
                if (move[0] == '0' && move[1] == '\0') 
                {
                    send(sock, move, strlen(move), 0);
                    printf("Message to shut off was sent.\n");
                    cout << "Exiting the program...\n";
                    break;
                    return 0; 
                }
                else
                {
                    modifyIntoFormat(move); 
                    send(sock, move, strlen(move), 0);
                    printf("Move sent to server\n");
                }
                
                memset(buffer,0,BUFFER_SIZE);
                valread = read(sock, buffer, BUFFER_SIZE);

                while(buffer[0]=='0')
                {
                    printf("Invalid move. Try again...\n");
                    cin.getline(move,9);
                    if (move[0] == '0' && move[1] == '\0') 
                    {
                        
                        send(sock, move, strlen(move), 0);
                        printf("Message to shut off was sent.\n");
                        cout << "Exiting the program...\n";
                        break; 
                    }
                    
                    modifyIntoFormat(move);

                    send(sock, move, strlen(move), 0);
                    printf("Move sent to server\n");

                    memset(buffer,0,BUFFER_SIZE);
                    int valread = read(sock, buffer, BUFFER_SIZE);
                }
                if(buffer[0]=='1')
                {
                    system("clear");
                    printf("Move made!\n");
                    int xTo=move[2]-'0', yTo=move[3]-'0', xFrom=move[0]-'0', yFrom=move[1]-'0';
                    board[xTo][yTo]=board[xFrom][yFrom];
                    board[xFrom][yFrom]=0;
                    if(abs(board[xTo][yTo]) == 6 && abs(yFrom-yTo) == 2)
                    {
                        rocada(xTo,yTo, board);
                    }
                    printBoard(board);
                }
                if(buffer[0]=='2')
                {
                    printf("White won!\n");
                }
                if(buffer[0]=='3')
                {
                    printf("Black won!\n");
                }
                if(buffer[0] =='2' || buffer[0] == '3')
                {
                    printf("Do you want a rematch? Type 1 for yes and 0 for no.\n");
                    char rematchResponse[10];
                    cin.getline(rematchResponse, 10);
                    send(sock, rematchResponse, strlen(rematchResponse), 0);

                    memset(buffer,0,BUFFER_SIZE);
                    valread = read(sock, buffer, BUFFER_SIZE);

                    if(buffer[0] == '1')
                    {
                        printf("Rematch accepted!\n");
                        rematch=1;
                    }

                    gameActive=0;
                    continue;
                }

                printf("Opponent move: ...\n");
                memset(buffer, 0, BUFFER_SIZE);
                int valread = read(sock, buffer, BUFFER_SIZE);

                if(buffer[0]=='2' && buffer[1]=='\0')
                {
                    printf("White won!\n");
                }
                if(buffer[0]=='3' && buffer[1]=='\0')
                {
                    printf("Black won!\n");
                }
                if( (buffer[0]=='2' && buffer[1]=='\0') || ( buffer[0]=='3' && buffer[1]=='\0'))
                {
                   printf("Do you want a rematch? Type 1 for yes and 0 for no.\n");
                    char rematchResponse[10];
                    cin.getline(rematchResponse, 10);
                    send(sock, rematchResponse, strlen(rematchResponse), 0);

                    memset(buffer,0,BUFFER_SIZE);
                    valread = read(sock, buffer, BUFFER_SIZE);

                    if(buffer[0] == '1')
                    {
                        printf("Rematch accepted!\n");
                        rematch=1;
                    }

                    gameActive=0;
                    continue;
                }
                if(buffer[0]=='9' && buffer[1]=='\0')
                {
                    printf("Opponnent left!\n Shutting down procces...\n");
                    break;
                }

                int xTo=buffer[2]-'0', yTo=buffer[3]-'0', xFrom=buffer[0]-'0', yFrom=buffer[1]-'0';
                board[xTo][yTo]=board[xFrom][yFrom];
                board[xFrom][yFrom]=0;
                if(abs(board[xTo][yTo]) == 6 && abs(yFrom-yTo) == 2)
                {
                    rocada(xTo,yTo, board);
                }
                
                modifyIntoReadable(buffer);
                system("clear");
                printf("Opponent's move: %s\n", buffer);
                printBoard(board);
            }
        }
        else //second player
        {
            printf("You play with black pieces!\n");
            int gameActive=1;
            while(gameActive)
            {
                printf("Opponent move: ...\n");
                memset(buffer,0,BUFFER_SIZE);
                int valread = read(sock, buffer, BUFFER_SIZE);

                if(buffer[0]=='9' && buffer[1]=='\0')
                {
                    printf("Opponnent left!\n Shutting down procces...\n");
                    break;
                }
                if(buffer[0]=='2' && buffer[1]=='\0')
                {
                    printf("White won!\n");
                }
                if(buffer[0]=='3' && buffer[1]=='\0')
                {
                    printf("Black won!\n");
                }
                if( (buffer[0]=='2' && buffer[1]=='\0') || ( buffer[0]=='3' && buffer[1]=='\0'))
                {
                   printf("Do you want a rematch? Type 1 for yes and 0 for no.\n");
                    char rematchResponse[10];
                    cin.getline(rematchResponse, 10);
                    send(sock, rematchResponse, strlen(rematchResponse), 0);

                    memset(buffer,0,BUFFER_SIZE);
                    valread = read(sock, buffer, BUFFER_SIZE);

                    if(buffer[0] == '1')
                    {
                        printf("Rematch accepted!\n");
                        rematch=1;
                    }

                    gameActive=0;
                    continue;
                }
            
                int xTo=buffer[2]-'0', yTo=buffer[3]-'0', xFrom=buffer[0]-'0', yFrom=buffer[1]-'0';
                board[xTo][yTo]=board[xFrom][yFrom];
                board[xFrom][yFrom]=0;
                if(abs(board[xTo][yTo]) == 6 && abs(yFrom-yTo) == 2)
                {
                    rocada(xTo,yTo, board);
                }

                modifyIntoReadable(buffer);

                system("clear");
                printf("Opponent's move: %s\n", buffer);
                printBoard(board);

                memset(move,0,sizeof(move));
                cin.getline(move,9);
                if (move[0] == '0' && move[1] == '\0') 
                {
                    send(sock, move, strlen(move), 0);
                    printf("Message to shut off was sent.\n");
                    cout << "Exiting the program...\n";
                    break;
                    return 0; 
                }
                else
                {
                    modifyIntoFormat(move);
                    send(sock, move, strlen(move), 0);
                    printf("Move sent to server\n");
                }
                

                valread = read(sock, buffer, BUFFER_SIZE);
                while(buffer[0]=='0')
                {
                    printf("Invalid move. Try again...\n");
                    cin.getline(move,9);
                    if (move[0] == '0' && move[1] == '\0') 
                    {
                        
                        send(sock, move, strlen(move), 0);
                        printf("Message to shut off was sent.\n");
                        cout << "Exiting the program...\n";
                        break; 
                    }
                    modifyIntoFormat(move);
                    send(sock, move, strlen(move), 0);
                    printf("Move sent to server\n");

                    memset(buffer,0,BUFFER_SIZE);
                    int valread = read(sock, buffer, BUFFER_SIZE);
                }
                if(buffer[0]=='1')
                {
                    system("clear");
                    printf("Move made!\n");
                    int xTo=move[2]-'0', yTo=move[3]-'0', xFrom=move[0]-'0', yFrom=move[1]-'0';
                    board[xTo][yTo]=board[xFrom][yFrom];
                    board[xFrom][yFrom]=0;
                    if(abs(board[xTo][yTo]) == 6 && abs(yFrom-yTo) == 2)
                    {
                        rocada(xTo,yTo, board);
                    }
                    printBoard(board);
                }
                if(buffer[0]=='2')
                {
                    printf("White won!\n");
                }
                if(buffer[0]=='3')
                {
                    printf("Black won!\n");
                }
                if(buffer[0] =='2' || buffer[0] == '3')
                {
                    printf("Do you want a rematch? Type 1 for yes and 0 for no.\n");
                    char rematchResponse[10];
                    cin.getline(rematchResponse, 10);
                    send(sock, rematchResponse, strlen(rematchResponse), 0);

                    memset(buffer,0,BUFFER_SIZE);
                    valread = read(sock, buffer, BUFFER_SIZE);

                    if(buffer[0] == '1')
                    {
                        printf("Rematch accepted!\n");
                        rematch=1;
                    }

                    gameActive=0;
                    continue;
                }
                
            }
        }
    }
    
    close(sock);
    printf("Closed socket...\n");
    return 0;
}