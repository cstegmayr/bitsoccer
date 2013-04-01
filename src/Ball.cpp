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

	u32 Ball::GetSameColorDirections( Board& board )
	{
		u32 directions = 0;

		u32 row = m_currentBrick->GetRow();
		u32 col = m_currentBrick->GetCol();

		Brick* northBrick = board.GetBrick(row+1,col);
		Brick* eastBrick  = board.GetBrick(row  ,col+1);
		Brick* southBrick = 0L;
		if (row > 0)
			southBrick = board.GetBrick(row-1,col);
		Brick* westBrick = 0L;
		if (col > 0 )
			westBrick = board.GetBrick(row,col-1);

		if ( m_currentBrick->GetColor(Direction::North) == northBrick->GetColor(Direction::South) )
			directions |= MoveDirection::ToNorth;
		
		if ( m_currentBrick->GetColor(Direction::East) == northBrick->GetColor(Direction::West) )
			directions |= MoveDirection::ToEast;

		
		if ( southBrick != 0L && m_currentBrick->GetColor(Direction::South) == southBrick->GetColor(Direction::North) )
			directions |= MoveDirection::ToSouth;
		
		if ( westBrick != 0L && m_currentBrick->GetColor(Direction::West) == westBrick->GetColor(Direction::East) )
			directions |= MoveDirection::ToWest;
	

		return directions;
	}

	// return possible to move directions
	u32 Ball::GetMoveDirections( Board& board )
	{
		u32 row;
		u32 col;
		GetPosition(row,col);
		u32 moveDirections = 0;
		if ( m_neighbourBricks[Direction::North] != board.GetBrick( row+1, col) )
			moveDirections |= MoveDirection::ToNorth;
		
		if ( m_neighbourBricks[Direction::East ] != board.GetBrick( row, col+1 ) ) 
			moveDirections |= MoveDirection::ToEast;
		
		if ( row > 0 && m_neighbourBricks[Direction::South] != board.GetBrick( row-1, col) )
			moveDirections |= MoveDirection::ToSouth;
	
		if ( col > 0 && m_neighbourBricks[Direction::West ] != board.GetBrick(row, col-1) )
			moveDirections |= MoveDirection::ToWest;

		return moveDirections;
	}

	void Ball::Draw( Board& board )
	{
		float brickWidth = board.GetBrickWidth();
		float radius = brickWidth * 0.3f;
		float posX = (m_currentBrick->GetCol() + 1.0f ) * brickWidth;
		float posY = (m_currentBrick->GetRow() + 1.0f ) * brickWidth;

		float centerX = posX + brickWidth*0.5f;
		float centerY = posY + brickWidth*0.5f;
		glColor3f(0.0f, 0.0f, 0.0f );

		// TRI NORTH
		glVertex2f(centerX, centerY);
		glVertex2f(centerX+radius, centerY+radius);
		glVertex2f(centerX-radius, centerY+radius);


	}
}