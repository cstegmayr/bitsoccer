#pragma once
#include "Types.h"
namespace bitsoccer
{
	class Board;
	class Brick;

	class Ball
	{
	public:
		Ball();
		void Draw();
		void SetPosition( u32  row, u32  col, Board& board );
		void GetPosition( u32& row, u32& col ) const;
		u32 GetRow() const;
		u32 GetCol() const;
		// return possible directions to go
		u32 GetMoveDirections(Board& board);

	private:
		Brick* m_currentBrick;
		Brick* m_neighbourBricks[Direction::NumDirections];
	};
}