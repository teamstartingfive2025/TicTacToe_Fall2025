// TicTacToe_Fall2023.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "TicTacToeUI.h"
#include "TicTacToeBoard.h"

#define MAX_CHARS 128     // max size of the user output buffer

// User Messages - format intended for sprintf_s
char INTRO_MESSAGE[MAX_CHARS] = "Welcome to Tic Tac Toe, class of Fall 2023!\n";
char ENTER_MOVE[MAX_CHARS] = "Player %c to play, please enter two digits, row[0 - 2] & column[0 - 2] or q to exit: ";
char SHOW_MOVE[MAX_CHARS] = "You entered ... Row: %u\tColumn: %u\n";

// Game over messages
char PLAYER_WIN[MAX_CHARS] = "Player %c has won!\n   Resetting board, q to exit\n";
char PLAYER_DRAW[MAX_CHARS] = "It's a DRAW!\n   Resetting board, q to exit\n";

// Error messages
char INVALID_COMMAND[MAX_CHARS] = "Invalid entry - please try again\n";
char SQUARE_NOT_EMPTY[MAX_CHARS] = "Invalid move!Square already taken - player %c to try again\n";
char EXIT_MESSAGE[MAX_CHARS] = "Thank you for playing\n";



int main()
{
    TicTacToeUI console;    // UI encapsulation - rather than directly writing to console
    TicTacToeBoard board;

    char userString[MAX_CHARS];

    // local variables
    int num_args;   // # of arguments returned from scanner
    char command = '?';   // if command is entered, currently only quit supported ('q')
    unsigned int row;        // row entered by user
    unsigned int col;        // column entered by user

    console.writeOutput(INTRO_MESSAGE);

    // ToDo - game play instuctions
    //
    // Game loop
    //     input options - row/column to play, or exit (can quit at any time)
    //     parse input
    //        command - currently only 'q' for quit or
    //        row & column - two digits, 0-2 (note - board has constants for these values - ToDo)
    //     after parsing input
    //        update the board with the players move (assuming valid move)
    //        check for win or draw
    do {
        console.writeTicTacToeBoard(board); 
        sprintf_s(userString, MAX_CHARS, ENTER_MOVE, board.getPlayer());
        string userInput = console.getUserInput(userString);

        // parse input string for single character
        num_args = sscanf_s(userInput.c_str(), "%c", &command, 1);

        if (num_args == 0) {  // no character entered, digits seem to work okay here
            console.writeOutput(INVALID_COMMAND);
            continue;
        }

        // user wants to exit?
        if ((num_args == 1) && (command == 'q')) {
            console.writeOutput(EXIT_MESSAGE);
            exit(0);
        }

        // Wasn't a command - check if row & column entered
        //   must be two unsigned integers between 0 & 2 (BAD - use board class constants)
        num_args = sscanf_s(userInput.c_str(), "%u %u", &row, &col);
        if ((num_args != 2) || (row > 2) || (col > 2)) {
            console.writeOutput(INVALID_COMMAND);
            continue;
        }
        sprintf_s(userString, MAX_CHARS, SHOW_MOVE, row, col);
        console.writeOutput(userString);


        // core game logic below
        //  if valid move (ie square is empty)
        //    log the move &
        //    check if game is over (win or draw)
        //       congratulate the player & start again
        //  else - user selected a square already taken
        //     politely ask them to try again

        if (board.isSquareEmpty(row, col)) {
            board.writeSquare(row, col, board.getPlayer());


            if (board.isWinner(board.getPlayer())) {  // a win?
                console.writeTicTacToeBoard(board); 
                sprintf_s(userString, MAX_CHARS, PLAYER_WIN, board.getPlayer());
                console.writeOutput(userString);
                board.resetBoard();
            }
            else if (board.isDraw()) {  // a draw?
                console.writeTicTacToeBoard(board); 
                console.writeOutput(PLAYER_DRAW);
                board.resetBoard();
            }

            else {                    // the game goes on
                board.nextPlayer();
            }
        }
        else {        // square already taken
            // cout << "Invalid move! Square already taken - player " << board.getPlayer() << " to try again\n";
            sprintf_s(userString, MAX_CHARS, SQUARE_NOT_EMPTY, board.getPlayer());
            console.writeOutput(userString);
        }
    } while (1);

}


/*  Initial high level design - some changes, primarily validation logic moved into main()
   UI
        handles all input & output to console
        knows how to display the board, uses board object to populate
        adjusts all input to lower case, removes front & trailing white space
        both players, single object

    Board

        captures squares available & taken
        implements win/lose/draw game logic
        tracks turn
        constructor
            selects starting player
            initializes blank board

    Main

        All user messages
        All input validation including context (e.g. row, column, yes/no)
        Orchestrates flow between objects

Sample Use cases
    Startup
        Create UI & board objects
        Display board (passes pointer to board object into UI & user message)
        Request user input for player ? (player queried from board object)blocks on player input

    Player enters valid row & column
        UI returns user input, as entered, without leading & trailing white space
        Main validates row & column are entered correctly

    Player enters invalid row & column
        Main validates user input, invalid
        Main prints appropriate message (e.g. Invalid row/column, please re-enter) & requests user input for player

    Input row & column for empty square
        Main asks board if square empty
        If so, row & column passed to board

    Board asked if player ? has won
        If a win - display board, display winning message, ask if player wants to play again
        if a tie - display board, display draw message, ask if player wants to play again
        if not a win or tie, request next move for other play

    Input row & column for square already taken
        board responds with error
        Display error message, request user input for same player
*/