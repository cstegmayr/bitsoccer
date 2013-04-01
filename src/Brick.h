#pragma once

#include "Types.h"
#include "Renderer.h"

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
		/// Sets the origin of the board, so bricks know where to render.
		void		SetBoardOrigin(int x, int y) { m_originX = x; m_originY = y;}
		/// The size in pixels of the brick
		int			GetSize() const { return 32; }

	private:
		Renderer::HitSurface m_hitSurface;
		Color::Type m_colors[Direction::NumDirections];
		u32 m_row;
		u32 m_col;
		u32 m_originX;
		u32 m_originY;
	};
}
