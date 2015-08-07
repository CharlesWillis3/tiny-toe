#pragma once

namespace TinyToe
{
	typedef uint32_t BoardDescription;
	typedef uint32_t MaskDescription;

	class Core
	{
				
	public:	
		Core();
		~Core();

		enum class CellState : uint8_t
		{
			UNDEFINED = 0b00,
			EMPTY = 0b11,
			X = 0b01,
			O = 0b10
		};

		enum class GameState
		{
			UNDEFINED,
			XWIN,
			OWIN,
			TIE,
			IP
		};
		typedef std::pair<MaskDescription, BoardDescription> DescriptionPair;
		typedef std::map<GameState, std::vector<DescriptionPair>> WinStateMap;

		GameState CalculateGameState(BoardDescription board_desc);

	private:
		WinStateMap m_GameStateMap;
	};
}

