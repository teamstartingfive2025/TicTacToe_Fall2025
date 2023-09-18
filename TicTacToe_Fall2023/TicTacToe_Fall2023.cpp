// TicTacToe_Fall2023.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "TicTacToeUI.h"
#include "TicTacToeBoard.h"

int main()
{
    TicTacToeUI console;    // UI encapsulation - rather than directly writing to console - ToDo fix issues in parser class
    TicTacToeBoard board;

    string inputSplit[2];   // ToDo - get rid of magic #

    console.writeOutput("Welcome to Tic Tac Toe, class of Fall 2023!\n");
    console.writeTicTacToeBoard(board);

    // write instuctions
    string userInput = console.getUserInput("Enter row & column: ");
    while (userInput[0] != 'q') {
        // braindead parsing of userInput
        int charPos = 0;
        while (isspace(userInput[charPos]) and userInput[charPos] != '\0') { // get rid of leading white space
            charPos++;
            cout << "deleting leading whitespace\n";
            continue;
        }
        while (!isspace(userInput[charPos]) and userInput[charPos] != '\0') {
            inputSplit[0] += userInput[charPos];
            cout << "saving row\n";
            charPos++;
            continue;
        }
        while (isspace(userInput[charPos]) and userInput[charPos] != '\0') { // spaces between row & column
            charPos++;
            cout << "moving past separator\n";
            continue;
        }
        while (!isspace(userInput[charPos]) and userInput[charPos] != '\0') {
            inputSplit[1] += userInput[charPos];
            cout << "saving col\n";
            charPos++;
            continue;
        }
        int row = stoi(inputSplit[0]);
        int col = stoi(inputSplit[1]);
        cout << row << "  " << col << "\n";

        if (board.isSquareEmpty(row, col)) {
            board.writeSquare(row, col, 'X');
            console.writeTicTacToeBoard(board);
        }

        // read next line
        inputSplit[0] = ""; inputSplit[1] = "";
        userInput = console.getUserInput("Enter row & column: ");
    }

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


/*
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