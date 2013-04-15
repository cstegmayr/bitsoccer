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
		u32 GetNumBricks() const;
		u32 GetWidth() const;
		bool SetWidth(u32 width);
		u32 GetHeight() const;
		void SetPosition(u32 x, u32 y);
		u32 GetXPosition() const { return m_posX; }
		u32 GetYPosition() const { return m_posY; }
		bool SetHeight(u32 height);
		Brick* GetBrick(u32 row, u32 col);
		Direction::Type GetOppositeDirection( Direction::Type dir ) const;
		const Brick* GetBrick(u32 row, u32 col) const;
		u32 CalcIndex(u32 i, u32 j) const;
		Brick* Push( Direction::Type dir, u32 row, u32 col, Brick* brick );

		u32 GetNumSurroundingHitSurfaces() const;
		Renderer::HitSurface& GetHitSurface( u32 index );

		/// Hit surface helpers
		Direction::Type GetDirectionFromIndex(u32 hitSurfaceIndex);
		void GetRowColumnFromIndex(u32 hitSurfaceIndex, u32& row, u32& col);
		u32 GetPossibleColorMoveDirections( u32 row, u32 col, Color::Type playerColor ) const;
		bool GetMovePathForColor( const Ball* ball, const u32 row, const u32 col, const Color::Type playerColor ) const;
		u32 GetBrickType( Ball* ball, MoveDirection::Type movableColorDirs, u32 h, u32 w);
		void Draw( Ball* ball, MoveDirection::Type movableColorDirs, Color::Type playerColor );
		void Update(float deltaTime);
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
