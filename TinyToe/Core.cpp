#include "stdafx.h"
#include "Core.h"

using namespace TinyToe;

namespace
{

	// 0 1 2 3 4 5 6 7 8
	const BoardDescription MIN_BOARD = 0b010101'010101'010101U;
	const BoardDescription MAX_BOARD = 0b111111'111111'111111U;

	const MaskDescription ROW_0_MSK = 0b111111'000000'000000U;
	const MaskDescription ROW_1_MSK = 0b000000'111111'000000U;
	const MaskDescription ROW_2_MSK = 0b000000'000000'111111U;

	const MaskDescription COL_0_MSK = 0b110000'110000'110000U;
	const MaskDescription COL_1_MSK = 0b011000'001100'001100U;
	const MaskDescription COL_2_MSK = 0b000011'000011'000011U;


	// 0 1 2 3 4 5 6 7 8
	const BoardDescription X_ROW_0 = 0b010101'000000'000000U;
	const BoardDescription X_ROW_1 = 0b000000'010101'000000U;
	const BoardDescription X_ROW_2 = 0b000000'000000'010101U;

	const BoardDescription X_COL_0 = 0b010000'010000'010000U;
	const BoardDescription X_COL_1 = 0b000100'000100'000100U;
	const BoardDescription X_COL_2 = 0b000001'000001'000001U;

	const BoardDescription X_DIG_0 = 0b010000'000100'000001U;
	const BoardDescription X_DIG_1 = 0b000001'000100'010000U;

	const BoardDescription O_ROW_0 = 0b111111'000000'000000U;
	const BoardDescription O_ROW_1 = 0b000000'111111'000000U;
	const BoardDescription O_ROW_2 = 0b000000'000000'111111U;

	const BoardDescription O_COL_0 = 0b110000'110000'110000U;
	const BoardDescription O_COL_1 = 0b001100'001100'001100U;
	const BoardDescription O_COL_2 = 0b000011'000011'000011U;

	const BoardDescription O_DIG_0 = 0b110000'001100'000011U;
	const BoardDescription O_DIG_1 = 0b000011'001100'110000U;

	Core::GameState _CheckForWins(BoardDescription board_desc, Core::WinStateMap winstate_map)
	{
		Core::GameState winning_state = Core::GameState::UNDEFINED;
		bool found_one = false;

		for each (auto win_set in winstate_map)
		{
			for each (auto mask_pair in win_set.second)
			{
				if ((board_desc & mask_pair.first) == mask_pair.second)
				{
					if (found_one)
					{
						return Core::GameState::UNDEFINED;
					}
					else
					{
						winning_state = win_set.first;
						found_one = true;
					}
				}
			}
		}

		return winning_state;
	}

	Core::GameState _ScanForTie(BoardDescription board_desc)
	{
		uint32_t board_mask = 0b11;
		uint8_t test_cell;

		//a board is described by 18 bits stored in a uint32. Each cell in the board is described by two bits,
		//as defined in the enum CellState. The bits are stored in row-major order from left to right in the LSB
		// of the board description uint32.

		//this loop looks at each cell in reverse row-major order, searching for an cell with an empty state.
		//if an empty state is found, the game must still be in-progress. Otherwise, the board state must describe a tie
		//(assuming no undefined cells)
		for (uint8_t shift = 0; shift <= 16; shift += 2)
		{
			test_cell = uint8_t((board_desc >> shift) & board_mask);
			if (Core::CellState(test_cell) == Core::CellState::UNDEFINED)
			{
				return Core::GameState::UNDEFINED;
			}
			if (Core::CellState(test_cell) == Core::CellState::EMPTY)
			{
				return Core::GameState::IP;
			}
		}

		return Core::GameState::TIE;
	}
}

Core::Core()
{
	m_GameStateMap = WinStateMap();
	//m_GameStateMap[GameState::XWIN] = std::vector<BoardDescription>{
	//	X_COL_0,
	//	X_COL_1,
	//	X_COL_2,
	//	X_ROW_0,
	//	X_ROW_1,
	//	X_ROW_2,
	//	X_DIG_0,
	//	X_DIG_1
	//};

	//m_GameStateMap[GameState::OWIN] = std::vector<BoardDescription>{
	//	O_COL_0,
	//	O_COL_1,
	//	O_COL_2,
	//	O_ROW_0,
	//	O_ROW_1,
	//	O_ROW_2,
	//	O_DIG_0,
	//	O_DIG_1
	//};

}


Core::~Core()
{

}

Core::GameState Core::CalculateGameState(BoardDescription board_desc)
{
	if (board_desc < MIN_BOARD) return GameState::UNDEFINED;
	if (board_desc > MAX_BOARD) return GameState::UNDEFINED;

	//test for win states

	switch (auto game_state = _CheckForWins(board_desc, m_GameStateMap))
	{
	case GameState::OWIN:
	case GameState::XWIN:
		return game_state;
		break;
	default:
		break;
	}

	//test for tie or in-progress state
	//if any cell is empty, it cannot be a TIE
	auto game_state = _ScanForTie(board_desc);

	return game_state;
}
