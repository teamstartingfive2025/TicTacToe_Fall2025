

// TicTacToeUI.cpp
//   Encapsulates the methods to read & write to the UI (for now, the console)

#include <iostream>
#include <stdlib.h>
#include "TicTacToeUI.h"

/* Tic Tac Toe UI Class
 * Scope:
 *   Handles all reads & writes to console (or in the future, a graphical window)
 *   Singleton class (for now) - uses console
 *
 * Methods:
 *      getUserInput() writes prompt to console, blocks on user input (terminated by new line), returns input
 *      writeOutput()  writes output to console & returns 0 indicating no error,
 *        in future write errors may contain an error code
 *      writeTicTacToeBoard() writes blank board to console
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

string TicTacToeUI::getUserInput(string prompt) {
    string userInput;

    writeOutput(prompt);
    getline(cin, userInput);
    return userInput;
}

// writeOutput()
//   writes passed string to console
int TicTacToeUI::writeOutput(string output) {
    cout << output;
    return(0);
}

// writeTicTacToeBoard()
//   initially keep it simple, hard code everything
// ToDo: switch to a formatted print, retrieving contents from board class
int TicTacToeUI::writeTicTacToeBoard() {
    cout << "   |   |   \n";  // row 0
    cout << "_________\n";
    cout << "   |   |   \n";  // row 1
    cout << "_________\n";
    cout << "   |   |   \n";  // row 2
    return(0);
}
