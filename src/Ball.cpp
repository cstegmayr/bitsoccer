#include "Ball.h"
#include "Board.h"
#include "Brick.h"

namespace bitsoccer
{
	Ball::Ball()
	{
		m_row = 0;
		m_col = 0;
	}

	u32 Ball::GetRow() const
	{
		return m_row;
	}

	u32 Ball::GetCol() const
	{
		return m_col;
	}

	void Ball::SetPosition(u32 row, u32 col, Board& board)
	{
		m_row = row;
		m_col = col;
		m_neighbourBricks[Direction::North] = board.GetBrick(m_row  ,m_col+1);
		m_neighbourBricks[Direction::East ] = board.GetBrick(m_row+1,m_col  );
		if ( m_col > 0 )
			m_neighbourBricks[Direction::South] = board.GetBrick(m_row  ,m_col-1);
		else
			m_neighbourBricks[Direction::South] = 0L;
		if ( m_row > 0 )
			m_neighbourBricks[Direction::West ] = board.GetBrick(m_row-1,m_col);
		else
			m_neighbourBricks[Direction::West ] = 0L;
	}

	void Ball::GetPosition( u32& row, u32& col ) const
	{
		row = m_row;
		col = m_col;
	}

	// return possible to move directions
	u32 Ball::GetMoveDirections( Board& board )
	{
		u32 moveDirections = 0;
		if ( m_neighbourBricks[Direction::North] != board.GetBrick(m_row, m_col+1) )
			moveDirections |= MoveDirection::ToNorth;
		
		if ( m_neighbourBricks[Direction::East ] != board.GetBrick(m_row+1, m_col  ) ) 
			moveDirections |= MoveDirection::ToEast;
		
		if ( m_col > 0 && m_neighbourBricks[Direction::South] != board.GetBrick(m_row, m_col-1) )
			moveDirections |= MoveDirection::ToSouth;
	
		if ( m_row > 0 && m_neighbourBricks[Direction::West ] != board.GetBrick(m_row-1, m_col) )
			moveDirections |= MoveDirection::ToWest;

		return moveDirections;
	}
}