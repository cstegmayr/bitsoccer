#include "Board.h"
#include <assert.h>
#include <math.h>
namespace bitsoccer
{
	Board::Board()
	{
		m_width  = kBoardWidth;
		m_height = kBoardHeight;
	}
	
	u32 Board::GetSize()
	{
		return m_width*m_height;
	}
    u32 Board::GetWidth()
	{
		return m_width;
	}

	u32 Board::GetHeight()
	{
		return m_height;
	}

	void Board::Initialize()
	{ 
	}

	Brick Board::GetBrick( u32 row, u32 col )
	{
		assert( index < getSize() );
		return m_board[row][col];
	}

	Brick Board::Push( Direction::Type dir, u32 row, u32 col, Brick brick )
	{
		u32 rowIncrement = dir == Direction::East  ? 1 : ( dir == Direction::West  ? -1 : 0 );
		u32 colIncrement = dir == Direction::North ? 1 : ( dir == Direction::South ? -1 : 0 );
		u32 numIterations = fabs( GetWidth()*rowIncrement + GetHeight()*colIncrement);
		for ( u32 i = 0; i < numIterations; ++i ) 
		{
			Brick tmp = m_board[row + rowIncrement*i ][col + colIncrement*i];
			m_board[row + rowIncrement*i ][col + colIncrement*i] = brick;
			brick = tmp;
		}
		return brick;
	}
	
	Board::~Board()
	{
	}
}
