#pragma once
#include "Brick.h"
#include "Mixer.h"
#include "Renderer.h"

namespace bitsoccer
{
	class Board {
		
		enum
		{
			kBoardWidth = 8,
			kBoardHeight = 12
		};
	public:
		Board();
		void Initialize();
		u32 GetSize();
		u32 GetWidth();
		bool SetWidth(u32 width);
		u32 GetHeight();
		bool SetHeight(u32 height);
		Brick* GetBrick(u32 row, u32 col);
		u32 CalcIndex(u32 i, u32 j);
		Brick* Push( Direction::Type dir, u32 row, u32 col, Brick* brick );

		void Draw();
		~Board();

	private:
		void SetupHitSurfaces();

		bool m_initialized;
		u32 m_width;
		u32 m_height;
		Brick** m_bricks;
		Renderer::HitSurface* m_hitSurfaces;
		
		
	};

}
