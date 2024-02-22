# Chess-Server-Client

This project is a chess server and client implemented in the C++ programming language. The main purpose of this project is to provide a platform where two or more players can interact in a game of chess through a connection to the server. The implementation is done using object-oriented programming (OOP) concepts.

Communication between the server and clients is done through sockets. This ensures the correct and secure transmission of information regarding the moves made by the players.

The server verifies and validates the moves sent by the clients, and provides them with correct information about the opponent's moves in real-time. If a client sends an invalid move, the server waits to receive another command until it receives a valid one.

A key feature of this server is the implementation of concurrency using the fork() function in UNIX-based operating systems. This approach allows the server to handle connections from multiple clients simultaneously without affecting the performance and reliability of the system.

The server uses the "Game" class, which contains two vectors of pointers to "Piece". "Piece" is an abstract class inherited by all types of pieces and contains methods such as "moveTo", "typeOfPiece", and "changeCoord". The "Game" class processes the moves received from clients through the "movePiece" method, which returns 1 if the move was valid. Furthermore, the server transmits this result to the client who sent the move to indicate that it was valid and also transmits the move to the other client.
