

// TicTacToeUI.cpp
//   Encapsulates the methods to read & write to the UI (for now, the console)

#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include "TicTacToeUI.h"
#include "TicTacToeBoard.h"  // required for displaying board which is maintained by the board class

/* Tic Tac Toe UI Class
 * Scope:
 *   Handles all reads & writes to console (or in the future, a graphical window)
 *   Singleton class (for now) - uses console
 *
 * Methods:
 *      getUserInput() writes prompt to console, blocks on user input (terminated by new line), returns input
 *      writeOutput()  writes output to console & returns 0 indicating no error,
 *        in future write errors may contain an error code
 *      writeTicTacToeBoard(board) displays current board to console
 *
 * Instance Variables:
 *   None
 */


 // empty constructor
TicTacToeUI::TicTacToeUI() {

}


// getUserInput()
//   prompts user with string included in call
//   waits for user input, echoes the input & returns it to caller
//     note: does not trim leading white space

string TicTacToeUI::getUserInput(string prompt) {
    string userInput;

    writeOutput(prompt);
    getline(cin, userInput);
        // convert to lower case, requires algorithm library
    transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);
    return userInput;
}

// writeOutput()
//   writes passed string to console
int TicTacToeUI::writeOutput(string output) {
    cout << output;
    return(0);
}

// Draws board based on data from board class
// Issues - hard coding last row & column to avoid drawing delimiter - e.g. |

int TicTacToeUI::writeTicTacToeBoard(TicTacToeBoard board) {
    // loop thru all rows and all columns, retrieving contents from board class & displaying
    cout << "\n";
    for (int r = 0; r < BOARD_NUM_ROWS; r++) {
        for (int c = 0; c < BOARD_NUM_COLS; c++) {
            cout << " " << board.getSquareContents(r,c);
            if (c < BOARD_NUM_COLS - 1)
                cout << " |";
        }
        if (r < BOARD_NUM_ROWS - 1)
            cout << "\n------------\n";
        else
            cout << "\n\n";
    }
    return(0);
}
