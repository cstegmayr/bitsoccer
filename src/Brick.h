#pragma once

#include "Types.h"

namespace bitsoccer
{
	class Brick
	{
	public:
		Brick();
		void        SetColor( Direction::Type dir, Color::Type color );
		Color::Type GetColor( Direction::Type );
		bool        IsGoal( Player::Type );
		void        rotateCW();
		void        rotateCCW();
		void		Draw(float posX, float posY, float size);
		void		NotifyPosition( u32 row, u32 col );
		u32			GetRow() const;	
		u32			GetCol() const;	

	private:
		Color::Type m_colors[Direction::NumDirections];
		u32 m_row;
		u32 m_col;
	};
}
