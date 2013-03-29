#pragma once
#include "Brick.h"
<<<<<<< HEAD:Board.h
#include "Mixer.h"
=======


>>>>>>> a433352657e109ea9a34a43b0d535c2f809f6203:src/Board.h
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
