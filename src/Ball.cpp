#include "Ball.h"
#include "Board.h"
#include "Brick.h"

namespace bitsoccer
{
	Ball::Ball()
	{
		m_currentBrick = 0L;
	}

	u32 Ball::GetRow() const
	{
		return m_currentBrick->GetRow();
	}

	u32 Ball::GetCol() const
	{
		return m_currentBrick->GetCol();		
	}

	void Ball::SetPosition(u32 row, u32 col, Board& board)
	{
		m_currentBrick = board.GetBrick(row,col);
		m_neighbourBricks[Direction::North] = board.GetBrick(row  ,col+1);
		m_neighbourBricks[Direction::East ] = board.GetBrick(row+1,col  );
		if ( col > 0 )
			m_neighbourBricks[Direction::South] = board.GetBrick(row  ,col-1);
		else
			m_neighbourBricks[Direction::South] = 0L;
		if ( row > 0 )
			m_neighbourBricks[Direction::West ] = board.GetBrick(row-1,col);
		else
			m_neighbourBricks[Direction::West ] = 0L;
	}

	void Ball::GetPosition( u32& row, u32& col ) const
	{
		if ( m_currentBrick == 0L )
		{
			row = 0;
			col = 0;
			return;
		}
		row = m_currentBrick->GetRow();
		col = m_currentBrick->GetCol();
	}

	// return possible to move directions
	u32 Ball::GetMoveDirections( Board& board )
	{
		u32 row;
		u32 col;
		GetPosition(row,col);
		u32 moveDirections = 0;
		if ( m_neighbourBricks[Direction::North] != board.GetBrick(row, col+1) )
			moveDirections |= MoveDirection::ToNorth;
		
		if ( m_neighbourBricks[Direction::East ] != board.GetBrick(row+1, col  ) ) 
			moveDirections |= MoveDirection::ToEast;
		
		if ( col > 0 && m_neighbourBricks[Direction::South] != board.GetBrick(row, col-1) )
			moveDirections |= MoveDirection::ToSouth;
	
		if ( row > 0 && m_neighbourBricks[Direction::West ] != board.GetBrick(row-1, col) )
			moveDirections |= MoveDirection::ToWest;

		return moveDirections;
	}
}