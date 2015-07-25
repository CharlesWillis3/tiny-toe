#pragma once

namespace TinyToe
{
	class TinyToeCore
	{
				
	public:	
		TinyToeCore();
		~TinyToeCore();

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

	protected:
		GameState _CheckForWins(BoardDescription board_desc);

	private:
		BoardDescriptionToGameStateMap m_GameStateMap;
	};
}

