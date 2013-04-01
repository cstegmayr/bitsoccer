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
		m_neighbourBricks[Direction::North] = board.GetBrick(row+1,col  );
		m_neighbourBricks[Direction::East ] = board.GetBrick(row  ,col+1);
		if ( row > 0 )
			m_neighbourBricks[Direction::South] = board.GetBrick(row-1, col);
		else
			m_neighbourBricks[Direction::South] = 0L;
		if ( col > 0 )
			m_neighbourBricks[Direction::West ] = board.GetBrick(row, col-1);
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

	void Ball::Draw( Board& board )
	{
		float brickWidth = board.GetBrickWidth();
		float radius = brickWidth * 0.3f;
		float posX = m_currentBrick->GetCol()*brickWidth;
		float posY = m_currentBrick->GetRow()*brickWidth;

		float centerX = posX + brickWidth*0.5f;
		float centerY = posY + brickWidth*0.5f;
		glColor3f(0.0f, 0.0f, 0.0f );

		// TRI NORTH
		glVertex2f(centerX, centerY);
		glVertex2f(centerX+radius, centerY+radius);
		glVertex2f(centerX-radius, centerY+radius);


	}
}