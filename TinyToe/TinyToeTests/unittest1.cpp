#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\stdafx.h"
#include "..\TinyToeCore.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TinyToeTests
{		
	
	TEST_CLASS(CoreTests)
	{

	public:
		
		TEST_CLASS_INITIALIZE(InitTinyToeCore)
		{
			
		}

		TEST_METHOD(Test_CheckForWinsReturnsCorrectStateForWinningBoard)
		{
			auto test_map = TinyToeCore::WinStateMap();
			test_map[TinyToeCore::GameState::XWIN] = std::vector<TinyToeCore::BoardDescription>{
				0b00'01'00U
			};
			test_map[TinyToeCore::GameState::OWIN] = std::vector<TinyToeCore::BoardDescription>{
				0b10'00'00U
			};
			
			TinyToeCore::BoardDescription x_win_board = 0b00'01'10U;
			TinyToeCore::BoardDescription o_win_board = 0b10'10'01U;

			Assert::IsTrue(TinyToeCore::GameState::XWIN == _CheckForWins(x_win_board, test_map));
			Assert::IsTrue(TinyToeCore::GameState::OWIN == _CheckForWins(o_win_board, test_map));
			Assert::IsFalse(TinyToeCore::GameState::XWIN == _CheckForWins(o_win_board, test_map));
			Assert::IsFalse(TinyToeCore::GameState::OWIN == _CheckForWins(x_win_board, test_map));

		}

		TEST_METHOD(Test_CheckForWinsReturnsUndefinedForBoardsWithMultipleWins)
		{
			auto test_map = TinyToeCore::WinStateMap();
			test_map[TinyToeCore::GameState::XWIN] = std::vector<TinyToeCore::BoardDescription>{
				0b00
			};
			test_map[TinyToeCore::GameState::OWIN] = std::vector<TinyToeCore::BoardDescription>{
				0b00
			};

			TinyToeCore::BoardDescription bad_win_board = 0b00;
			Assert::IsTrue(TinyToeCore::GameState::UNDEFINED == _CheckForWins(bad_win_board, test_map));
		}

	};
}