#pragma once

namespace TinyToe
{
	class TinyToeCore
	{
				
	public:	
		TinyToeCore();
		~TinyToeCore();

		enum class CellShift
		{
			_0_0 = 16,
			_0_1 = 14,
			_0_2 = 12,

			_1_0 = 10,
			_1_1 = 8,
			_1_2 = 6,

			_2_0 = 4,
			_2_1 = 2,
			_2_2 = 0
		};

		enum class CellState : uint8_t
		{
			UNDEFINED = 0b00,
			EMPTY = 0b01,
			X = 0b10,
			O = 0b11
		};

		enum class GameState
		{
			UNDEFINED,
			XWIN,
			OWIN,
			TIE,
			IP
		};

		typedef uint32_t BoardDescription;
		typedef std::map<BoardDescription, GameState> BoardDescriptionToGameStateMap;

		GameState CalculateGameState(BoardDescription board_desc);

	private:
		BoardDescriptionToGameStateMap m_GameStateMap;
	};
}

