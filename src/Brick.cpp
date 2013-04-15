#include "Brick.h"
#include "Renderer.h"
#include "Vec3.h"

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

	void Brick::NotifyPosition( u32 row, u32 col, BrickAnimation::Type animationType )
	{
		if (animationType != BrickAnimation::None)
		{
			CreateKeyFramesToPos(row, col, animationType);
		}

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

	void Brick::RotateCCW()
	{
		Color::Type first = m_colors[0];
		m_colors[0] = m_colors[1];
		m_colors[1] = m_colors[2];
		m_colors[2] = m_colors[3];
		m_colors[3] = first;
	}

	void Brick::RotateCW()
	{
		Color::Type first = m_colors[3];
		m_colors[3] = m_colors[2];
		m_colors[2] = m_colors[1];
		m_colors[1] = m_colors[0];
		m_colors[0	] = first;
	}

	Vec3 ColorDarken( const Vec3& color )
	{
		double darkMod = 0.8;
		Vec3 newColor = color;// Vec3(darkMod, darkMod, darkMod) * color;
		return newColor;
	}

	Vec3 ColorPuls( const Vec3& color )
	{
		double pulse_time = 2.0;
		double m = cosf((modf(glfwGetTime() / pulse_time, &pulse_time)*2.0-1.0) * M_PI) * 0.2;
		Vec3 pulseCol(color.r > color.g && color.r > color.b, color.g > color.r && color.g > color.b, color.b > color.r && color.b > color.g);
		pulseCol *= m;
		Vec3 newColor = pulseCol + color;
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
		u32 posX = GetX();
		u32 posY = GetY();
		s32 depthOffset = 0;

		if (m_currentAnimation.HasKeyFrames())
		{
			posX = (u32)m_currentAnimation.GetCurrentFrame().position.x;
			posY = (u32)m_currentAnimation.GetCurrentFrame().position.y;
			depthOffset += 2;
		}

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

		glBegin(GL_TRIANGLES);
		{
			glColor3f(brickColor.r, brickColor.g, brickColor.b );
			glVertex3i(posX, posY, depthOffset);
			glColor3f(brickColor.r, brickColor.g, brickColor.b );
			glVertex3i(posX, posY+size, depthOffset);
			glColor3f(brickColor.r, brickColor.g, brickColor.b );
			glVertex3i(posX+size, posY, depthOffset);
			
			// Background upper
			glColor3f(brickColor.r, brickColor.g, brickColor.b );
			glVertex3i(posX+size, posY+size, depthOffset);
			glColor3f(brickColor.r, brickColor.g, brickColor.b );
			glVertex3i(posX+size, posY, depthOffset);
			glColor3f(brickColor.r, brickColor.g, brickColor.b );
			glVertex3i(posX, posY+size, depthOffset);

			// TRI NORTH
			Vec3 color = colors[m_colors[Direction::North]];
			if ( m_colors[Direction::North] == playerColor && m_colors[Direction::North] != Color::Green )
				color = bitsoccer::ColorPuls(color);
			else if ( m_colors[Direction::North] != Color::Green )
				color = bitsoccer::ColorDarken(color);
			
			glColor3f(color.r, color.g, color.b);
			glVertex3i(centerX, centerY, 1+depthOffset);
			glColor3f(color.r, color.g, color.b);
			glVertex3i(centerX+width, centerY+halfSize, 1+depthOffset);
			glColor3f(color.r, color.g, color.b);
			glVertex3i(centerX-width, centerY+halfSize, 1+depthOffset);

			// TRI EAST
			color = colors[m_colors[Direction::East]];
			if ( m_colors[Direction::East] == playerColor && m_colors[Direction::East] != Color::Green )
				color = bitsoccer::ColorPuls(color);
			else if ( m_colors[Direction::East] != Color::Green )
				color = bitsoccer::ColorDarken(color);
			glColor3f(color.r, color.g, color.b);
			glVertex3i(centerX, centerY, 1+depthOffset);
			glColor3f(color.r, color.g, color.b);
			glVertex3i(centerX+halfSize, centerY+width, 1+depthOffset);
			glColor3f(color.r, color.g, color.b);
			glVertex3i(centerX+halfSize, centerY-width, 1+depthOffset);

			// TRI SOUTH
			color = colors[m_colors[Direction::South]];
			if ( m_colors[Direction::South] == playerColor && m_colors[Direction::South] != Color::Green )
				color = bitsoccer::ColorPuls(color);
			else if ( m_colors[Direction::South] != Color::Green )
				color = bitsoccer::ColorDarken(color);
			glColor3f(color.r, color.g, color.b);
			glVertex3i(centerX, centerY, 1+depthOffset);
			glColor3f(color.r, color.g, color.b);
			glVertex3i(centerX+width, centerY-halfSize, 1+depthOffset);
			glColor3f(color.r, color.g, color.b);
			glVertex3i(centerX-width, centerY-halfSize, 1+depthOffset);

			// TRI WEST
			color = colors[m_colors[Direction::West]];
			if ( m_colors[Direction::West] == playerColor && m_colors[Direction::West] != Color::Green )
				color = bitsoccer::ColorPuls(color);
			else if ( m_colors[Direction::West] != Color::Green )
				color = bitsoccer::ColorDarken(color);
			glColor3f(color.r, color.g, color.b);
			glVertex3i(centerX, centerY, 1+depthOffset);
			glVertex3i(centerX-halfSize, centerY+width, 1+depthOffset);
			glVertex3i(centerX-halfSize, centerY-width, 1+depthOffset);
		}		
		glEnd();

		if (m_currentAnimation.HasKeyFrames() && m_currentAnimation.HasPlayedToEnd())
		{
			m_currentAnimation.ClearKeyFrames();
		}
	}

	void Brick::Update(float deltaTime)
	{
		// Update AnimatableObject
		if (m_currentAnimation.HasKeyFrames())
			m_currentAnimation.AddTime(deltaTime);
	}

	///////////////////////////////////////////////////////
	// PRIVATE METHODS
	///////////////////////////////////////////////////////

	void Brick::CreateKeyFramesToPos(u32 row, u32 col, BrickAnimation::Type animationType)
	{
		s32 oldX = GetX();
		s32 oldY = GetY();

		s32	newX = col * (GetSize()+GetMargin()) + m_originX;
		s32	newY = row * (GetSize()+GetMargin()) + m_originY;

		
		const Frame& currentEndFrame = m_currentAnimation.GetLastKeyFrame();

		Frame start;
		start.position = Vec2(oldX, oldY);
		start.rotation = currentEndFrame.rotation;
		start.time = currentEndFrame.time+0.01f;
		m_currentAnimation.AddKeyFrame(start);
		float curTime = start.time;

		/*if (animationType == BrickAnimation::StandardBrick)
		{
			Frame mid = start;
			mid.time = curTime + 2.0f;
			curTime = mid.time;
			m_currentAnimation.AddKeyFrame(mid);
		}*/

		Frame end;
		end.position = Vec2(newX, newY);
		end.rotation = currentEndFrame.rotation; // Const rotation
		end.time = curTime + 1.0f;
		m_currentAnimation.AddKeyFrame(end);

		//printf("start pos: [%.2f, %.2f] rot: %.2f time: %.2f\n", start.position.x, start.position.y, start.rotation, start.time);
		//printf("  end pos: [%.2f, %.2f] rot: %.2f time: %.2f\n", end.position.x, end.position.y, end.rotation, end.time);


	}

	void Brick::CreateKeyFramesToRotate(bool CW)
	{

	}
}
