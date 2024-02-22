#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include<cstring>
#include "Game.cpp"
#include "Pawn.cpp"



#include <stdio.h> 
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <utmp.h>
#include <time.h>
#include <string.h>
#include <netinet/in.h>
#include <signal.h>


using namespace std;

#define PORT 8080
#define BUFFER_SIZE 1024
int server_fd;
void sigintHandler(int sig_num)
{
    close(server_fd);  
    printf("Closed socket...\n");
    exit(0);
}

void handleGame(int new_socket1, int new_socket2)
{

    char buffer[BUFFER_SIZE];
    char player1[]="1";
    char player2[]="2";
    
    int rematch=1;



    while(rematch)
    {
        printf("New game started..\n");
        send(new_socket1, player1, strlen(player1), 0);
        send(new_socket2, player2, strlen(player2), 0);
        
        rematch=0;
    
        Game game;
        game.setUpGame();
        game.printPieces();
        char responseValid[10];
        const char* responseInvalid="Invalid format of move received!\n";
        int gameActive=1;
        while(gameActive)
        {
            int wasValidMove=0;
            //printf("First move..\n");
            while(wasValidMove==0)
            {
                memset(buffer, 0, sizeof(buffer));
                int valread = read(new_socket1, buffer, BUFFER_SIZE);
                printf("Received message from client: %s\n", buffer);
                
                

                if (buffer[0] == '0' && buffer[1] == '\0') 
                {
                    cout << "Exiting the program...\n";
                    responseValid[0]='9';
                    responseValid[1]='\0';
                    send(new_socket2, responseValid, strlen(responseValid), 0);
                    close(new_socket1);
                    close(new_socket2);
                    close(server_fd);
                    printf("Sockets closed...\n");
                    return ;

                }
                if(buffer[0]>='0' && buffer[0]<='9'&& 
                buffer[1]>='0' && buffer[1]<='9'&& 
                buffer[2]>='0' && buffer[2]<='9'&& 
                buffer[3]>='0' && buffer[3]<='9'&&
                buffer[4]=='\0')
                {
                    int resultOfMove=game.movePiece(buffer[0]-'0',buffer[1]-'0',buffer[2]-'0',buffer[3]-'0');
                    if(resultOfMove == 1) 
                    {
                        responseValid[0]='1';
                        responseValid[1]='\0';
                        send(new_socket1, responseValid, strlen(responseValid), 0);
                        send(new_socket2, buffer, strlen(buffer), 0);
                        printf("Response 1 sent to client\n");
                        wasValidMove=1;
                    }
                    else if(resultOfMove == 2) //white won
                    {
                        responseValid[0]='2';
                        responseValid[1]='\0';
                        send(new_socket1, responseValid, strlen(responseValid), 0);
                        send(new_socket2, responseValid, strlen(responseValid), 0);

                        printf("Response 2 sent to client\n");
                    }
                    else if(resultOfMove== 3) //black won
                    {
                        responseValid[0]='3';
                        responseValid[1]='\0';
                        send(new_socket1, responseValid, strlen(responseValid), 0);
                        send(new_socket2, responseValid, strlen(responseValid), 0);
                        printf("Response 3 sent to client\n");
                    }
                    else //invalid move
                    {
                        responseValid[0]='0';
                        responseValid[1]='\0';
                        send(new_socket1, responseValid, strlen(responseValid), 0);
                        printf("Response 0 sent to client\n");
                    }
                    if(resultOfMove == 3 || resultOfMove == 2) //check for rematch
                    {
                        int rem=0;
                        memset(buffer, 0, sizeof(buffer));
                        printf("Asking first player for rematch..\n");
                        int valread = read(new_socket1, buffer, BUFFER_SIZE);
                        
                        if(buffer[0] == '1')
                        {
                            printf("Player 1 wants rematch!\n"); 
                            rem++;
                        }
                        printf("Asking second player for rematch..\n");
                        memset(buffer, 0, sizeof(buffer));
                        valread = read(new_socket2, buffer, BUFFER_SIZE);
                        if(buffer[0] == '1')
                        {
                            printf("Player 2 wants rematch!\n"); 
                            rem++;
                        }
                        if (rem == 2)
                            rematch=1;
                        //printf("rem:%d\n", rem);
                        gameActive=0;
                        responseValid[0]='0';
                        responseValid[1]='\0';
                        if(rematch)
                        {
                            responseValid[0]='1';
                            responseValid[1]='\0';
                        }
                        send(new_socket1, responseValid, strlen(responseValid), 0);
                        send(new_socket2, responseValid, strlen(responseValid), 0);


                        goto end;
                    }
                }
                else //if the message received is not the right format 
                {
                    responseValid[0]='0';
                    responseValid[1]='\0';
                    send(new_socket1, responseValid, strlen(responseValid), 0);
                    printf("Invalid format sent to client\n");
                }
                game.printPieces();
            }
            wasValidMove=0;
            //printf("Asteapta mutarea 2\n");
            while(wasValidMove==0)
            {
                memset(buffer, 0, sizeof(buffer));

                int valread = read(new_socket2, buffer, BUFFER_SIZE);
                printf("Received message from client: %s\n", buffer);
                
                

                if (buffer[0] == '0' && buffer[1] == '\0') 
                {
                    cout << "Exiting the program...\n";
                    responseValid[0]='9';
                    responseValid[1]='\0';
                    send(new_socket1, responseValid, strlen(responseValid), 0);
                    close(new_socket1);
                    close(new_socket2);
                    close(server_fd);
                    printf("Sockets closed...\n");
                    return;
                }
                if(buffer[0]>='0' && buffer[0]<='9'&& 
                buffer[1]>='0' && buffer[1]<='9'&& 
                buffer[2]>='0' && buffer[2]<='9'&& 
                buffer[3]>='0' && buffer[3]<='9'&&
                buffer[4]=='\0')
                {
                    int resultOfMove=game.movePiece(buffer[0]-'0',buffer[1]-'0',buffer[2]-'0',buffer[3]-'0');
                    if(resultOfMove == 1) 
                    {
                        responseValid[0]='1';
                        responseValid[1]='\0';
                        send(new_socket2, responseValid, strlen(responseValid), 0);
                        send(new_socket1, buffer, strlen(buffer), 0);
                        printf("Response 1 sent to client\n");
                        wasValidMove=1;
                    }
                    else if(resultOfMove == 2) //white won
                    {
                        responseValid[0]='2';
                        responseValid[1]='\0';
                        send(new_socket2, responseValid, strlen(responseValid), 0);
                        send(new_socket1, responseValid, strlen(responseValid), 0);
                        printf("Response 2 sent to client\n");
                    }
                    else if(resultOfMove== 3) //black won
                    {
                        responseValid[0]='3';
                        responseValid[1]='\0';
                        send(new_socket2, responseValid, strlen(responseValid), 0);
                        send(new_socket1, responseValid, strlen(responseValid), 0);
                        printf("Response 3 sent to client\n");
                    }
                    else //invalid move
                    {
                        responseValid[0]='0';
                        responseValid[1]='\0';
                        send(new_socket2, responseValid, strlen(responseValid), 0);
                        printf("Response 0 sent to client\n");
                    }
                    if(resultOfMove == 3 || resultOfMove == 2) //check for rematch
                    {
                        int rem=0;
                        memset(buffer, 0, sizeof(buffer));
                        printf("Asking first player for rematch..\n");
                        int valread = read(new_socket1, buffer, BUFFER_SIZE);
                        
                        if(buffer[0] == '1')
                        {
                            printf("Player 1 wants rematch!\n"); 
                            rem++;
                        }
                        printf("Asking second player for rematch..\n");
                        memset(buffer, 0, sizeof(buffer));
                        valread = read(new_socket2, buffer, BUFFER_SIZE);
                        if(buffer[0] == '1')
                        {
                            printf("Player 2 wants rematch!\n"); 
                            rem++;
                        }
                        if (rem == 2)
                            rematch=1;
                        gameActive=0;
                        responseValid[0]='0';
                        responseValid[1]='\0';
                        if(rematch)
                        {
                            responseValid[0]='1';
                            responseValid[1]='\0';
                        }
                        send(new_socket1, responseValid, strlen(responseValid), 0);
                        send(new_socket2, responseValid, strlen(responseValid), 0);


                        goto end;
                    }
                }
                else //if the message received is not the right format 
                {
                    responseValid[0]='0';
                    responseValid[1]='\0';
                    send(new_socket2, responseValid, strlen(responseValid), 0);
                    printf("Invalid format sent to client\n");
                }
                game.printPieces();
            }
            end:
            printf("End of loop\n");
        }
    }
    close(new_socket1);
    close(new_socket2);
    exit(0);
}

int main()
{
    
    
    printf("Server started...\n");
    
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *response = "Message received by the server";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Socket created...\n");

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Bind done...\n");

    if (listen(server_fd, 2) < 0) { // Listen for up to 2 connections
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Listening done...\n");

    signal(SIGINT, sigintHandler);
    

    while(1)
    {
        int new_socket1, new_socket2;

        if ((new_socket1 = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }
        printf("First client connected, socket fd is %d\n", new_socket1);
        if ((new_socket2 = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        printf("Second client connected, socket fd is %d\n", new_socket2);

        pid_t pid=fork();

        if(pid==-1)
        {
            perror("Fork failed!");
            exit(EXIT_FAILURE);
        }
        else if(pid == 0) //child procces
        {
            handleGame(new_socket1, new_socket2);
        }
        else
        {
            close(new_socket1);
            close(new_socket2);
        }
        
    }
        cout << endl;
        close(server_fd);
        printf("Socket closed...\n");
    return 0;

    
}