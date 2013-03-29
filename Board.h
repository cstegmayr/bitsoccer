#pragma once
#include "Brick.h"
#include "Mixer.h"
namespace bitsoccer
{
	class Board {
		
		enum
		{
			kBoardWidth = 8,
			kBoardHeight = 12
		};
	public:
		Board();
		void Initialize( const Mixer* mixer );
		u32 getSize();
		u32 getWidth();
		u32 getHeight();
		~Board();
	private:
		u32 m_width;
		u32 m_height;
		Brick m_board[kBoardWidth][kBoardHeight];
		
		
	};

}
