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
	
	Color::type Brick::SetColor( Direction::type dir )
	{
		return m_colors[dir];
	}

	bool Brick::IsGoal( Player::Type player )
	{
		for ( u32 i = 0; i < Direction::NumDirections; ++i )
		{
			if ( m_colors[i] != player )
				return false;
		}
		return true;
	}
}
