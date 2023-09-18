#pragma once
/*
* board class - TicTacToeBoard

constructor - initializes board, initializes player

int resetBoard() - initializes board

boolean isSquareEmpty(int row, int column) - ultimately, ENUMs

true = empty, false otherwsie

int writeSquare(int row, int column, char player) ? ENUMsreturns ERROR if can’t write squareif successful, updates to other player

char getSquareContents(int row, int column) ? ENUMsreturns character for player (e.g. X, O, blank)

char getPlayer()returns player whose turn it is
*/
class TicTacToeBoard
{
#define NUM_ROWS 3
#define NUM_COLS 3
#define INITIAL_PLAYER 'X'

	char board[NUM_ROWS][NUM_COLS];
	char player;
	int takenSquareCount;



public:
	TicTacToeBoard();
	int resetBoard();
	bool isSquareEmpty(int row, int col);
	int writeSquare(int row, int col, char currentPlayer);
	char getSquareContents(int row, int col);
	char getPlayer();
	char nextPlayer();   // swap player for next move, returns player
	bool isWinner(char playerToCheck); // check if specified player has won
	bool isDraw(); // check if a draw
};

