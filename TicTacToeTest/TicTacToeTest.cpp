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
			// write a cell & verify the cell is written correctly
			Assert::IsTrue(board.isSquareEmpty(0, 0));
			board.writeSquare(0, 0, TicTacToeBoard::X);
			Assert::AreEqual(board.getSquareContents(0, 0), 'X');
			Assert::IsFalse(board.isSquareEmpty(0, 0));
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

	};
}
