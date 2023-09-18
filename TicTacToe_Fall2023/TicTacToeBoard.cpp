#include "TicTacToeBoard.h"
#include <iostream>
#include <stdlib.h>

/*
 * ToDo - Validate row & columns
 * ToDo - create ENUM for players
 * ToDo - create ENUM for entries in board
 * ToDo - create define or constant for Error returns
*/

// empty constructor
TicTacToeBoard::TicTacToeBoard() {
	resetBoard();
	player = INITIAL_PLAYER;  // ToDo - move this to a helper function within the class, e.g. setPlayer()
}

int TicTacToeBoard::resetBoard() {
	takenSquareCount = 0;
	for (int r = 0; r < BOARD_NUM_ROWS; r++) {
		for (int c = 0; c < BOARD_NUM_COLS; c++) {
			board[r][c] = ' ';
		}
	}
	return (0);
}

bool TicTacToeBoard::isSquareEmpty(int row, int col) {
	if (board[row][col] == ' ')
		return true;
	else
		return false;
}

int TicTacToeBoard::writeSquare(int row, int col, char currentPlayer) {
	if (this -> isSquareEmpty(row, col)) {
		board[row][col] = currentPlayer;
		takenSquareCount++;
	}
	else {
		return(99);
	}
}

char TicTacToeBoard::getSquareContents(int row, int col) {
	return board[row][col];
}

char TicTacToeBoard::getPlayer() {
	return player;
}

char TicTacToeBoard::nextPlayer() {
	if (player == 'X')
		player = 'O';
	else
		player = 'X';
	return player;
}

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
	if ((takenSquareCount >= BOARD_NUM_ROWS * BOARD_NUM_COLS) && !this->isWinner('X') and !this->isWinner('O')) {
		return (true);
	}
	else
		return(false);
}