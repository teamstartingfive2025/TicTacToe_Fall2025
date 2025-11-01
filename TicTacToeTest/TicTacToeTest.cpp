#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include "../TicTacToe_Fall2023/TicTacToeBoard.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TicTacToeTest
{
	TEST_CLASS(TicTacToeTest)
	{
	public:
		TicTacToeBoard board;
		TEST_CLASS_INITIALIZE(Board) {
			// nothing to initialize at the momement
		}
		TEST_METHOD(GameStartPlayerX)
		{
			Logger::WriteMessage("Testing X is selected as first player\n");
			Assert::AreEqual(board.getPlayerName(), 'X');
			Assert::AreNotEqual(board.getPlayerName(), 'O');
		}

		TEST_METHOD(TestMoves) {
			// :writeSquare(int row, int col, char currentPlayer)
			// :getSquareContents(int row, int col)
			// :isSquareEmpty(int row, int col) 
			Logger::WriteMessage("Testing we can write X & O into different cells\n");
			// write cell 0,0 & verify the cell is written correctly
			Assert::IsTrue(board.isSquareEmpty(0, 0));
			board.writeSquare(0, 0, TicTacToeBoard::X);
			Assert::AreEqual('X', board.getSquareContents(0, 0), L"Expected X in 0,0, but received something else");
			Assert::IsFalse(board.isSquareEmpty(0, 0));

			// now test other extreme row 2, column 2, mix it up & write O into this square
			Assert::IsTrue(board.isSquareEmpty(2, 2));
			board.writeSquare(2, 2, TicTacToeBoard::O);
			Assert::AreEqual('O', board.getSquareContents(2, 2), L"Expected O in 2,2, but received something else");
			Assert::IsFalse(board.isSquareEmpty(2, 2));

			// now test something int he middle - e.g. 1, 1
			Assert::IsTrue(board.isSquareEmpty(1, 1));
			board.writeSquare(1,1, TicTacToeBoard::O);
			Assert::AreEqual('O', board.getSquareContents(2, 2), L"Expected O in 1,1, but received something else");
			Assert::IsFalse(board.isSquareEmpty(1,1));
		}
		TEST_METHOD(TestException) {
			Logger::WriteMessage("Testing Exception handling in getSquareContents - throw invalid argument");
			board.getSquareContents(3, 1);  // should throw an exception as 3 is invalid
		}
		TEST_METHOD(InvalidMove) {
			// :writeSquare(int row, int col, char currentPlayer)
			// :getSquareContents(int row, int col)
			// :isSquareEmpty(int row, int col) 
			Logger::WriteMessage("Testing an invalid move 2,3\n");
			Assert::IsTrue(board.isSquareEmpty(2, 3), L"Cell 2,3 is not empty");
			board.writeSquare(2, 3, TicTacToeBoard::X);
			Assert::AreEqual(board.getSquareContents(2, 3), 'X');
			Assert::IsFalse(board.isSquareEmpty(2, 3));
		}
		TEST_METHOD(TestDraw) {
			Logger::WriteMessage("Testing if draws work.");
			board.writeSquare(0, 0, TicTacToeBoard::X);
			board.writeSquare(0, 2, TicTacToeBoard::O);
			board.writeSquare(0, 1, TicTacToeBoard::X);
			board.writeSquare(1, 0, TicTacToeBoard::O);
			board.writeSquare(1, 1, TicTacToeBoard::X);
			board.writeSquare(2, 1, TicTacToeBoard::O);
			board.writeSquare(1, 2, TicTacToeBoard::X);
			board.writeSquare(2, 2, TicTacToeBoard::O);
			board.writeSquare(2, 0, TicTacToeBoard::X);

			Assert::IsTrue(board.isDraw());
			// LV - added verification that not only is Draw condition true
			// but, X & O showing as not winning
			Assert::IsFalse(board.isWinner(TicTacToeBoard::X));
			Assert::IsFalse(board.isWinner(TicTacToeBoard::O));
		}
		TEST_METHOD(TestWinX) {
			Logger::WriteMessage("Testing Win X Validation");
			board.writeSquare(0, 0, TicTacToeBoard::X);
			board.writeSquare(0, 2, TicTacToeBoard::O);
			board.writeSquare(0, 1, TicTacToeBoard::X);
			board.writeSquare(1, 0, TicTacToeBoard::O);
			board.writeSquare(1, 1, TicTacToeBoard::X);
			board.writeSquare(2, 1, TicTacToeBoard::X);
			board.writeSquare(1, 2, TicTacToeBoard::X);
			board.writeSquare(2, 2, TicTacToeBoard::X);
			board.writeSquare(2, 0, TicTacToeBoard::X);
			Assert::IsTrue(board.isWinner(TicTacToeBoard::X));
		}

		// Testing X winning a game
		// scenario:   X  O  X
		//             O  X  X
		//             X  X  X
		//   Note: in this scenario - X wins on 7th move, but continues to fill in additional cells
		// LV - adding precondition checks & also checks b4 and after first winning move
		//   Add error messages if asserts fail
		TEST_METHOD(TestWinX_LV) {
			Logger::WriteMessage("Testing Win X Validation - updated with pre & post asserts");
			// reset the board & verify no winner and no draw
			board.resetBoard();
			Assert::IsFalse(board.isWinner(TicTacToeBoard::X), L"board reset, but X showing as winner");
			Assert::IsFalse(board.isWinner(TicTacToeBoard::O), L"board reset, but O showing as winner");
			Assert::IsFalse(board.isDraw(), L"board reset, but game showing a draw");

			board.writeSquare(0, 0, TicTacToeBoard::X);
			board.writeSquare(0, 2, TicTacToeBoard::O);
			board.writeSquare(0, 1, TicTacToeBoard::X);
			board.writeSquare(1, 0, TicTacToeBoard::O);
			board.writeSquare(1, 1, TicTacToeBoard::X);
			board.writeSquare(1, 2, TicTacToeBoard::X);
			// verify no winner yet
			Assert::IsFalse(board.isWinner(TicTacToeBoard::X), L"Expecting no winner after 6 moves, but showing X won");
			Assert::IsFalse(board.isWinner(TicTacToeBoard::O), L"Expecting no winner after 6 moves, but showing O won");
			Assert::IsFalse(board.isDraw(), L"Expecting no draw after 6 moves, but isDraw returned true!");

			board.writeSquare(2, 1, TicTacToeBoard::X);  // this should be the first winning move (X)
			// now verify that X has won, O hasn't won & there isn't a draw
			Assert::IsTrue(board.isWinner(TicTacToeBoard::X), L"Expecting X as winner, but isWinner() returned false");
			Assert::IsFalse(board.isWinner(TicTacToeBoard::O), L"Expecting only X has won, not O, but showing O won");
			Assert::IsFalse(board.isDraw(), L"Expecting no draw after 7 moves, but isDraw returned true!");

			// write X into the remaining open squares - shouldn't affect outcome
			board.writeSquare(2, 2, TicTacToeBoard::X);
			board.writeSquare(2, 0, TicTacToeBoard::X);

			// verify that X still showing as the winner & O is not
			//   consider that given the Board class doesn't deny moves once a player has won
			//   that X & O can both be showing as winners
			// Net: we should consider improving the class to deny moves after the game is won
			Assert::IsTrue(board.isWinner(TicTacToeBoard::X), L"Expecting X as winner, but isWinner() returned false");
			Assert::IsFalse(board.isWinner(TicTacToeBoard::O), L"Expecting only X has won, not O, but showing O won");
			Assert::IsFalse(board.isDraw(), L"Expecting no draw since X won, but isDraw returned true!");
		}


		TEST_METHOD(TestWinO) {
			Logger::WriteMessage("Testing Win X Validation");   // Note - incorrect player in output message
			board.writeSquare(0, 0, TicTacToeBoard::X);
			board.writeSquare(0, 2, TicTacToeBoard::O);
			board.writeSquare(0, 1, TicTacToeBoard::O);
			board.writeSquare(1, 0, TicTacToeBoard::O);
			board.writeSquare(1, 1, TicTacToeBoard::X);
			board.writeSquare(2, 1, TicTacToeBoard::X);
			board.writeSquare(1, 2, TicTacToeBoard::O);
			board.writeSquare(2, 2, TicTacToeBoard::O);
			board.writeSquare(2, 0, TicTacToeBoard::O);

			Assert::IsTrue(board.isWinner(TicTacToeBoard::O));

		}
		TEST_METHOD(TestReset) {
			Logger::WriteMessage("Testing Reset Board function.");
			board.writeSquare(0, 0, TicTacToeBoard::X);
			board.writeSquare(0, 2, TicTacToeBoard::O);
			board.writeSquare(0, 1, TicTacToeBoard::O);
			board.writeSquare(1, 0, TicTacToeBoard::O);
			board.writeSquare(1, 1, TicTacToeBoard::X);
			board.writeSquare(2, 1, TicTacToeBoard::X);
			board.writeSquare(1, 2, TicTacToeBoard::O);
			board.resetBoard();
			Assert::IsTrue(board.isSquareEmpty(0, 0));
			Assert::IsTrue(board.isSquareEmpty(0, 1));
			Assert::IsTrue(board.isSquareEmpty(0, 2));
			Assert::IsTrue(board.isSquareEmpty(1, 0));
			Assert::IsTrue(board.isSquareEmpty(1, 1));
			Assert::IsTrue(board.isSquareEmpty(1, 2));
			Assert::IsTrue(board.isSquareEmpty(2, 0));
			Assert::IsTrue(board.isSquareEmpty(2, 1));
			Assert::IsTrue(board.isSquareEmpty(2, 2));
		}

	};
}

/* Board class - method description
* Implementation notes :
* -Player enum is used for both the name of the player& for the player's move
* -lots of Technical debt in this implementation, including need to consistently use BOARD_NUM_ROWS and BOARD_NUM_COLS
* - the range for valid rows & columns is [0,2], all other values are invalid
*
* constructor - initializes board via resetBoard() method
* resetBoard() - initializes board & number of turns played in current game
* bool isSquareEmpty(int row, int column) - returns true = empty, false otherwise
* bool writeSquare(int row, int column, Player player) - returns false if can’t write square
* char getSquareContents(int row, int column) - returns character in specified square(e.g. 'X', 'O', ' ')
* Player getPlayer() - returns player(enum) whose turn it is
* char getPlayerName() - returns player(character) whose turn it is
* Player nextPlayer() - returns Player(ie enum) of the next player(e.g. if O playing, returns X)
* bool isWinner(Player playerToCheck) - true if the specified player has won, false otherwise
* bool isDraw() - true if no - one has won, false otherwise(e.g.consider - no spaces empty)
**/

/*
Common Test Automation Asserts including Examples
•	Assert::AreEqual(expected, actual, message): Checks if two values are equal.
		 Assert::AreEqual(5, my_function(2, 3), L"my_function should return 5 for inputs 2 and 3");
•	Assert::AreNotEqual(expected, actual, message): Checks if two values are not equal.
		 Assert::AreNotEqual(0, my_function(1, 0), L"my_function should not return 0 for inputs 1 and 0");
•	Assert::IsTrue(condition, message): Checks if a condition is true.
		Assert::IsTrue(my_object.IsValid(), L"my_object should be valid after initialization");
•	Assert::IsFalse(condition, message): Checks if a condition is false.
		Assert::IsFalse(my_object.IsEmpty(), L"my_object should not be empty after adding elements");
•	Assert::IsNull(pointer, message): Checks if a pointer is null.
		Assert::IsNull(my_pointer, L"my_pointer should be null after deletion");
•	Assert::IsNotNull(pointer, message): Checks if a pointer is not null.
		Assert::IsNotNull(my_pointer, L"my_pointer should not be null after allocation");
•	Assert::Fail(message): Forces a test failure with a specified message.
		Assert::Fail(L"This code path should never be reached");

Important Notes:
•	The message parameter in these methods is optional but highly recommended for providing context about the assertion's purpose, especially when a test fails.
•	The string literals used for messages should be wide-character strings (prefixed with L) to be compatible with the framework.
•	These assertions are part of the Microsoft::VisualStudio::CppUnitTestFramework namespace. You typically include the necessary header and use this namespace in your test files.
C++
	#include "CppUnitTest.h"
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
*/
