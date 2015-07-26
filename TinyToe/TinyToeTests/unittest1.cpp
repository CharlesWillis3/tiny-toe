#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\stdafx.h"
#include "..\Core.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TinyToeTests
{

	TEST_CLASS(CoreTests)
	{

	public:

		TEST_CLASS_INITIALIZE(InitCore)
		{

		}

		TEST_METHOD(XRowsReturnXWIN)
		{
			auto test_map = Core::WinStateMap();

			test_map[Core::GameState::XWIN] = std::vector<Core::DescriptionPair>{
				std::make_pair(ROW_0_MSK, X_ROW_0),
				std::make_pair(ROW_1_MSK, X_ROW_1),
				std::make_pair(ROW_2_MSK, X_ROW_2)
			};

			BoardDescription x_row_0_board = 0b010101'101011'101111;
			BoardDescription x_row_1_board = 0b101011'010101'111010;
			BoardDescription x_row_2_board = 0b101011'101011'010101;

			Assert::IsTrue(Core::GameState::XWIN == _CheckForWins(x_row_0_board, test_map));
			Assert::IsTrue(Core::GameState::XWIN == _CheckForWins(x_row_1_board, test_map));
			Assert::IsTrue(Core::GameState::XWIN == _CheckForWins(x_row_2_board, test_map));

		}

		TEST_METHOD(XColsReturnXWIN)
		{
			auto test_map = Core::WinStateMap();

			test_map[Core::GameState::XWIN] = std::vector<Core::DescriptionPair>{
				std::make_pair(COL_0_MSK, X_COL_0),
				std::make_pair(COL_1_MSK, X_COL_1),
				std::make_pair(COL_2_MSK, X_COL_2)
			};

			BoardDescription x_col_0_board = 0b010111'011011'011111;
			BoardDescription x_col_1_board = 0b100111'010101'111010;
			BoardDescription x_col_2_board = 0b101001'101001'010101;

			Assert::IsTrue(Core::GameState::OWIN == _CheckForWins(x_col_0_board, test_map));
			Assert::IsTrue(Core::GameState::OWIN == _CheckForWins(x_col_1_board, test_map));
			Assert::IsTrue(Core::GameState::OWIN == _CheckForWins(x_col_2_board, test_map));

		}

	};
}