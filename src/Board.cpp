#include "Board.h"
#include "Ball.h"
#include "Types.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>
//#include <iostream>
#include <memory.h>

namespace bitsoccer
{
	Board::Board()
		: m_initialized(false)
		, m_width(kBoardWidth)
		, m_height(kBoardHeight)
		, m_posX(0)
		, m_posY(0)
		, m_bricks(0)
		, m_hitSurfaces(0)

	{
	}

	void Board::Draw( Ball* ball )
	{	
		for (u32 w = 0; w < m_width; ++w)
		{
			for (u32 h = 0; h < m_height; ++h)
			{
				Brick* b = GetBrick(h, w);
				u32 brickType = (u32)BrickMode::Normal;
				Brick* ballBrick = GetBrick( ball->GetRow(), ball->GetCol() );
				MoveDirection::Type movableColorDirs = (MoveDirection::Type)ball->GetMovableColorDirections(*this);
				if	( 
					( movableColorDirs & MoveDirection::ToNorth && h > 0 && w     == ball->GetCol() && h - 1 == ball->GetRow() ) ||
					( movableColorDirs & MoveDirection::ToEast  && w > 0 && w - 1 == ball->GetCol() && h     == ball->GetRow() ) ||
					( movableColorDirs & MoveDirection::ToSouth &&          w     == ball->GetCol() && h + 1 == ball->GetRow() ) ||
					( movableColorDirs & MoveDirection::ToWest  &&          w + 1 == ball->GetCol() && h     == ball->GetRow() )   
					)
					brickType |= (u32)BrickMode::PossibleMove;
				if ( b->IsGoal(Player::Red) )
					brickType |= BrickMode::RedGoal;
				if ( b->IsGoal(Player::Blue) )
					brickType |= BrickMode::BlueGoal;
				b->Draw( (BrickMode::Type)brickType );
			}
		}
	}
	
	u32 Board::GetNumBricks()
	{
		return m_width*m_height;
	}
    u32 Board::GetWidth()
	{
		return m_width;
	}

	u32 Board::GetHeight()
	{
		return m_height;
	}

	bool Board::SetWidth( u32 width )
	{
		if ( m_initialized )
			return false; 
		m_width = width;
		return true;
	}

	bool Board::SetHeight( u32 height )
	{
		if ( m_initialized )
			return false;
		m_height = height;
		return true;
	}

	u32 Board::CalcIndex(u32 rowIndex, u32 colIndex)
	{
		return m_width*rowIndex + colIndex; 
	}

	void Board::SetupHitSurfaces()
	{
		m_hitSurfaces = (Renderer::HitSurface*)malloc(sizeof(Renderer::HitSurface) * 2 * (m_width + m_height));
		int currentSurface = 0;
		u32 brickSize = Brick::GetSize();

		// Lower buttons
		for (u32 i = 0; i < m_width; ++i)
		{
			m_hitSurfaces[currentSurface].startX = i * (brickSize+Brick::GetMargin()) + m_posX;
			m_hitSurfaces[currentSurface].startY = -(brickSize+Brick::GetMargin()) + m_posY;
			m_hitSurfaces[currentSurface].width = brickSize;
			m_hitSurfaces[currentSurface].height = brickSize;
			m_hitSurfaces[currentSurface].state = HitState::Released;

			Renderer::RegisterHitSurface(&m_hitSurfaces[currentSurface]);

			++currentSurface;
		}

		// Upper buttons
		for (u32 i = 0; i < m_width; ++i)
		{
			m_hitSurfaces[currentSurface].startX = i * (brickSize+Brick::GetMargin()) + m_posX;
			m_hitSurfaces[currentSurface].startY = (m_height) * (brickSize+Brick::GetMargin()) + m_posY;
			m_hitSurfaces[currentSurface].width = brickSize;
			m_hitSurfaces[currentSurface].height = brickSize;
			m_hitSurfaces[currentSurface].state = HitState::Released;

			Renderer::RegisterHitSurface(&m_hitSurfaces[currentSurface]);

			++currentSurface;
		}

		// Left buttons
		for (u32 i = 0; i < m_height; ++i)
		{
			m_hitSurfaces[currentSurface].startX = -(brickSize+Brick::GetMargin()) + m_posX;
			m_hitSurfaces[currentSurface].startY = i * (brickSize+Brick::GetMargin()) + m_posY;
			m_hitSurfaces[currentSurface].width = brickSize;
			m_hitSurfaces[currentSurface].height = brickSize;
			m_hitSurfaces[currentSurface].state = HitState::Released;

			Renderer::RegisterHitSurface(&m_hitSurfaces[currentSurface]);

			++currentSurface;
		}

		// Right buttons
		for (u32 i = 0; i < m_height; ++i)
		{
			m_hitSurfaces[currentSurface].startX = m_width * (brickSize+Brick::GetMargin()) + m_posX;
			m_hitSurfaces[currentSurface].startY = i * (brickSize+Brick::GetMargin()) + m_posY;
			m_hitSurfaces[currentSurface].width = brickSize;
			m_hitSurfaces[currentSurface].height = brickSize;
			m_hitSurfaces[currentSurface].state = HitState::Released;

			Renderer::RegisterHitSurface(&m_hitSurfaces[currentSurface]);

			++currentSurface;
		}
	}

	void Board::SetPosition(u32 x, u32 y)
	{
		m_posX = x; m_posY = y;
		for (u32 i = 0; i < m_height; ++i)
		{
			for ( u32 j = 0; j < m_width; ++j)
			{
				u32 index = CalcIndex(i,j);
				m_bricks[index]->SetBoardOrigin(x, y);
			}
		}
	}

	void Board::Initialize(u32 x, u32 y)
	{
		if (m_bricks == 0)
		{
			m_bricks = (Brick**)malloc(sizeof(Brick*) * m_width * m_height);
			for (u32 i = 0; i < m_height; ++i)
			{
				for ( u32 j = 0; j < m_width; ++j)
				{
					u32 index = CalcIndex(i,j);
					m_bricks[index] = new Brick();
				}
			}
		}

		SetPosition(x, y);
		SetupHitSurfaces();

		m_initialized = true; 
	}

	Brick* Board::GetBrick( u32 row, u32 col )
	{
		u32 index = CalcIndex(row,col);
		if ( index >= GetNumBricks() )
			return 0;
		return m_bricks[index];
	}

	Brick* Board::Push( Direction::Type dir, u32 row, u32 col, Brick* brick )
	{
		s32 rowIncrement = dir == Direction::North  ? 1 : ( dir == Direction::South  ? -1 : 0 );
		s32 colIncrement = dir == Direction::East  ? 1 : ( dir == Direction::West ? -1 : 0 );
		u32 numIterations = (u32)abs( (s32)GetWidth()*colIncrement + (s32)GetHeight()*rowIncrement);
		for ( u32 i = 0; i < numIterations; ++i ) 
		{			
			u32 index = CalcIndex(row + rowIncrement*i,col + colIncrement*i);
			
			Brick* tmp = m_bricks[index];
			m_bricks[index] = brick;
			brick->NotifyPosition(row + rowIncrement*i,col + colIncrement*i);
			brick = tmp;
		}
		return brick;
	}

	Direction::Type Board::GetDirectionFromIndex(u32 index)
	{
		if (index < m_width)						// Lower
			return Direction::North;
		else if (index < 2 * m_width)				// Upper
			return Direction::South;
		else if (index < (2*m_width + m_height))	// Left
			return Direction::East;
		else										// Right
			return Direction::West;
	}


	void Board::GetRowColumnFromIndex(u32 hitSurfaceIndex, u32& row, u32& col)
	{
		u32 index = hitSurfaceIndex;
		if (index < m_width)						// Lower
		{
			row = 0;
			col = index % m_width;
		}
		else if (index < 2 * m_width)				// Upper
		{
			row = m_height - 1;
			col = (index - m_width) % m_width;
		}
		else if (index < (2*m_width + m_height))	// Left
		{
			col = 0;
			row = (index - 2 * m_width) % m_height;
		}
		else										// Right
		{
			col = m_width - 1;
			row = (index - 2*m_width - m_height) % m_height;
		}
	}
	
	Board::~Board()
	{		
		if (m_bricks)
		{
			for (u32 i = 0; i < m_height; ++i)
			{
				for ( u32 j = 0; j < m_width; ++j)
				{
					u32 index = CalcIndex(i,j);
					delete m_bricks[index];
					m_bricks[index] = 0;
				}
			}
		}
		free(m_bricks);

		if (m_hitSurfaces)
		{
			for (int i = 0; i < 2 * m_width * m_height; ++i)
			{
				Renderer::UnregisterHitSurface(&m_hitSurfaces[i]);
			}
		}
		free(m_hitSurfaces);
	}
}
