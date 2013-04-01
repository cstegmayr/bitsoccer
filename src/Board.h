#pragma once
#include "Brick.h"
#include "Mixer.h"
#include "Renderer.h"

namespace bitsoccer
{
	class Ball;

	class Board {
		
		enum
		{
			kBoardWidth = 9,
			kBoardHeight = 13
		};
	public:
		Board();
		void Initialize(u32 x, u32 y);
		u32 GetNumBricks();
		u32 GetWidth();
		bool SetWidth(u32 width);
		u32 GetHeight();
		u32 GetXPosition() const { return m_posX; }
		u32 GetYPosition() const { return m_posY; }
		bool SetHeight(u32 height);
		Brick* GetBrick(u32 row, u32 col);
		u32 CalcIndex(u32 i, u32 j);
		Brick* Push( Direction::Type dir, u32 row, u32 col, Brick* brick );
		u32 GetNumSurroundingHitSurfaces() const;
		Renderer::HitSurface& GetHitSurface( u32 index );
		void Draw( Ball* ball );
		~Board();

	private:
		void SetupHitSurfaces();

		bool m_initialized;
		u32 m_width;
		u32 m_height;
		u32 m_posX;
		u32 m_posY;
		Brick** m_bricks;
		Renderer::HitSurface* m_hitSurfaces;
		
		
		
	};

}
