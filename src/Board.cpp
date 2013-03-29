#include "Board.h"
#include <assert.h>
#include <math.h>
namespace bitsoccer
{
	Board::Board()
	{
		m_width  = kBoardWidth;
		m_height = kBoardHeight;
		m_initialized = false;
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

	bool Board::SetWidth( u32 width )
	{
		if ( m_initialized )
			return false; 
		m_width = width;
		return true;
	}

	bool Board::SetHeight( u32 height )
	{
		if ( m_initialized )
			return false;
		m_height = height;
		return true;
	}

	u32 Board::CalcIndex(u32 rowIndex, u32 colIndex)
	{
		return m_width*rowIndex + colIndex; 
	}

	void Board::Initialize()
	{
		m_board = (Block*)malloc(sizeof(Block*) * m_width * m_height);
		for (u32 i = 0; i < m_width; ++i)
		{
			for ( u32 j = 0; j < m_height; ++j)
			{
				u32 index = CalcIndex(i,j);
				m_board[index] = new Block();
			}
		}
		m_initialized = true; 
	}

	Brick* Board::GetBrick( u32 row, u32 col )
	{
		u32 index = CalcIndex(row,col);
		assert( index < getSize() );
		if ( index >= getSize() )
			return 0L;
		return m_board[index];
	}

	Brick* Board::Push( Direction::Type dir, u32 row, u32 col, Brick* brick )
	{
		u32 rowIncrement = dir == Direction::East  ? 1 : ( dir == Direction::West  ? -1 : 0 );
		u32 colIncrement = dir == Direction::North ? 1 : ( dir == Direction::South ? -1 : 0 );
		u32 numIterations = fabs( GetWidth()*rowIncrement + GetHeight()*colIncrement);
		for ( u32 i = 0; i < numIterations; ++i ) 
		{
			Brick* tmp = m_board[row + rowIncrement*i ][col + colIncrement*i];
			m_board[row + rowIncrement*i ][col + colIncrement*i] = brick;
			brick = tmp;
		}
		return brick;
	}
	
	Board::~Board()
	{
	}
}
