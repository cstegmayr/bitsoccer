#include "Brick.h"
namespace
{
	Brick::Brick()
	{
		// initialize everything green
		for ( u8 i = 0; i < Direction::NumDirections ; ++i )
			m_colors[i] = Color::Green;
	}

	void Brick::SetColor( Direction::type dir, Color::type color )
	{
		m_colors[dir] = color;
	}
	
	Color::type Brick::GetColor( Direction::type dir )
	{
		return m_colors[dir];
	}

	bool Brick::IsGoal( Player::Type player )
	{
		for ( u32 i = 0; i < Direction::NumDirections; ++i )
		{ 
        // Definition of a goal is that all colors are the same.
		// Player::Red == Color::Red and Player::Blue == Color::Blue
			if ( m_colors[i] != player )
				return false; // If any of the colors differ from the player-color, this is no goal
		}
		// All colors are same as player color.
		return true;
	}

	void Brick::rotateCW()
	{	
		u32 prev = m_colors[0];
		for ( u32 i = 0; i < Directions::NumDirections; ++i )
		{
			u32 tmp = m_colors[(i+1)%(Directions::NumDirections)];
			m_colors[(i+1)%(Directions::NumDirections)] = prev;
			prev = tmp;
		}
		m_colors[0]=prev;
	}
}
