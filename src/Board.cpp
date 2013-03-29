#include "Board.h"
namespace bitsoccer
{
	Board::Board()
	{
		m_width  = kBoardWidth;
		m_height = kBoardHeight;
	}
	
	u32 Board::getSize()
	{
		return m_width*m_height;
	}
    u32 Board::getWidth()
	{
		return m_width;
	}

	u32 Board::getHeight()
	{
		return m_height;
	}

	void Board::Initialize( const MixerBase* mixer )
	{ 
	}
	
	Board::~Board()
	{
	}
}
