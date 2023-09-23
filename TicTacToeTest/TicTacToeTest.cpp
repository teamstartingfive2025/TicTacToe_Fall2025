#include "pch.h"
#include "CppUnitTest.h"
#include "../TicTacToe_Fall2023/TicTacToeBoard.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TicTacToeTest
{
	TEST_CLASS(TicTacToeTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			TicTacToeBoard board;
			Assert::AreEqual(board.getPlayer(), 'X');
			Assert::AreNotEqual(board.getPlayer(), 'O');
		}
	};
}
