#pragma once

#include "Types.h"
#include "Renderer.h"
#include "AnimatableObject.h"

namespace bitsoccer
{
	class Brick
	{
	public:
		Brick();
		~Brick();
		void        SetColor( Direction::Type dir, Color::Type color );
		Color::Type GetColor( Direction::Type ) const;
		bool        IsGoal( Player::Type );
		bool		IsPressed() const { return m_hitSurface.state == HitState::Pressed; }
		void        RotateCW();
		void        RotateCCW();
		void		Draw(BrickMode::Type brickMode, Color::Type playerColor);
		void		Update(float deltaTime);
		void		NotifyPosition( u32 row, u32 col, BrickAnimation::Type animationType );
		void		NotifyPauseInAnimation();
		u32			GetRow() const { return m_row; }	
		u32			GetCol() const { return m_col; }
		u32			GetX() const { return m_col * (GetSize()+GetMargin()) + m_originX; }
		u32			GetY() const { return m_row * (GetSize()+GetMargin()) + m_originY; }
		float		GetRotation() const { return m_currentAnimation.GetCurrentFrame().rotation; }
		/// Sets the origin of the board, so bricks know where to render.
		void		SetBoardOrigin(int x, int y) { m_originX = x; m_originY = y;}
		/// The size in pixels of the brick
		static u32	GetSize() { return 32; }
		static u32	GetMargin() { return 1; }

	private:
		void CreateKeyFramesToPos(u32 row, u32 col, BrickAnimation::Type animationType);
		void CreateKeyFramesToRotate(bool CW);

		Renderer::HitSurface m_hitSurface;
		Color::Type m_colors[Direction::NumDirections];
		AnimatableObject m_currentAnimation;
		u32 m_row;
		u32 m_col;
		u32 m_originX;
		u32 m_originY;
	};
}
