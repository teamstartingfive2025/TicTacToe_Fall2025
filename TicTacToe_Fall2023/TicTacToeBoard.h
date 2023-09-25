#pragma once
/*
 * board class - TicTacToeBoard
 *     Scope - all aspects of the board, including defining the # rows & columns, win conditions, current/starting player
 *        supports retrieving data elements for displaying the board
 *        ideally, use BOARD_NUM_ROWS and BOARD_NUM_COLS to reference board dimensions
 * constructor - initializes board, initializes player
 * int resetBoard() - initializes board
 * boolean isSquareEmpty(int row, int column) - ultimately, ENUMs
 *    true = empty, false otherwise
 * int writeSquare(int row, int column, char player) ? ENUMsreturns ERROR if can’t write squareif successful, updates to other player
 * char getSquareContents(int row, int column) ? ENUMsreturns character for player (e.g. X, O, blank)
 * char getPlayer()returns player whose turn it is
 */
class TicTacToeBoard
{
#define BOARD_NUM_ROWS 3
#define BOARD_NUM_COLS 3
#define INITIAL_PLAYER 'X'

private:  // reserve memory for board & current player
	char board[BOARD_NUM_ROWS][BOARD_NUM_COLS];      // board storage, indexed by row [0-2] and column [0-2]
	char player = INITIAL_PLAYER;                    // tracks the current player, ie next symbol placed
	int takenSquareCount = 0;                        // # of spaces played in current game, reset for new games


public:
	TicTacToeBoard();
	void resetBoard();
	bool isSquareEmpty(int row, int col) const;
	bool writeSquare(int row, int col, char currentPlayer);  // returns true if successfully written, false on failure
	char getSquareContents(int row, int col);
	char getPlayer();
	char nextPlayer();   // swap player for next move, returns player
	bool isWinner(char playerToCheck); // check if specified player has won
	bool isDraw(); // check if a draw
};