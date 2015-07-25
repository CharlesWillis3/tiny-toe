#include "stdafx.h"
#include "TinyToeCore.h"

using namespace TinyToe;

namespace
{

	// 0 1 2 3 4 5 6 7 8
	const TinyToeCore::BoardDescription MIN_BOARD = 0b010101010101010101;
	const TinyToeCore::BoardDescription MAX_BOARD = 0b111111111111111111;

	// 0 1 2 3 4 5 6 7 8
	const TinyToeCore::BoardDescription X_ROW_0 = 0b101010000000000000;
	const TinyToeCore::BoardDescription X_ROW_1 = 0b000000101010000000;
	const TinyToeCore::BoardDescription X_ROW_2 = 0b000000000000101010;

	const TinyToeCore::BoardDescription X_COL_0 = 0b100000100000100000;
	const TinyToeCore::BoardDescription X_COL_1 = 0b001000001000001000;
	const TinyToeCore::BoardDescription X_COL_2 = 0b000010000010000010;

	const TinyToeCore::BoardDescription X_DIG_0 = 0b100000001000000010;
	const TinyToeCore::BoardDescription X_DIG_1 = 0b000010001000100000;

	const TinyToeCore::BoardDescription O_ROW_0 = 0b111111000000000000;
	const TinyToeCore::BoardDescription O_ROW_1 = 0b000000111111000000;
	const TinyToeCore::BoardDescription O_ROW_2 = 0b000000000000111111;

	const TinyToeCore::BoardDescription O_COL_0 = 0b110000110000110000;
	const TinyToeCore::BoardDescription O_COL_1 = 0b001100001100001100;
	const TinyToeCore::BoardDescription O_COL_2 = 0b000011000011000011;

	const TinyToeCore::BoardDescription O_DIG_0 = 0b110000001100000011;
	const TinyToeCore::BoardDescription O_DIG_1 = 0b000011001100110000;
}

TinyToeCore::TinyToeCore()
{
	m_GameStateMap = BoardDescriptionToGameStateMap();
	m_GameStateMap[X_ROW_0] = GameState::XWIN;
	m_GameStateMap[X_ROW_1] = GameState::XWIN;
	m_GameStateMap[X_ROW_2] = GameState::XWIN;
	m_GameStateMap[X_COL_0] = GameState::XWIN;
	m_GameStateMap[X_COL_1] = GameState::XWIN;
	m_GameStateMap[X_COL_2] = GameState::XWIN;
	m_GameStateMap[X_DIG_0] = GameState::XWIN;
	m_GameStateMap[X_DIG_1] = GameState::XWIN;

	m_GameStateMap[O_ROW_0] = GameState::OWIN;
	m_GameStateMap[O_ROW_1] = GameState::OWIN;
	m_GameStateMap[O_ROW_2] = GameState::OWIN;
	m_GameStateMap[O_COL_0] = GameState::OWIN;
	m_GameStateMap[O_COL_1] = GameState::OWIN;
	m_GameStateMap[O_COL_2] = GameState::OWIN;
	m_GameStateMap[O_DIG_0] = GameState::OWIN;
	m_GameStateMap[O_DIG_1] = GameState::OWIN;
}


TinyToeCore::~TinyToeCore()
{

}

TinyToeCore::GameState TinyToeCore::CalculateGameState(BoardDescription board_desc)
{
	if (board_desc < MIN_BOARD) return GameState::UNDEFINED;
	if (board_desc > MAX_BOARD) return GameState::UNDEFINED;

	//test for win states
	
	switch (auto game_state = _CheckForWins(board_desc))
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
			if (CellState(test_cell) == CellState::UNDEFINED)
			{
				return GameState::UNDEFINED;
			}
			if (CellState(test_cell) == CellState::EMPTY)
			{
				return GameState::IP;
			}
		}
	}

	return GameState::TIE;
}

TinyToeCore::GameState TinyToe::TinyToeCore::_CheckForWins(BoardDescription board_desc)
{
	for each (auto i in m_GameStateMap)
	{
		if ((board_desc & i.first) == i.first)
		{
			return i.second;
		}
	}

	return GameState::UNDEFINED;
}
