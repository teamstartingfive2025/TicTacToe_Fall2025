#include "TicTacToeBoard.h"
#include <iostream>
#include <stdlib.h>

/*
 * ToDo - Validate row & columns everywhere  (highest priority - poor OO coding!!!
 * ToDo - create ENUM for players
 * ToDo - create ENUM for entries in board
 * ToDo - create define or constant for Error returns
*/

/*
 * Instance variables
 *   board[][] - two dimensional array indexed by row (0-2) & column (0-2), cleared when starting a new game
 *   takenSquareCount - integer tracking # of moves in the game, reset at instance creation & on starting a new game
 *   player - character indicating the player making the current move
 *     notes - default player defined in board class header file,
 *     current player is tracked and can be retrived by the board class, but is updated from outside the class via nextPlayer()
 */

// Constructor
//   reset board, player intialized in .h file when memory allocated
TicTacToeBoard::TicTacToeBoard() {
	resetBoard();
}

// reset the board and the instance variable tracking # of spaces played
//   ToDo - bad - hardcoded empty space as a ' ', really should use enums
void TicTacToeBoard::resetBoard() {
	takenSquareCount = 0;
	for (int r = 0; r < BOARD_NUM_ROWS; r++) {
		for (int c = 0; c < BOARD_NUM_COLS; c++) {
			board[r][c] = ' ';
		}
	}
}

// checking if a given space is empty - returns true if empty
bool TicTacToeBoard::isSquareEmpty(int row, int col) const {
	if (board[row][col] == ' ')
		return true;
	else
		return false;
}

// updates a space to the player (character) specified
//   ToDo - bad - not validating row & col prior to indexing into array
bool TicTacToeBoard::writeSquare(int row, int col, char currentPlayer) {
	if (this -> isSquareEmpty(row, col)) {
		board[row][col] = currentPlayer;
		takenSquareCount++;
		return true;
	}
	else {
		return false;
	}
}

// returns character (ie player marker) in the given row/col
char TicTacToeBoard::getSquareContents(int row, int col) {
	return board[row][col];
}

// returns the current player
char TicTacToeBoard::getPlayer() {
	return player;
}

// updates the player who has the next turn
//   ToDo - hardcoded the players here, bad coding practice, should use enums
char TicTacToeBoard::nextPlayer() {
	if (player == 'X')
		player = 'O';
	else
		player = 'X';
	return player;
}

// checks if the specified player has won the game
//   ToDo - tighten up this check - works but could be cleaner
bool TicTacToeBoard::isWinner(char playerToCheck) {
	// check rows
	for (int r = 0; r < BOARD_NUM_ROWS; r++) {
		if ((board[r][0] == playerToCheck) &&
			(board[r][1] == playerToCheck) &&
			(board[r][2] == playerToCheck))
			return(true);
	}

	// check columns
	for (int c = 0; c < BOARD_NUM_COLS; c++) {
		if ((board[0][c] == playerToCheck) &&
			(board[1][c] == playerToCheck) &&
			(board[2][c] == playerToCheck))
			return(true);
	}

	// check diagonals
	if ((board[0][0] == playerToCheck) &&
		(board[1][1] == playerToCheck) &&
		(board[2][2] == playerToCheck))
			return(true);
	// reverse
	if ((board[0][2] == playerToCheck) &&
		(board[1][1] == playerToCheck) &&
		(board[2][0] == playerToCheck))
			return(true);

	return(false);              // no winner this time
}


// Draw - all squares filled and no one has one
bool TicTacToeBoard::isDraw() {
	if ((takenSquareCount >= BOARD_NUM_ROWS * BOARD_NUM_COLS) && !this->isWinner('X') && !this->isWinner('O')) {
		return (true);
	}
	else
		return(false);
}