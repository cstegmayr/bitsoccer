#include "Brick.h"
#include "Renderer.h"

#include <string.h> // For memset

namespace bitsoccer
{
	Brick::Brick()
	: m_row(0)
	, m_col(0)
	, m_originX(0)
	, m_originY(0)
	{
		// initialize everything green
		for (int i = 0; i < Direction::NumDirections; ++i)
			m_colors[i] = Color::Green;

		m_hitSurface.state = HitState::Released;
	}

	void Brick::SetColor( Direction::Type dir, Color::Type color )
	{
		m_colors[dir] = color;
	}
	
	u32 Brick::GetRow() const
	{
		return m_row;
	}

	u32 Brick::GetCol() const
	{
		return m_col;
	}

	void Brick::NotifyPosition( u32 row, u32 col )
	{
		m_row = row;
		m_col = col;

		m_hitSurface.startX = m_col * GetSize() + m_originX;
		m_hitSurface.startY = m_row * GetSize() + m_originY;
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
			if ( m_colors[i] != (Color::Type)player )
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
			Vec3(0.7f, 0.0f, 0.0f), 
			Vec3(0.2f, 0.2f, 0.8f), 
			Vec3(0.0f, 0.6f, 0.0f), 
			Vec3(0.7f, 0.0f, 0.0f), 
			Vec3(0.0f, 0.0f, 0.7f)};

		float halfSize = size / 2.0f;
		float width = halfSize * 0.2f;
		float centerX = posX + halfSize;
		float centerY = posY + halfSize;

		// Background lower
		if (IsGoal(Player::Blue) || IsGoal(Player::Red))
			glColor3f(0.3f, 0.3f, 0.3f);
		else
			glColor3f(0.8f, 0.8f, 0.8f);

		glVertex2f(posX, posY);
		glVertex2f(posX, posY+size);
		glVertex2f(posX+size, posY);
		
		// Background upper
		glVertex2f(posX+size, posY+size);
		glVertex2f(posX+size, posY);
		glVertex2f(posX, posY+size);

		// TRI NORTH
		Vec3 color = colors[m_colors[Direction::North]];
		glColor3f(color.r, color.g, color.b);
		glVertex2f(centerX, centerY);
		glVertex2f(centerX+width, centerY+halfSize);
		glVertex2f(centerX-width, centerY+halfSize);

		// TRI EAST
		color = colors[m_colors[Direction::East]];
		glColor3f(color.r, color.g, color.b);
		glVertex2f(centerX, centerY);
		glVertex2f(centerX+halfSize, centerY+width);
		glVertex2f(centerX+halfSize, centerY-width);

		// TRI SOUTH
		color = colors[m_colors[Direction::South]];
		glColor3f(color.r, color.g, color.b);
		glVertex2f(centerX, centerY);
		glVertex2f(centerX+width, centerY-halfSize);
		glVertex2f(centerX-width, centerY-halfSize);

		// TRI WEST
		color = colors[m_colors[Direction::West]];
		glColor3f(color.r, color.g, color.b);
		glVertex2f(centerX, centerY);
		glVertex2f(centerX-halfSize, centerY+width);
		glVertex2f(centerX-halfSize, centerY-width);
	}
}
