#include "Ball.h"
#include "Board.h"
namespace bitsoccer
{
	Ball::Ball()
	{
		m_row = 0;
		m_col = 0;
		m_bricks = (Brick*)malloc(sizeof(Brick*)*Directions::NumDirections);
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
		m_bricks[MoveDirection::FromNorth] = board.GetBrick(m_row  ,m_col+1);
		m_bricks[MoveDirection::FromEast ] = board.GetBrick(m_row+1,m_col  );
		if ( m_col > 0 )
			m_bricks[MoveDirection::FromSouth] = board.GetBrick(m_row  ,m_col-1);
		else
			m_bricks[MoveDirection::FromSouth] = 0L;
		if ( m_row > 0 )
			m_bricks[MoveDirection::FromWest ] = board.GetBrick(m_row-1,m_col);
		else
			m_bricks[MoveDirection::FromWest ] = 0L;
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
		if ( m_bricks[MoveDirection::FromNorth] != board.GetBrick(m_row  ,m_col+1) )
			moveDirections |= Directions::North;
		
		if ( m_bricks[MoveDirection::FromEast ] != board.GetBrick(m_row+1,m_col  ) ) 
			moveDirections |= Directions::East
		
		if ( m_col > 0 && m_bricks[MoveDirection::FromSouth] != board.GetBrick(m_row  ,m_col-1) )
			moveDirections |= Directions::South;
	
		if ( m_row > 0 && m_bricks[MoveDirection::FromWest ] != board.GetBrick(m_row-1,m_col) )
			moveDirections |= Directions::West;

		return moveDirections;
	}
}