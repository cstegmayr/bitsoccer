#pragma once
#include "Brick.h"


namespace bitsoccer
{
	class Board {
	public:
		Board( u32 width, u32 height );
		void Initialize();
		~Board();
	private:
		u32 m_width;
		u32 m_height;
		Brick* m_board;
		
		
	};

}
