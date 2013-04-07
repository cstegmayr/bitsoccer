#include "Brick.h"
#include "Renderer.h"

#include <string.h> // For memset
#define _USE_MATH_DEFINES
#include <math.h>

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
		m_hitSurface.width = GetSize();
		m_hitSurface.height = GetSize();

		Renderer::RegisterHitSurface(&m_hitSurface);
	}

	Brick::~Brick()
	{		
		Renderer::UnregisterHitSurface(&m_hitSurface);
	}

	void Brick::SetColor( Direction::Type dir, Color::Type color )
	{
		m_colors[dir] = color;
	}

	void Brick::NotifyPosition( u32 row, u32 col )
	{
		m_row = row;
		m_col = col;

		m_hitSurface.startX = GetX();
		m_hitSurface.startY = GetY();
	}

	Color::Type Brick::GetColor( Direction::Type dir ) const
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

	void Brick::RotateCW()
	{
		Color::Type first = m_colors[0];
		m_colors[0] = m_colors[1];
		m_colors[1] = m_colors[2];
		m_colors[2] = m_colors[3];
		m_colors[3] = first;
	}

	void Brick::RotateCCW()
	{
		Color::Type first = m_colors[3];
		m_colors[3] = m_colors[2];
		m_colors[2] = m_colors[1];
		m_colors[1] = m_colors[0];
		m_colors[0] = first;
	}

	Vec3 ColorDarken( const Vec3& color )
	{
		double darkMod = 0.8;
		Vec3 newColor = color;// Vec3(darkMod, darkMod, darkMod) * color;
		return newColor;
	}

	Vec3 ColorPuls( const Vec3& color )
	{
		double currentTimeMod = 0.0;
		double dummy = 2.0;
		currentTimeMod = fabs(cosf(modf(glfwGetTime() / dummy, &dummy) * M_PI)) * 0.2 + 0.1;
		Vec3 newColor = Vec3(currentTimeMod+color.r, currentTimeMod+color.g, currentTimeMod+color.b);
		return newColor;
	}

	void Brick::Draw(BrickMode::Type brickMode, Color::Type playerColor)
	{
		const Vec3 colors[] = {
			Vec3(0.7f, 0.0f, 0.0f),  // Red
			Vec3(0.2f, 0.2f, 0.8f),  // Blue
			Vec3(0.0f, 0.6f, 0.0f),  // Green
			Vec3(0.7f, 0.0f, 0.0f),  // RedGoal
			Vec3(0.0f, 0.0f, 0.7f)}; // BlueGoal

		u32 size = GetSize();
		u32 posX = m_col * (size+GetMargin()) + m_originX;
		u32 posY = m_row * (size+GetMargin()) + m_originY;

		u32 halfSize = size / 2;
		u32 width = 8;
		u32 centerX = posX + halfSize;
		u32 centerY = posY + halfSize;
		
		Vec3 brickColor(0.5f, 0.5f, 0.5f);

		if ( brickMode == BrickMode::Normal )
			brickColor  = Vec3( 0.8f, 0.8f, 0.8f );

		if ( brickMode & BrickMode::RedGoal )
			brickColor = brickColor * Vec3( 1.0f, 0.0f, 0.0f );

		if (  brickMode & BrickMode::BlueGoal )
			brickColor = brickColor * Vec3( 0.0f, 0.0f, 1.0f );

		if (  brickMode & BrickMode::PossibleMove )
			brickColor = brickColor * Vec3( 1.9f, 0.05f, 1.9f );

		glColor3f(brickColor.r, brickColor.g, brickColor.b );
		glVertex3i(posX, posY, 0);
		glVertex3i(posX, posY+size, 0);
		glVertex3i(posX+size, posY, 0);
		
		// Background upper
		glVertex3i(posX+size, posY+size, 0);
		glVertex3i(posX+size, posY, 0);
		glVertex3i(posX, posY+size, 0);

		// TRI NORTH
		Vec3 color = colors[m_colors[Direction::North]];
		if ( m_colors[Direction::North] == playerColor && m_colors[Direction::North] != Color::Green )
			color = bitsoccer::ColorPuls(color);
		else if ( m_colors[Direction::North] != Color::Green )
			color = bitsoccer::ColorDarken(color);
		
		glColor3f(color.r, color.g, color.b);
		glVertex3i(centerX, centerY, 1);
		glVertex3i(centerX+width, centerY+halfSize, 1);
		glVertex3i(centerX-width, centerY+halfSize, 1);

		// TRI EAST
		color = colors[m_colors[Direction::East]];
		if ( m_colors[Direction::East] == playerColor && m_colors[Direction::East] != Color::Green )
			color = bitsoccer::ColorPuls(color);
		else if ( m_colors[Direction::East] != Color::Green )
			color = bitsoccer::ColorDarken(color);
		glColor3f(color.r, color.g, color.b);
		glVertex3i(centerX, centerY, 1);
		glVertex3i(centerX+halfSize, centerY+width, 1);
		glVertex3i(centerX+halfSize, centerY-width, 1);

		// TRI SOUTH
		color = colors[m_colors[Direction::South]];
		if ( m_colors[Direction::South] == playerColor && m_colors[Direction::South] != Color::Green )
			color = bitsoccer::ColorPuls(color);
		else if ( m_colors[Direction::South] != Color::Green )
			color = bitsoccer::ColorDarken(color);
		glColor3f(color.r, color.g, color.b);
		glVertex3i(centerX, centerY, 1);
		glVertex3i(centerX+width, centerY-halfSize, 1);
		glVertex3i(centerX-width, centerY-halfSize, 1);

		// TRI WEST
		color = colors[m_colors[Direction::West]];
		if ( m_colors[Direction::West] == playerColor && m_colors[Direction::West] != Color::Green )
			color = bitsoccer::ColorPuls(color);
		else if ( m_colors[Direction::West] != Color::Green )
			color = bitsoccer::ColorDarken(color);
		glColor3f(color.r, color.g, color.b);
		glVertex3i(centerX, centerY, 1);
		glVertex3i(centerX-halfSize, centerY+width, 1);
		glVertex3i(centerX-halfSize, centerY-width, 1);
	}
}
