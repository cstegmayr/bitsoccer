#pragma once

namespace bitsoccer
{
	class Brick
	{
	public:
		Brick();
		void        SetColor( Direction::type dir, Color::type color );
		Color::type GetColor( Direction::type );
		bool        IsGoal( Player::Type );

	private:
		u8 m_directions[Direction::NumDirections];
	};
}
