#include "Brick.h"
#include "Renderer.h"

#include <string.h> // For memset

namespace bitsoccer
{
	Brick::Brick()
	{
		// initialize everything green
		for (int i = 0; i < Direction::NumDirections; ++i)
			m_colors[i] = Color::Green;
	}

	void Brick::SetColor( Direction::Type dir, Color::Type color )
	{
		m_colors[dir] = color;
	}
	
	Color::Type Brick::GetColor( Direction::Type dir )
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
		Color::Type prev = m_colors[0];
		for ( u32 i = 0; i < Direction::NumDirections; ++i )
		{
			Color::Type tmp = m_colors[(i+1)%(Direction::NumDirections)];
			m_colors[(i+1)%(Direction::NumDirections)] = prev;
			prev = tmp;
		}
		m_colors[0] = prev;
	}

	void Brick::Draw(float posX, float posY, float size)
	{
		Vec3 colors[] = {
			Vec3(1.0f, 0.0f, 0.0f), 
			Vec3(0.0f, 0.0f, 1.0f), 
			Vec3(0.0f, 1.0f, 0.0f), 
			Vec3(0.7f, 0.0f, 0.0f), 
			Vec3(0.0f, 0.0f, 0.7f)};

		float halfSize = size / 2.0f;
		float centerX = posX + halfSize;
		float centerY = posY + halfSize;

		// TRI NORTH
		Vec3 color = colors[m_colors[Direction::North]];
		glColor3f(color.r, color.g, color.b);
		glVertex2f(centerX, centerY);
		glVertex2f(centerX-halfSize, centerY+halfSize);
		glVertex2f(centerX+halfSize, centerY+halfSize);

		// TRI EAST
		color = colors[m_colors[Direction::East]];
		glColor3f(color.r, color.g, color.b);
		glVertex2f(centerX, centerY);
		glVertex2f(centerX+halfSize, centerY+halfSize);
		glVertex2f(centerX+halfSize, centerY-halfSize);

		// TRI SOUTH
		color = colors[m_colors[Direction::South]];
		glColor3f(color.r, color.g, color.b);
		glVertex2f(centerX, centerY);
		glVertex2f(centerX+halfSize, centerY-halfSize);
		glVertex2f(centerX-halfSize, centerY-halfSize);

		// TRI WEST
		color = colors[m_colors[Direction::West]];
		glColor3f(color.r, color.g, color.b);
		glVertex2f(centerX, centerY);
		glVertex2f(centerX-halfSize, centerY-halfSize);
		glVertex2f(centerX-halfSize, centerY+halfSize);
	}
}
