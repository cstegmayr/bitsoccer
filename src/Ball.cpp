#include "Ball.h"
#include "Board.h"
#include "Brick.h"

#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

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

	u32 Ball::GetMovableColorDirections( Board& board )
	{
		u32 directions = 0;

		u32 row = m_currentBrick->GetRow();
		u32 col = m_currentBrick->GetCol();

		Brick* northBrick = 0L;
		
		if ( row + 1 < board.GetHeight() )
			northBrick = board.GetBrick(row+1,col);
		Brick* eastBrick  = 0L;
		if ( col + 1 < board.GetWidth() ) 
			eastBrick = board.GetBrick(row  ,col+1);
		Brick* southBrick = 0L;
		if (row > 0)
			southBrick = board.GetBrick(row-1,col);
		Brick* westBrick = 0L;
		if (col > 0 )
			westBrick = board.GetBrick(row,col-1);

		if ( northBrick != 0L && ( m_currentBrick->GetColor(Direction::North) == northBrick->GetColor(Direction::South) || northBrick->GetColor(Direction::South) == Color::Green ) )
			directions |= MoveDirection::ToNorth;
		
		if ( eastBrick != 0L && ( m_currentBrick->GetColor(Direction::East) == eastBrick->GetColor(Direction::West) || eastBrick->GetColor(Direction::West) == Color::Green ) )
			directions |= MoveDirection::ToEast;

		
		if ( southBrick != 0L && ( m_currentBrick->GetColor(Direction::South) == southBrick->GetColor(Direction::North) ||  southBrick->GetColor(Direction::North) == Color::Green ) )
			directions |= MoveDirection::ToSouth;
		
		if ( westBrick != 0L && ( m_currentBrick->GetColor(Direction::West) == westBrick->GetColor(Direction::East) || westBrick->GetColor(Direction::East) == Color::Green ) )
			directions |= MoveDirection::ToWest;
	

		return directions;
	}

	// return possible to move directions
	u32 Ball::GetChangedDirections( Board& board )
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
		u32 brickSize = Brick::GetSize();
		u32 posX = m_currentBrick->GetX();
		u32 posY = m_currentBrick->GetY();

		float centerX = (float)(posX + brickSize / 2);
		float centerY = (float)(posY + brickSize / 2);
		float radius = (float)(brickSize / 4);

		double currentTimeMod = 0.0;
		double dummy = 2.0;
		currentTimeMod = fabs(cosf(modf(glfwGetTime() / 2.0, &dummy) * M_PI)) * 0.7f;

		u32 numSeg = 8;
		float inc = 1.0f / (float)numSeg;
		for (int i = 0; i < numSeg; ++i)
		{
			float p0 = (float)i * inc;
			float x0 = cosf(p0*M_PI*2.0) * radius + centerX;
			float y0 = sinf(p0*M_PI*2.0) * radius + centerY;
			float p1 = (float)(i+1) * inc;
			float x1 = cosf(p1*M_PI*2.0) * radius + centerX;
			float y1 = sinf(p1*M_PI*2.0) * radius + centerY;

			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex2f(centerX, centerY);
			glColor3f(currentTimeMod, currentTimeMod, currentTimeMod);
			glVertex2f(x0, y0);
			glColor3f(currentTimeMod, currentTimeMod, currentTimeMod);
			glVertex2f(x1, y1);
		}

	}
}