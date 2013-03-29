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

	private:
		Color::Type m_colors[Direction::NumDirections];
	};
}
