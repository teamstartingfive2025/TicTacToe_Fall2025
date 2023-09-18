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
	for (int r = 0; r < NUM_ROWS; r++) {
		for (int c = 0; c < NUM_COLS; c++) {
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
	}
	else {
		return(99);
	}
	if (player == 'X')
		player = 'O';
	else
		player = 'X';
}

char TicTacToeBoard::getSquareContents(int row, int col) {
	return board[row][col];
}

char TicTacToeBoard::getPlayer() {
	return player;
}